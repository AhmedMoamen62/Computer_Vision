#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#include "matrix.h"

// Draws a line on an image with color corresponding to the direction of line
// image im: image to draw line on
// float x, y: starting point of line
// float dx, dy: vector corresponding to line angle and magnitude
void draw_line(image im, float x, float y, float dx, float dy)
{
    assert(im.c == 3);
    // get the angle in radian in range of -pi --> pi
    // normalize by dividing by 2*pi ro get range of -0.5 --> 0.5
    // then shift the range to be of 0 --> 1
    // then scale the range to be of 0 --> 6
    float angle = 6*(atan2(dy, dx) / TWOPI + .5);
    // get the integer value of the angle
    int index = floor(angle);
    // get the float difference value (f <= 1 && f >= 0)
    float f = angle - index;
    float r, g, b;
    // set different color with respect to the angle and the difference f
    if(index == 0){ // theta between 0 and 60 degree
        r = 1; g = f; b = 0;
    } else if(index == 1){ // theta between 60 and 120 degree
        r = 1-f; g = 1; b = 0;
    } else if(index == 2){ // theta between 120 and 180 degree
        r = 0; g = 1; b = f;
    } else if(index == 3){ // theta between 180 and 240 degree
        r = 0; g = 1-f; b = 1;
    } else if(index == 4){ // theta between 240 and 300 degree
        r = f; g = 0; b = 1;
    } else { // theta between 300 and 360 degree
        r = 1; g = 0; b = 1-f;
    }
    float i;
    // get the distance to dx and dy point from zero reference
    float d = sqrt(dx*dx + dy*dy);
    // iterate from zero reference untill the end of the distance d to draw the curve
    for(i = 0; i < d; i++){
        // get a ratio of the current iteration to the total distance
        // then multiply it with delta variation in x , y to get the abslute variation in the image coordinates
        // then add the orginial x , y value to draw the new point
        int xi = x + dx*i/d;
        int yi = y + dy*i/d;
        // color the point with the calculated rgb colors wrt the angle
        set_pixel(im, xi, yi, 0, r);
        set_pixel(im, xi, yi, 1, g);
        set_pixel(im, xi, yi, 2, b);
    }
}

// Make an integral image or summed area table from an image
// image im: image to process
// returns: image I such that I[x,y] = sum{i<=x, j<=y}(im[i,j])
image make_integral_image(image im)
{
    image integ = make_image(im.w, im.h, im.c);
    // TODO: fill in the integral image
    for(int row = 0 ; row < integ.h ; row++)
    {
        for (int col = 0 ; col < integ.w ; col++)
        {
            for (int ch = 0; ch < integ.c ; ch++)
            {
                float original_pixel = get_pixel_padding(im,col,row,ch);
                float left_pixel = get_pixel_padding(integ,col - 1,row,ch);
                float top_pixel = get_pixel_padding(integ,col,row - 1,ch);
                float top_left_pixel = get_pixel_padding(integ,col - 1,row - 1,ch);

                float pixel_value = original_pixel + left_pixel + top_pixel - top_left_pixel;
                set_pixel(integ,col,row,ch,pixel_value);
            }
        }
    }
    return integ;
}

// Apply a box filter to an image using an integral image for speed
// image im: image to smooth
// int s: window size for box filter
// returns: smoothed image
image box_filter_image(image im, int s)
{
    if(1)
    {
        int i,j,k;
        image integ = make_integral_image(im);
        image S = make_image(im.w, im.h, im.c);
        float weight = 1.0/(s*s);
        // TODO: fill in S using the integral image.
        for(i = 0 ; i < S.h ; i++) // row
        {
            int top_row = i - s/2 - 1;
            int bottom_row = i + s/2;
            for(j = 0 ; j < S.w ; j++) // column
            {
                int left_col = j - s/2 - 1;
                int right_col = j + s/2;
                for(k = 0 ; k < S.c ; k++) // channel
                {
                    float right_bottom = get_pixel(integ,right_col,bottom_row,k);
                    float right_top = get_pixel(integ,right_col,top_row,k);
                    float left_top = get_pixel(integ,left_col,top_row,k);
                    float left_bottom = get_pixel(integ,left_col,bottom_row,k);

                    float pixel_value = (right_bottom - right_top + left_top - left_bottom)*weight;
                    set_pixel(S,j,i,k,pixel_value);
                }
            }
        }
        free_image(integ);
        return S;
    }
    else
    {
        image box = make_box_filter(s);
        image filtered = convolve_image(im,box,1);
        free_image(box);
        return filtered;
    }
}

