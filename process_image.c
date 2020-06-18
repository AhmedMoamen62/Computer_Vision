#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"

int clip_axis(int axis,int min,int max)
{
    if(axis > max)
    {
        return max;
    }
    if(axis < min)
    {
        return min;
    }
    return axis;
}

float get_pixel(image im, int x, int y, int c)
{
    x = clip_axis(x,0,im.w - 1);
    y = clip_axis(y,0,im.h - 1);
    c = clip_axis(c,0,im.c - 1);
    int index = im.w*im.h*c + im.w*y + x;
    return im.data[index];
}

void set_pixel(image im, int x, int y, int c, float v)
{
    // TODO Fill this in
    if(x >= 0 && y >= 0 && x < im.w && y < im.h)
    {
        int index = im.w*im.h*c + im.w*y + x;
        im.data[index] = v;
    }
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
    for(int row = 0 ; row < copy.h ; row++)
    {
        for(int col = 0; col < copy.w ; col++)
        {
            for(int  ch = 0 ; ch < copy.c ; ch++)
            {
                float pixel_value = get_pixel(im,col,row,ch);
                set_pixel(copy,col,row,ch,pixel_value);
            }
        }
    }
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    // TODO Fill this in
    for(int row = 0 ; row < gray.h ; row++)
    {
        for(int col = 0; col < gray.w ; col++)
        {
            float pixel_value = 0.299*get_pixel(im,col,row,0) + 0.587*get_pixel(im,col,row,1) + 0.114*get_pixel(im,col,row,2);
            set_pixel(gray,col,row,0,pixel_value);
        }
    }
    return gray;
}

image average_image(image im)
{
    assert(im.c == 3);
    image average = make_image(im.w, im.h, 1);
    // TODO Fill this in
    for(int row = 0 ; row < average.h ; row++)
    {
        for(int col = 0; col < average.w ; col++)
        {
            float pixel_value = get_pixel(im,col,row,0) + get_pixel(im,col,row,1) + get_pixel(im,col,row,2);
            set_pixel(average,col,row,0,pixel_value/3.0);
        }
    }
    return average;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in
    for(int row = 0 ; row < im.h ; row++)
    {
        for(int col = 0; col < im.w ; col++)
        {
            float pixel_value = get_pixel(im,col,row,c)+v;
            set_pixel(im,col,row,c,pixel_value);
        }
    }
}

void scale_image(image im, int c, float v)
{
    // TODO Fill this in
    for(int row = 0 ; row < im.h ; row++)
    {
        for(int col = 0; col < im.w ; col++)
        {
            float pixel_value = get_pixel(im,col,row,c)*v;
            set_pixel(im,col,row,c,pixel_value);
        }
    }
}


void clamp_image(image im)
{
    // TODO Fill this in
    for(int row = 0 ; row < im.h ; row++)
    {
        for(int col = 0; col < im.w ; col++)
        {
            for(int ch = 0; ch <im.c ; ch++)
            {
                float pixel_value = get_pixel(im,col,row,ch);
                if(pixel_value < 0)
                {
                    set_pixel(im,col,row,ch,0);
                }
                else if(pixel_value > 1)
                {
                    set_pixel(im,col,row,ch,1);
                }
            }
        }
    }
}


void set_channel(image out,int ch_out,image in, int ch_in)
{
    assert(out.w == in.w && out.h == in.h);

    for(int row = 0 ; row < out.h; row++)
    {
        for(int col = 0 ; col < out.w ; col++)
        {
            set_pixel(out,col,row,ch_out,get_pixel(in,col,row,ch_in));
        }
    }
}


