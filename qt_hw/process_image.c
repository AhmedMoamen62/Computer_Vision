#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"
#include "image_math.h"

float get_pixel(image im, int x, int y, int c)
{
    if(x < im.w && y < im.h && x >= 0 && y >= 0)
    {
        int index = im.w*im.h*c + im.w*y + x;
        return im.data[index];
    }
    // if greater than the w and h
    else if(x > im.w && y > im.h)
    {
        int index = im.w*im.h*(c+1);
        return im.data[index];
    }
    // if less than the w and h
    else if(x < 0 && y < 0)
    {
        int index = im.w*im.h*c;
        return im.data[index];
    }
    else if(x < 0 && y < im.h)
    {
        int index = im.w*im.h*c + im.w*y;
        return im.data[index];
    }
    else if(x >= im.w && y < im.h)
    {
        int index = im.w*im.h*c + im.w*(y+1) - 1;
        return im.data[index];
    }
    else if(x < im.w && y < 0)
    {
        int index = im.w*im.h*c + x;
        return im.data[index];
    }
    else if(x < im.w && y >= im.h)
    {
        int index = im.w*im.h*c + im.w*(im.h-1) + x;
        return im.data[index];
    }
}

void set_pixel(image im, int x, int y, int c, float v)
{
    // TODO Fill this in
    if(x < im.w && y < im.h)
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
            float pixel_value = get_pixel(im,col,row,0);
            set_pixel(copy,col,row,0,pixel_value);

            pixel_value = get_pixel(im,col,row,1);
            set_pixel(copy,col,row,1,pixel_value);

            pixel_value = get_pixel(im,col,row,2);
            set_pixel(copy,col,row,2,pixel_value);
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
            float red = get_pixel(im,col,row,0);
            float green = get_pixel(im,col,row,1);
            float blue = get_pixel(im,col,row,2);
            if(red > 1)
            {
                set_pixel(im,col,row,0,1);
            }
            if(red < 0)
            {
                set_pixel(im,col,row,0,0);
            }
            if(green > 1)
            {
                set_pixel(im,col,row,1,1);
            }
            if(green < 0)
            {
                set_pixel(im,col,row,1,0);
            }
            if(blue > 1)
            {
                set_pixel(im,col,row,2,1);
            }
            if(blue < 0)
            {
                set_pixel(im,col,row,2,0);
            }
        }
    }
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
            if(hue_deg > 1 && hue_deg <= 3) // green
            {
                set_pixel(im,col,row,1,value);
                if(hue_deg <= 2)
                {
                    float blue = value - difference;
                    set_pixel(im,col,row,2,blue);
                    float red = blue - difference*(hue_deg - 2);
                    set_pixel(im,col,row,0,red);
                }
                else
                {
                    float red = value - difference;
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
                    float red = value - difference;
                    set_pixel(im,col,row,0,red);
                    float green = red - difference*(hue_deg - 4);
                    set_pixel(im,col,row,1,green);
                }
                else
                {
                    float green = value - difference;
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
                    float blue = value - difference;
                    set_pixel(im,col,row,2,blue);
                    float green = blue + difference*hue_deg;
                    set_pixel(im,col,row,1,green);
                }
                else
                {
                    float green = value - difference;
                    set_pixel(im,col,row,1,green);
                    float blue = green - difference*(hue_deg-6);
                    set_pixel(im,col,row,2,blue);
                }
            }
        }
    }
}
