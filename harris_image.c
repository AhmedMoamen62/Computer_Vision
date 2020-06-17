#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#include "image_math.h"
#include "matrix.h"
#include <time.h>

// Frees an array of descriptors.
// descriptor *d: the array.
// int n: number of elements in array.
void free_descriptors(descriptor *d, int n)
{
    int i;
    for(i = 0; i < n; ++i){
        free(d[i].data);
    }
    free(d);
}

// Create a feature descriptor for an index in an image.
// image im: source image.
// int i: index in image for the pixel we want to describe.
// returns: descriptor for that index.
descriptor describe_index(image im, int i)
{
    int w = 5;
    descriptor d;
    d.p.x = i%im.w; // suppose image 3*3 and i = 7 , so x (col) = 1 as 7%3 = 1
    d.p.y = i/im.w; // suppose image 3*3 and i = 7 , so y (row) = 1 as 7/3 = 2
    d.data = calloc(w*w*im.c, sizeof(float)); // allocate descriptor (image) with 5*5 pixels with the same number of channels
    d.n = w*w*im.c; // number of pixels
    int c, dx, dy;
    int count = 0;
    // If you want you can experiment with other descriptors
    // This subtracts the central value from neighbors
    // to compensate some for exposure/lighting changes.
    for(c = 0; c < im.c; ++c){  // iterate over all channels
        float cval = im.data[c*im.w*im.h + i];  // get pixel value of the index in each channel
        for(dx = -w/2; dx < (w+1)/2; ++dx){     // iterate over the descriptor pixels in columns from -2 to 2
            for(dy = -w/2; dy < (w+1)/2; ++dy){ // iterate over the descriptor pixels in rows from -2 to 2
                float val = get_pixel(im, i%im.w+dx, i/im.w+dy, c); // get the neighboor pixel in the descriptor
                d.data[count++] = cval - val;                       // set this pixel in the descriptor with the difference between index pixel and descriptor itself
            }
        }
    }
    return d;
}

// Marks the spot of a point in an image.
// image im: image to mark.
// ponit p: spot to mark in the image.
void mark_spot(image im, point p)
{
    int x = p.x;
    int y = p.y;
    int i;
    // draw the pink cross with 9 pixels arround the corner
    for(i = -9; i < 10; ++i){
        set_pixel(im, x+i, y, 0, 1);
        set_pixel(im, x, y+i, 0, 1);
        set_pixel(im, x+i, y, 1, 0);
        set_pixel(im, x, y+i, 1, 0);
        set_pixel(im, x+i, y, 2, 1);
        set_pixel(im, x, y+i, 2, 1);
    }
}

// Marks corners denoted by an array of descriptors.
// image im: image to mark.
// descriptor *d: corners in the image.
// int n: number of descriptors to mark.
void mark_corners(image im, descriptor *d, int n)
{
    int i;
    for(i = 0; i < n; ++i){ // iterate over number of descriptors or corners
        mark_spot(im, d[i].p);
    }
}

// Creates a 1d Gaussian filter.
// float sigma: standard deviation of Gaussian.
// returns: single row image of the filter.
image make_1d_gaussian(float sigma)
{
    // TODO: optional, make separable 1d Gaussian.
    int sigma_size = sigma*6;
    int gaussian_size = sigma_size + 1 - sigma_size%2;

    float sigma_square = powf(sigma,2);
    float outter_coefficient = sqrtf(1.0/(TWOPI*sigma_square));
    float inner_coefficient = -1.0/(2*sigma_square);

    image img = make_image(gaussian_size,1,1);
    int center = (int)gaussian_size/2;

    for(int col = 0 ; col < img.w ; col++)
    {
        float pixel_value = outter_coefficient*expf(inner_coefficient*(powf(col - center,2)));
        set_pixel(img,col,0,0,pixel_value);
    }
    l1_normalize(img);
    return img;
}

