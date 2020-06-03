#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853

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
    image img;
    if(im.c == filter.c && preserve == 1)
    {
        img = make_image(im.w,im.h,im.c);
        for(int row = 0 ; row < img.h ; row++)
        {
            for(int col = 0; col < img.w ; col++)
            {
                for(int ch = 0 ; ch < img.c ; ch++)
                {
                    //set_pixel(img,col,row,ch,weight);
                }
            }
        }
    }
    else if(im.c == filter.c)
    {
        img = make_image(im.w,im.h,1);
    }
    else if(filter.c == 1)
    {
        img = make_image(im.w,im.h,im.c);
    }

    return img;
}

image make_highpass_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_sharpen_filter()
{
    // TODO
    return make_image(1,1,1);
}

image make_emboss_filter()
{
    // TODO
    return make_image(1,1,1);
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: TODO

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