// Calculate the time-structure matrix of an image pair.
// image im: the input image.
// image prev: the previous image in sequence.
// int s: window size for smoothing.
// returns: structure matrix. 1st channel is Ix^2, 2nd channel is Iy^2,
//          3rd channel is IxIy, 4th channel is IxIt, 5th channel is IyIt.
image time_structure_matrix(image im, image prev, int s)
{
    assert(im.h == prev.h && im.w == prev.w && im.c == prev.c);

    int converted = 0;
    // convert the image to gray scale
    if(im.c == 3){
        converted = 1;
        im = rgb_to_grayscale(im);
        prev = rgb_to_grayscale(prev);
    }

    // TODO: calculate gradients, structure components, and smooth them

    image S = make_image(im.w,im.h,5);

    // calculate the Ix, Iy gradients
    image gx = make_gx_filter();
    image gy = make_gy_filter();

    image img_gx = convolve_image(im,gx,0);
    image img_gy = convolve_image(im,gy,0);

    for(int row = 0 ; row < S.h; row++)
    {
        for(int col = 0 ; col < S.w ; col++)
        {
            // calculate the It gradient (it's the difference between two images)
            float It_pixel = get_pixel(im,col,row,0) - get_pixel(prev,col,row,0);

            float channel_1 = get_pixel(img_gx,col,row,0)*get_pixel(img_gx,col,row,0);
            float channel_2 = get_pixel(img_gy,col,row,0)*get_pixel(img_gy,col,row,0);
            float channel_3 = get_pixel(img_gx,col,row,0)*get_pixel(img_gy,col,row,0);
            float channel_4 = get_pixel(img_gx,col,row,0)*It_pixel;
            float channel_5 = get_pixel(img_gy,col,row,0)*It_pixel;

            set_pixel(S,col,row,0,channel_1);
            set_pixel(S,col,row,1,channel_2);
            set_pixel(S,col,row,2,channel_3);
            set_pixel(S,col,row,3,channel_4);
            set_pixel(S,col,row,4,channel_5);
        }
    }

    // smooth the image with box filter
    S = box_filter_image(S,s);

    free_image(gx);
    free_image(gy);
    free_image(img_gx);
    free_image(img_gy);

    if(converted){
        free_image(im); free_image(prev);
    }
    return S;
}

// Calculate the velocity given a structure image
// image S: time-structure image
// int stride: only calculate subset of pixels for speed
image velocity_image(image S, int stride)
{
    // make imaga downsampled by the stride(step)
    image v = make_image(S.w/stride, S.h/stride, 3);
    int i, j;
    matrix M = make_matrix(2,2);
    matrix T = make_matrix(2,1);
    matrix invert;
    matrix mul;
    // solve the vx and vy by the matrix M and T over the image v
    for(j = (stride-1)/2; j < S.h; j += stride){ // start row with the half the stride and the counter step it the stride
        for(i = (stride-1)/2; i < S.w; i += stride){ // start column with the half the stride and the counter step it the stride
            float Ixx = get_pixel(S,i,j,0);
            float Iyy = get_pixel(S,i,j,1);
            float Ixy = get_pixel(S,i,j,2);
            float Ixt = get_pixel(S,i,j,3);
            float Iyt = get_pixel(S,i,j,4);
            // TODO: calculate vx and vy using the flow equation
            float vx = 0;
            float vy = 0;

            // fill the mtrix M , T by its values
            M.data[0][0] = Ixx;
            M.data[0][1] = Ixy;
            M.data[1][0] = Ixy;
            M.data[1][1] = Iyy;

            T.data[0][0] = -Ixt;
            T.data[1][0] = -Iyt;

            // inverse the Matrix M
            invert = matrix_invert(M);

            // check if it's invertable first
            if(invert.data)
            {
                // multuply the mtrix to get velocity matrix
                mul = matrix_mult_matrix(invert,T);

                // extract the values from the velocity matrix
                vx = mul.data[0][0];
                vy = mul.data[1][0];
            }

            // fill the first required pixels in the image v
            // if stride = 8 , start = 2,10,18,...etc, index = 2/8,10/8,18/8 = 0,1,2
            set_pixel(v, i/stride, j/stride, 0, vx);
            set_pixel(v, i/stride, j/stride, 1, vy);
        }
    }
    free_matrix(M);
    free_matrix(T);
    free_matrix(invert);
    free_matrix(mul);
    return v;
}

