#include <math.h>
#include "image.h"
#include "image_math.h"

float nn_interpolate(image im, float x, float y, int c)
{
     // TODO Fill in
    int x_right = ceil(x);
    int x_left = floor(x);
    int y_bottom = ceil(y);
    int y_top = floor(y);


    float left_width = x - x_left;
    float right_width = x_right - x;
    float top_width = y - y_top;
    float bottom_width = y_bottom - y;

    float D1 = sqrtf(powf(left_width,2) + powf(top_width,2));
    float D2 = sqrtf(powf(right_width,2) + powf(top_width,2));
    float D3 = sqrtf(powf(left_width,2) + powf(bottom_width,2));
    float D4 = sqrtf(powf(right_width,2) + powf(bottom_width,2));

    int min_index = four_min(D1,D2,D3,D4);

    if(min_index == 0)
    {
        return get_pixel(im,x_left,y_top,c);
    }
    else if(min_index == 1)
    {
        return get_pixel(im,x_right,y_top,c);
    }
    else if(min_index == 2)
    {
        return get_pixel(im,x_left,y_bottom,c);
    }
    else if(min_index == 3)
    {
        return get_pixel(im,x_right,y_bottom,c);
    }
}

image nn_resize(image im, int w, int h)
{
     // TODO Fill in (also fix that first line)
    image img = make_image(w,h,im.c);
    // calculate m and c parameter of the first order euation
    float m_x,c_x,m_y,c_y;

    m_x = (float)im.w/w;
    c_x = m_x*(w - 0.5) - im.w + 0.5;

    m_y = (float)im.h/h;
    c_y = m_y*(h - 0.5) - im.h + 0.5;

    for(int row = 0 ; row < h ; row++)
    {
        // calculate the x, y values for the new scaled image
        float y = m_y*row + c_y;
        for(int col = 0; col < w ; col++)
        {
            float x = m_x*col + c_x;

            for(int ch = 0; ch < im.c ; ch++)
            {
                set_pixel(img,col,row,ch,nn_interpolate(im,x,y,ch));
            }
        }
    }
    return img;
}

float bilinear_interpolate(image im, float x, float y, int c)
{
     // TODO Fill in
    float pixel_val;

    int x_right = ceil(x);
    int x_left = floor(x);
    int y_bottom = ceil(y);
    int y_top = floor(y);

    float A1 = (x - x_left)*(y - y_top);
    float A2 = (x_right - x)*(y - y_top);
    float A3 = (x - x_left)*(y_bottom - y);
    float A4 = (x_right - x)*(y_bottom - y);

    pixel_val = (get_pixel(im,x_right,y_top,c)*A3)
              + (get_pixel(im,x_left,y_top,c)*A4)
              + (get_pixel(im,x_right,y_bottom,c)*A1)
              + (get_pixel(im,x_left,y_bottom,c)*A2);

    return pixel_val;
}

image bilinear_resize(image im, int w, int h)
{
    // TODO Fill in (also fix that first line)
    image img = make_image(w,h,im.c);
    // calculate m and c parameter of the first order euation
    float m_x,c_x,m_y,c_y;

    m_x = (float)im.w/w;
    c_x = m_x*(w - 0.5) - im.w + 0.5;

    m_y = (float)im.h/h;
    c_y = m_y*(h - 0.5) - im.h + 0.5;

    for(int row = 0 ; row < h ; row++)
    {
        // calculate the x, y values for the new scaled image
        float y = m_y*row + c_y;
        for(int col = 0; col < w ; col++)
        {
            float x = m_x*col + c_x;

            for(int ch = 0; ch < im.c ; ch++)
            {
                set_pixel(img,col,row,ch,bilinear_interpolate(im,x,y,ch));
            }
        }
    }
    return img;
}

