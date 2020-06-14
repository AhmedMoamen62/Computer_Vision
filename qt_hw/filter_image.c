#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853

float convolve_1_in_1(int start_row_img,int start_col_img,int ch_img,int ch_kernel,image img,image kernel)
{
    float avg = 0;

    for (int start_row_kernel = 0 ; start_row_kernel < kernel.h/2 ; start_row_kernel++)
    {
        int opposite_row = kernel.h - start_row_kernel - 1;

        for (int start_col_kernel = 0; start_col_kernel < kernel.w/2 ; start_col_kernel++)
        {
            int opposite_col = kernel.w - start_col_kernel - 1;

            float kernel_value_1 = get_pixel(kernel,start_col_kernel,start_row_kernel,ch_kernel);
            float image_value_1 = get_pixel(img,start_col_img + start_col_kernel,start_row_img + start_row_kernel,ch_img);

            float kernel_value_2 = get_pixel(kernel,opposite_col,start_row_kernel,ch_kernel);
            float image_value_2 = get_pixel(img,start_col_img + opposite_col,start_row_img + start_row_kernel,ch_img);

            float kernel_value_3 = get_pixel(kernel,start_col_kernel,opposite_row,ch_kernel);
            float image_value_3 = get_pixel(img,start_col_img + start_col_kernel,start_row_img + opposite_row,ch_img);

            float kernel_value_4 = get_pixel(kernel,opposite_col,opposite_row,ch_kernel);
            float image_value_4 = get_pixel(img,start_col_img + opposite_col,start_row_img + opposite_row,ch_img);

            avg += kernel_value_1*image_value_1 + kernel_value_2*image_value_2
                 + kernel_value_3*image_value_3 + kernel_value_4*image_value_4;
        }
    }
    if(kernel.h % 2 == 1)
    {
        int kernel_center_row = kernel.h/2;

        for (int start_col_kernel = 0; start_col_kernel < kernel.w/2 ; start_col_kernel++)
        {
            int opposite_col = kernel.w - start_col_kernel - 1;

            float kernel_value_1 = get_pixel(kernel,start_col_kernel,kernel_center_row,ch_kernel);
            float image_value_1 = get_pixel(img,start_col_img + start_col_kernel,start_row_img + kernel_center_row,ch_img);

            float kernel_value_2 = get_pixel(kernel,opposite_col,kernel_center_row,ch_kernel);
            float image_value_2 = get_pixel(img,start_col_img + opposite_col,start_row_img + kernel_center_row,ch_img);

            avg += kernel_value_1*image_value_1 + kernel_value_2*image_value_2;
        }

    }
    if(kernel.w % 2 == 1)
    {
        int kernel_center_col = kernel.w/2;

        for (int start_row_kernel = 0; start_row_kernel < kernel.h/2 ; start_row_kernel++)
        {
            int opposite_row = kernel.h - start_row_kernel - 1;

            float kernel_value_1 = get_pixel(kernel,kernel_center_col,start_row_kernel,ch_kernel);
            float image_value_1 = get_pixel(img,start_col_img + kernel_center_col,start_row_img + start_row_kernel,ch_img);

            float kernel_value_2 = get_pixel(kernel,kernel_center_col,opposite_row,ch_kernel);
            float image_value_2 = get_pixel(img,start_col_img + kernel_center_col,start_row_img + opposite_row,ch_img);

            avg += kernel_value_1*image_value_1 + kernel_value_2*image_value_2;
        }
    }
    if(kernel.h % 2 == 1 && kernel.w % 2 == 1)
    {
        int kernel_center_row = kernel.h/2;
        int kernel_center_col = kernel.w/2;

        float kernel_value = get_pixel(kernel,kernel_center_col,kernel_center_row,ch_kernel);
        float image_value = get_pixel(img,start_col_img + kernel_center_col,start_row_img + kernel_center_row,ch_img);

        avg += kernel_value*image_value;
    }
    return avg;
}

image calculate_avg(image img,image im,image filter,int mode)
{

    for(int row = 0 ; row < im.h ; row++)
    {
        int start_row_img = row - filter.h/2;
        for(int col = 0; col < im.w ; col++)
        {
            int start_col_img = col - filter.w/2;
            float pixel_value = 0;
            for(int ch = 0 ; ch < im.c ; ch++)
            {
                // check if mode = 0 , we get all the convolved pixels from every channed in the original image
                if(mode == 0)
                {
                    pixel_value += convolve_1_in_1(start_row_img,start_col_img,ch,0,im,filter);
                }
                // check if mode = 1 , we set every channel with the opposite convolved channel with the original image
                else
                {
                    pixel_value = convolve_1_in_1(start_row_img,start_col_img,ch,ch,im,filter);
                    set_pixel(img,col,row,ch,pixel_value);
                }                
            }
            if(mode == 0)
            {
                set_pixel(img,col,row,0,pixel_value);
            }
        }
    }
    return img;
}