// Draw lines on an image given the velocity
// image im: image to draw on
// image v: velocity of each pixel
// float scale: scalar to multiply velocity by for drawing
void draw_flow(image im, image v, float scale)
{
    // to get the stride(step) --> v.w = im.w/stride , stride = im.w/v.w
    int stride = im.w / v.w;
    int i,j;
    for (j = (stride-1)/2; j < im.h; j += stride) { // start row with the half the stride and the counter step it the stride
        for (i = (stride-1)/2; i < im.w; i += stride) { // start column with the half the stride and the counter step it the stride
            // at high scalar --> the line will get very large so it's prefered to be equal to the stride (step)
            float dx = scale*get_pixel(v, i/stride, j/stride, 0); // get the delta of x by multiply the velocity with constant scalar (time slice , dx = t*vx)
            float dy = scale*get_pixel(v, i/stride, j/stride, 1); // get the delta of y by multiply the velocity with constant scalar (time slice , dy = t*vy)
            if(fabs(dx) > im.w) dx = 0; // check if the dx is greater than image width , set it to zer0 --> unchanged
            if(fabs(dy) > im.h) dy = 0; // check if the dy is greater than image width , set it to zer0 --> unchanged
            draw_line(im, i, j, dx, dy); // draw the flow change with respect to the dx and dy
        }
    }
}


// Constrain the absolute value of each image pixel
// image im: image to constrain
// float v: each pixel will be in range [-v, v]
void constrain_image(image im, float v)
{
    int i;
    // make the range of pixels value for [-v,v]
    for(i = 0; i < im.w*im.h*im.c; ++i){
        if (im.data[i] < -v) im.data[i] = -v;
        if (im.data[i] >  v) im.data[i] =  v;
    }
}

// Calculate the optical flow between two images
// image im: current image
// image prev: previous image
// int smooth: amount to smooth structure matrix by
// int stride: downsampling for velocity matrix
// returns: velocity matrix
image optical_flow_images(image im, image prev, int smooth, int stride)
{
    image S = time_structure_matrix(im, prev, smooth);   
    image v = velocity_image(S, stride);
    // set the range of the image v
    constrain_image(v, 6);
    // smooth the velocity matrix to remove the high frequency of v
    image vs = smooth_image(v, 2);
    free_image(v);
    free_image(S);
    return vs;
}

// Run optical flow demo on webcam
// int smooth: amount to smooth structure matrix by
// int stride: downsampling for velocity matrix
// int div: downsampling factor for images from webcam
void optical_flow_webcam(int smooth, int stride, int div,int camera_index)
{
    // smooth to is the sigma for gaussian filter
    // stride is the step of dawnsampling the image
    // div a scalar to the image to resize it
    // camera_index to select a camera from the device
#ifdef OPENCV
    CvCapture * cap;
    // get the indexed camera connected to the device
    cap = cvCaptureFromCAM(camera_index);
    // capture image from live streaming
    image prev = get_image_from_stream(cap);
    // resize this image to get high response
    image prev_c = nn_resize(prev, prev.w/div, prev.h/div);
    // capture another image from live streaming
    image im = get_image_from_stream(cap);
    // resize this image to be equal to the previous image
    image im_c = nn_resize(im, im.w/div, im.h/div);
    // while one loop to capture images in sequence
    while(im.data){
        // copy the new original image to edit it
        image copy = copy_image(im);
        // run sparse optical flow algorithm on the resized image
        image v = optical_flow_images(im_c, prev_c, smooth, stride);
        // draw the flow changes on the original image
        draw_flow(copy, v, smooth*div);
        // show the drawing on the copied image and get key value from keyboard if entered any key
        int key = show_image(copy, "flow", 5);
        // free all the used image from memory
        free_image(v);
        free_image(copy);
        free_image(prev);
        free_image(prev_c);
        // make the current original image equal the previous original image
        prev = im;
        // make the current resized image equal the previous resized image
        prev_c = im_c;
        // check if the key value equal esc --> break the loop
        if(key != -1) {
            key = key % 256;
            printf("%d\n", key);
            if (key == 27) break;
        }
        // capture a new image and resize it
        im = get_image_from_stream(cap);
        im_c = nn_resize(im, im.w/div, im.h/div);
    }
#else
    fprintf(stderr, "Must compile with OpenCV\n");
#endif
}