// Smooths an image using separable Gaussian filter.
// image im: image to smooth.
// float sigma: std dev. for Gaussian.
// returns: smoothed image.
image smooth_image(image im, float sigma)
{
    if(0){
        image g = make_gaussian_filter(sigma);
        image s = convolve_image(im, g, 1);
        free_image(g);
        return s;
    } else {
        // TODO: optional, use two convolutions with 1d gaussian filter.
        // If you implement, disable the above if check.
        image horizontal_gaussian = make_1d_gaussian(sigma);
        image vertical_gaussian = image_transpose(horizontal_gaussian);

        image img = convolve_image(im,horizontal_gaussian,1);
        img = convolve_image(img,vertical_gaussian,1);

        free_image(horizontal_gaussian);
        free_image(vertical_gaussian);

        return img;
    }
}

// Calculate the structure matrix of an image.
// image im: the input image.
// float sigma: std dev. to use for weighted sum.
// returns: structure matrix. 1st channel is Ix^2, 2nd channel is Iy^2,
//          third channel is IxIy.
image structure_matrix(image im, float sigma)
{
    image S = make_image(im.w, im.h, 3);
    // TODO: calculate structure matrix for im.
    image gx = make_gx_filter();
    image gy = make_gy_filter();

    image img_gx = convolve_image(im,gx,0);
    image img_gy = convolve_image(im,gy,0);

    for(int row = 0 ; row < S.h; row++)
    {
        for(int col = 0 ; col < S.w ; col++)
        {
            float channel_1 = get_pixel(img_gx,col,row,0)*get_pixel(img_gx,col,row,0);
            float channel_2 = get_pixel(img_gy,col,row,0)*get_pixel(img_gy,col,row,0);
            float channel_3 = get_pixel(img_gx,col,row,0)*get_pixel(img_gy,col,row,0);

            set_pixel(S,col,row,0,channel_1);
            set_pixel(S,col,row,1,channel_2);
            set_pixel(S,col,row,2,channel_3);
        }
    }

    S = smooth_image(S,sigma);

    free_image(gx);
    free_image(gy);
    free_image(img_gx);
    free_image(img_gy);

    return S;
}

// Estimate the cornerness of each pixel given a structure matrix S.
// image S: structure matrix for an image.
// returns: a response map of cornerness calculations.
image cornerness_response(image S)
{
    image R = make_image(S.w, S.h, 1);
    // TODO: fill in R, "cornerness" for each pixel using the structure matrix.
    // We'll use formulation det(S) - alpha * trace(S)^2, alpha = .06.
    for(int row = 0 ; row < S.h; row++)
    {
        for(int col = 0 ; col < S.w ; col++)
        {
            float det = get_pixel(S,col,row,0)*get_pixel(S,col,row,1)
                      - get_pixel(S,col,row,2)*get_pixel(S,col,row,2);
            float trace = get_pixel(S,col,row,0) + get_pixel(S,col,row,1);
            float pixel_value = det - 0.06*trace*trace;

            set_pixel(R,col,row,0,pixel_value);
        }
    }

    return R;
}

float check_window_maximum(image img,int ch,int start_row_img,int start_col_img,int window_size,float value)
{
    for (int start_row_window = 0 ; start_row_window < window_size/2 ; start_row_window++)
    {
        int opposite_row = window_size - start_row_window - 1;

        for (int start_col_window = 0; start_col_window < window_size/2 ; start_col_window++)
        {
            int opposite_col = window_size - start_col_window - 1;

            float image_value_1 = get_pixel(img,start_col_img + start_col_window,start_row_img + start_row_window,ch);

            float image_value_2 = get_pixel(img,start_col_img + opposite_col,start_row_img + start_row_window,ch);

            float image_value_3 = get_pixel(img,start_col_img + start_col_window,start_row_img + opposite_row,ch);

            float image_value_4 = get_pixel(img,start_col_img + opposite_col,start_row_img + opposite_row,ch);

            float max_neighboor = four_max_value(image_value_1,image_value_2,image_value_3,image_value_4);

            if(max_neighboor > value)
            {
                return -999999;
            }

        }
    }
    if(window_size % 2 == 1)
    {
        int window_center_row = window_size/2;

        for (int start_col_window = 0; start_col_window < window_size/2 ; start_col_window++)
        {
            int opposite_col = window_size - start_col_window - 1;

            float image_value_1 = get_pixel(img,start_col_img + start_col_window,start_row_img + window_center_row,ch);

            float image_value_2 = get_pixel(img,start_col_img + opposite_col,start_row_img + window_center_row,ch);

            if(image_value_1 > value || image_value_2 > value)
            {
                return -999999;
            }

        }

    }
    if(window_size % 2 == 1)
    {
        int window_center_col = window_size/2;

        for (int start_row_window = 0; start_row_window < window_size/2 ; start_row_window++)
        {
            int opposite_row = window_size - start_row_window - 1;

            float image_value_1 = get_pixel(img,start_col_img + window_center_col,start_row_img + start_row_window,ch);

            float image_value_2 = get_pixel(img,start_col_img + window_center_col,start_row_img + opposite_row,ch);

            if(image_value_1 > value || image_value_2 > value)
            {
                return -999999;
            }
        }
    }

    return value;
}