image get_channel(image im, int c)
{
    image img = make_image(im.w,im.h,1);
    for(int row = 0 ; row < img.h; row++)
    {
        for(int col = 0 ; col < img.w ; col++)
        {
            set_pixel(img,col,row,0,get_pixel(im,col,row,c));
        }
    }

    return img;
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
    for(int row = 0 ; row < im.h ; row++)
    {
        for(int col = 0; col < im.w ; col++)
        {
            float red = get_pixel(im,col,row,0);
            float green = get_pixel(im,col,row,1);
            float blue = get_pixel(im,col,row,2);

            float value = three_way_max(red,green,blue);
            set_pixel(im,col,row,2,value);

            float difference = value - three_way_min(red,green,blue);

            if(value != 0)
            {
                float saturation = difference/value;
                set_pixel(im,col,row,1,saturation);
            }
            else
            {
                set_pixel(im,col,row,1,0);
            }
            if(difference > 0)
            {
                int index = three_max(red,green,blue);
                float hue;
                if(index == 0) // red
                {
                    hue = (green-blue)/difference;
                }
                else if(index == 1) // green
                {
                    hue = ((blue-red)/difference) + 2;
                }
                else if(index == 2) // blue
                {
                    hue = ((red-green)/difference) + 4;
                }
                if(hue < 0)
                {
                    set_pixel(im,col,row,0,(hue/6) + 1);
                }
                else
                {
                    set_pixel(im,col,row,0,hue/6);
                }
            }
            else
            {
                set_pixel(im,col,row,0,0);
            }
        }
    }
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
    for(int row = 0 ; row < im.h ; row++)
    {
        for(int col = 0; col < im.w ; col++)
        {
            float value = get_pixel(im,col,row,2);
            float saturation = get_pixel(im,col,row,1);
            float hue = get_pixel(im,col,row,0);

            float hue_deg = hue*6;
            float difference = saturation*value;
            float min = value - difference;

            if(hue_deg > 1 && hue_deg <= 3) // green
            {
                set_pixel(im,col,row,1,value);
                if(hue_deg <= 2)
                {
                    float blue = min;
                    set_pixel(im,col,row,2,blue);
                    float red = blue - difference*(hue_deg - 2);
                    set_pixel(im,col,row,0,red);
                }
                else
                {
                    float red = min;
                    set_pixel(im,col,row,0,red);
                    float blue = red + difference*(hue_deg - 2);
                    set_pixel(im,col,row,2,blue);
                }
            }
            else if(hue_deg > 3 && hue_deg <= 5) // blue
            {
                set_pixel(im,col,row,2,value);
                if(hue_deg <= 4)
                {
                    float red = min;
                    set_pixel(im,col,row,0,red);
                    float green = red - difference*(hue_deg - 4);
                    set_pixel(im,col,row,1,green);
                }
                else
                {
                    float green = min;
                    set_pixel(im,col,row,1,green);
                    float red = green + difference*(hue_deg - 4);
                    set_pixel(im,col,row,0,red);
                }
            }
            else if(hue_deg > 5 || hue_deg <= 1) // red
            {
                set_pixel(im,col,row,0,value);
                if(hue_deg <= 1)
                {
                    float blue = min;
                    set_pixel(im,col,row,2,blue);
                    float green = blue + difference*hue_deg;
                    set_pixel(im,col,row,1,green);
                }
                else
                {
                    float green = min;
                    set_pixel(im,col,row,1,green);
                    float blue = green - difference*(hue_deg-6);
                    set_pixel(im,col,row,2,blue);
                }
            }
        }
    }
}

int three_max(float a, float b, float c)
{
    float arr[3];

    arr[0] = a;
    arr[1] = b;
    arr[2] = c;

    int max = 0;
    for(int i = 1; i < 3 ; i++)
    {
        if(arr[i] > arr[max])
        {
            max = i;
        }
    }
    return max;
}
int three_min(float a, float b, float c)
{
    float arr[3];

    arr[0] = a;
    arr[1] = b;
    arr[2] = c;

    int min = 0;
    for(int i = 1; i < 3 ; i++)
    {
        if(arr[i] < arr[min])
        {
            min = i;
        }
    }
    return min;
}
int four_max(float a, float b, float c, float d)
{
    float arr[4];

    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;

    int max = 0;
    for(int i = 1; i < 4 ; i++)
    {
        if(arr[i] > arr[max])
        {
            max = i;
        }
    }
    return max;
}
int four_min(float a, float b, float c, float d)
{
    float arr[4];

    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;

    int min = 0;
    for(int i = 1; i < 4 ; i++)
    {
        if(arr[i] < arr[min])
        {
            min = i;
        }
    }
    return min;
}

float four_max_value(float a, float b, float c, float d)
{
    float arr[4];

    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;

    float max = arr[0];
    for(int i = 1; i < 4 ; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}
float four_min_value(float a, float b, float c, float d)
{
    float arr[4];

    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;

    float min = arr[0];
    for(int i = 1; i < 4 ; i++)
    {
        if(arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}