image convolve_image(image im, image filter, int preserve)
{
    // TODO
    assert(im.c == filter.c || filter.c == 1);
    image img;
    if(filter.c == 1)
    {
        if(preserve != 1)
        {
            img = make_image(im.w,im.h,1);
            img = calculate_avg(img,im,filter,0);
        }
        else
        {
            img = make_image(im.w,im.h,3);
            img = calculate_avg(img,im,filter,1);
        }
    }
    else if(im.c == filter.c)
    {
        if(preserve != 1)
        {
            img = make_image(im.w,im.h,1);
            img = calculate_avg(img,im,filter,0);
        }
        else
        {
            img = make_image(im.w,im.h,im.c);
            img = calculate_avg(img,im,filter,1);
        }
    }
    return img;
}

void l1_normalize(image im)
{
    // TODO
    float sum = 0;
    for(int row = 0 ; row < im.h ; row++)
    {
        for(int col = 0; col < im.w ; col++)
        {
            for(int ch = 0 ; ch < im.c ; ch++)
            {
                sum += get_pixel(im,col,row,ch);
            }
        }
    }
    if(sum != 1)
    {
        float weight = -(sum - 1)/(im.h*im.w);
        for(int row = 0 ; row < im.h ; row++)
        {
            for(int col = 0; col < im.w ; col++)
            {
                for(int ch = 0 ; ch < im.c ; ch++)
                {
                    float pixel_value = get_pixel(im,col,row,ch) + weight;
                    set_pixel(im,col,row,ch,pixel_value);
                }
            }
        }
    }
}

image make_box_filter(int w)
{
    // TODO
    image img = make_image(w,w,1);
    float weight = 1.0/(w*w);
    for(int row = 0 ; row < img.h ; row++)
    {
        for(int col = 0; col < img.w ; col++)
        {
            set_pixel(img,col,row,0,weight);
        }
    }
    return img;
}

image make_highpass_filter()
{
    // TODO
    image img = make_image(3,3,1);

    set_pixel(img,1,0,0,-1);
    set_pixel(img,0,1,0,-1);
    set_pixel(img,2,1,0,-1);
    set_pixel(img,1,2,0,-1);
    set_pixel(img,1,1,0,4);

    return img;
}

image make_sharpen_filter()
{
    // TODO

    image img = make_image(3,3,1);

    set_pixel(img,1,0,0,-1);
    set_pixel(img,0,1,0,-1);
    set_pixel(img,2,1,0,-1);
    set_pixel(img,1,2,0,-1);
    set_pixel(img,1,1,0,5);

    return img;
}