// Perform non-max supression on an image of feature responses.
// image im: 1-channel image of feature responses.
// int w: distance to look for larger responses.
// returns: image with only local-maxima responses within w pixels.
image nms_image(image im, int w)
{
    image r = copy_image(im);
    // TODO: perform NMS on the response map.
    // for every pixel in the image:
    //     for neighbors within w:
    //         if neighbor response greater than pixel response:
    //             set response to be very low (I use -999999 [why not 0??])
    int window_size = 2*w + 1;
    for(int row = 0 ; row < r.h ; row++)
    {
        int start_row_img = row - w;
        for(int col = 0; col < r.w ; col++)
        {
            int start_col_img = col - w;
            for(int ch = 0 ; ch < r.c ; ch++)
            {
                float pixel_value  = get_pixel(r,col,row,ch);
                float suppression_value = check_window_maximum(r,ch,start_row_img,start_col_img,window_size,pixel_value);
                set_pixel(r,col,row,ch,suppression_value);
            }
        }
    }
    return r;
}

int count_responses(image img,float thresh)
{
    int count = 0;
    for(int row = 0 ; row < img.h ; row++)
    {
        for(int col = 0; col < img.w ; col++)
        {
            for(int ch = 0 ; ch < img.c ; ch++)
            {
                if(get_pixel(img,col,row,ch) > thresh)
                {
                    count++;
                }
            }
        }
    }

    return count;
}

// Perform harris corner detection and extract features from the corners.
// image im: input image.
// float sigma: std. dev for harris.
// float thresh: threshold for cornerness.
// int nms: distance to look for local-maxes in response map.
// int *n: pointer to number of corners detected, should fill in.
// returns: array of descriptors of the corners in the image.
descriptor *harris_corner_detector(image im, float sigma, float thresh, int nms, int *n)
{
    // Calculate structure matrix
    image S = structure_matrix(im, sigma);

    // Estimate cornerness
    image R = cornerness_response(S);

    // Run NMS on the responses
    image Rnms = nms_image(R, nms);


    //TODO: count number of responses over threshold
    int count = count_responses(Rnms,thresh); // change this

    
    *n = count; // <- set *n equal to number of corners in image.
    descriptor *d = calloc(count, sizeof(descriptor));
    //TODO: fill in array *d with descriptors of corners, use describe_index.
    int index  = 0;
    int i = 0;
    for(; i < count ; i++)
    {
        for(; index < Rnms.h*Rnms.w ; index++)
        {
            if(Rnms.data[index] > thresh)
            {
               d[i] = describe_index(im,index);
               index++;
               break;
            }
        }
    }

    free_image(S);
    free_image(R);
    free_image(Rnms);
    return d;
}

// Find and draw corners on an image.
// image im: input image.
// float sigma: std. dev for harris.
// float thresh: threshold for cornerness.
// int nms: distance to look for local-maxes in response map.
void detect_and_draw_corners(image im, float sigma, float thresh, int nms)
{
    int n = 0;
    descriptor *d = harris_corner_detector(im, sigma, thresh, nms, &n);
    mark_corners(im, d, n);
}
