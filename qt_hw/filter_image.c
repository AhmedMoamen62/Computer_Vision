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

            float kernel_value_1 = get_pixel(kernel,kernel_center_row,start_col_kernel,ch_kernel);
            float image_value_1 = get_pixel(img,start_col_img + kernel_center_row,start_row_img + start_col_kernel,ch_img);

            float kernel_value_2 = get_pixel(kernel,kernel_center_row,opposite_col,ch_kernel);
            float image_value_2 = get_pixel(img,start_col_img + kernel_center_row,start_row_img + opposite_col,ch_img);

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

    for(int row = 0 ; row < img.h ; row++)
    {
        int start_row_img = row - filter.h/2;
        for(int col = 0; col < img.w ; col++)
        {
            int start_col_img = col - filter.w/2;
            for(int ch = 0 ; ch < img.c ; ch++)
            {
                if(mode == 0)
                {
                    float pixel_value = convolve_1_in_1(start_row_img,start_col_img,ch,0,im,filter);
                    if(pixel_value < 0)
                    {
                        set_pixel(img,col,row,ch,0);
                    }
                    else if (pixel_value > 1)
                    {
                        set_pixel(img,col,row,ch,1);
                    }
                    else
                    {
                        set_pixel(img,col,row,ch,pixel_value);
                    }
                }
                else
                {
                    float pixel_value = convolve_1_in_1(start_row_img,start_col_img,ch,ch,im,filter);
                    if(pixel_value < 0)
                    {
                        set_pixel(img,col,row,ch,0);
                    }
                    else if (pixel_value > 1)
                    {
                        set_pixel(img,col,row,ch,1);
                    }
                    else
                    {
                        set_pixel(img,col,row,ch,pixel_value);
                    }
                }
            }
            //            float red = get_pixel(img,col,row,0);
            //            float green = get_pixel(img,col,row,1);
            //            float blue = get_pixel(img,col,row,2);
            //            printf("x = %d , y = %d , red = %.6f , green = %.6f , blue = %.6f\n",col,row,red,green,blue);
        }
    }
    return img;
}

void l1_normalize(image im)
{
    // TODO
    float weight = 1.0/(im.w*im.h);
    for(int row = 0 ; row < im.h ; row++)
    {
        for(int col = 0; col < im.w ; col++)
        {
            for(int ch = 0 ; ch < im.c ; ch++)
            {
                set_pixel(im,col,row,ch,weight);
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

image convolve_image(image im, image filter, int preserve)
{
    // TODO
    assert(im.c == filter.c || filter.c == 1);
    image img = make_image(im.w,im.h,im.c);
    if(filter.c == 1)
    {
        img = calculate_avg(img,im,filter,0);
        if(preserve != 1)
        {
            img = average_image(img);
        }
    }
    else if(im.c == filter.c)
    {
        img = calculate_avg(img,im,filter,1);
        if(preserve != 1)
        {
            img = average_image(img);
        }
    }
    return img;
}

image make_highpass_filter()
{
    // TODO
    image img = make_image(3,3,1);

    float weight = 3;

    set_pixel(img,1,0,0,-1*weight);
    set_pixel(img,0,1,0,-1*weight);
    set_pixel(img,2,1,0,-1*weight);
    set_pixel(img,1,2,0,-1*weight);
    set_pixel(img,1,1,0,4*weight);

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
// Answer: sharpen and emboss

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: TODO

image make_gaussian_filter(float sigma)
{
    // TODO
    return make_image(1,1,1);
}

image add_image(image a, image b)
{
    // TODO
    return make_image(1,1,1);
}

image sub_image(image a, image b)
{
    // TODO
    return make_image(1,1,1);
}

image make_gx_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_gy_filter()
{
    // TODO
    return make_image(1,1,1);
}

void feature_normalize(image im)
{
    // TODO
}

image *sobel_image(image im)
{
    // TODO
    return calloc(2, sizeof(image));
}

image colorize_sobel(image im)
{
    // TODO
    return make_image(1,1,1);
}