image make_emboss_filter()
{
    // TODO
    image img = make_image(3,3,1);

    set_pixel(img,0,0,0,-2);
    set_pixel(img,0,1,0,-1);
    set_pixel(img,1,0,0,-1);
    set_pixel(img,2,2,0,2);
    set_pixel(img,2,1,0,1);
    set_pixel(img,1,2,0,1);
    set_pixel(img,1,1,0,1);

    return img;
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: sharpen and emboss, to keep the colored image

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: yes clamp the image after highpass filter

image make_gaussian_filter(float sigma)
{
    // TODO
    int sigma_size = sigma*6;
    int gaussian_size = sigma_size + 1 - sigma_size%2;

    float sigma_square = powf(sigma,2);
    float outter_coefficient = 1.0/(TWOPI*sigma_square);
    float inner_coefficient = -1.0/(2*sigma_square);

    image img = make_image(gaussian_size,gaussian_size,1);
    int center = (int)gaussian_size/2;

    for(int row = 0 ; row < img.h ; row++)
    {
        float row_square = powf(row - center,2);
        for(int col = 0; col < img.w ; col++)
        {
            float pixel_value = outter_coefficient*expf(inner_coefficient*(row_square + powf(col - center,2)));
            set_pixel(img,col,row,0,pixel_value);
        }
    }
    l1_normalize(img);
    return img;
}

image add_image(image a, image b)
{
    // TODO
    assert(a.c == b.c && a.h == b.h && a.w == b.w);
    image img = make_image(a.w,a.h,a.c);
    for(int row = 0; row < a.h ; row++)
    {
        for(int col = 0; col < a.w ; col++)
        {
            for(int ch = 0;  ch < a.c ; ch++)
            {
                set_pixel(img,col,row,ch,get_pixel(a,col,row,ch) + get_pixel(b,col,row,ch));
            }
        }
    }
    return img;
}

image sub_image(image a, image b)
{
    // TODO
    assert(a.c == b.c && a.h == b.h && a.w == b.w);
    image img = make_image(a.w,a.h,a.c);
    for(int row = 0; row < a.h ; row++)
    {
        for(int col = 0; col < a.w ; col++)
        {
            for(int ch = 0;  ch < a.c ; ch++)
            {
                set_pixel(img,col,row,ch,get_pixel(a,col,row,ch) - get_pixel(b,col,row,ch));
            }
        }
    }
    return img;
}

image make_gx_filter()
{
    // TODO
    image img = make_image(3,3,1);

    set_pixel(img,0,0,0,-1);
    set_pixel(img,0,1,0,-2);
    set_pixel(img,0,2,0,-1);
    set_pixel(img,2,0,0,1);
    set_pixel(img,2,1,0,2);
    set_pixel(img,2,2,0,1);

    return img;
}

image make_gy_filter()
{
    // TODO
    image img = make_image(3,3,1);

    set_pixel(img,0,0,0,-1);
    set_pixel(img,1,0,0,-2);
    set_pixel(img,2,0,0,-1);
    set_pixel(img,0,2,0,1);
    set_pixel(img,1,2,0,2);
    set_pixel(img,2,2,0,1);

    return img;
}

void feature_normalize(image im)
{
    // TODO
    float min_value = get_pixel(im,0,0,0);
    float max_value = get_pixel(im,0,0,0);

    for(int row = 0 ; row < im.h ; row++)
    {
        for(int col = 0 ; col < im.w ; col++)
        {
            for(int ch = 0; ch < im.c ; ch++)
            {
                float pixel_value = get_pixel(im,col,row,ch);
                if(pixel_value > max_value)
                {
                    max_value = pixel_value;
                }
                if(pixel_value < min_value)
                {
                    min_value = pixel_value;
                }
            }
        }
    }

    float denominator = max_value - min_value;

    if(denominator == 0)
    {
        for(int row = 0 ; row < im.h ; row++)
        {
            for(int col = 0 ; col < im.w ; col++)
            {
                for(int ch = 0; ch < im.c ; ch++)
                {
                    set_pixel(im,col,row,ch,0);
                }
            }
        }
        return;
    }

    for(int row = 0 ; row < im.h ; row++)
    {
        for(int col = 0 ; col < im.w ; col++)
        {
            for(int ch = 0; ch < im.c ; ch++)
            {
                float pixel_value = get_pixel(im,col,row,ch);
                float normalized_pixel = (pixel_value - min_value)/denominator;
                set_pixel(im,col,row,ch,normalized_pixel);
            }
        }
    }
}

image *sobel_image(image im)
{
    // TODO
    image * img = calloc(2, sizeof(image));
    img[0] = make_image(im.w,im.h,1);
    img[1] = make_image(im.w,im.h,1);

    image gy = make_gy_filter();
    image gx = make_gx_filter();

    image img_gy = convolve_image(im,gy,0);
    image img_gx = convolve_image(im,gx,0);

    for(int row = 0 ; row < im.h ; row++)
    {
        for(int col = 0 ; col < im.w ; col++)
        {
            float gx_value = get_pixel(img_gx,col,row,0);
            float gy_value = get_pixel(img_gy,col,row,0);

            float pixel_value = sqrtf(powf(gx_value,2) + powf(gy_value,2));
            set_pixel(img[0],col,row,0,pixel_value);

            float angle = atan2f(gy_value,gx_value);
            set_pixel(img[1],col,row,0,angle);
        }
    }

    return img;
}

image colorize_sobel(image im)
{
    // TODO
    image * sobel = sobel_image(im);
    image img = make_image(im.w,im.h,3);

    feature_normalize(sobel[0]);
    feature_normalize(sobel[1]);

    for(int row = 0 ; row < im.h ; row++)
    {
        for(int col = 0 ; col < im.w ; col++)
        {
            float value = get_pixel(sobel[0],col,row,0);
            float saturation = get_pixel(sobel[0],col,row,0);
            float hue = get_pixel(sobel[1],col,row,0);

            set_pixel(img,col,row,0,hue);
            set_pixel(img,col,row,1,saturation);
            set_pixel(img,col,row,2,value);
        }
    }
    hsv_to_rgb(img);

    return img;
}
