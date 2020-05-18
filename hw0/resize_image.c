#include <math.h>
#include "image.h"

float nn_interpolate(image im, float x, float y, int c)
{
    // TODO Fill in
    float pixel_val;
    /*
    int x_right = ceil(x);
    int x_left = floor(x);
    int y_bottom = ceil(y);
    int y_top = floor(y);
    */

    return pixel_val;
}

image nn_resize(image im, int w, int h)
{
    // TODO Fill in (also fix that first line)
    image img = make_image(w,h,im.c);
    float m_x = im.w/w;
    float c_x = m_x*(w - 0.5) - im.w + 0.5;
    float m_y = im.h/h;
    float c_y = m_y*(h - 0.5) - im.h + 0.5;
    for(int row = 0 ; row < h ; row++)
    {
        for(int col = 0; col < w ; col++)
        {
            float x = m_x*col + c_x;
            float y = m_y*row + c_y;
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

    // check if the pixel is out of the old image size
    if(y <= 0 && x <= 0)
    {
        pixel_val = get_pixel(im,0,0,c);
        return pixel_val;
    }

    if(y >= im.h && x >= im.w)
    {
        pixel_val = get_pixel(im,im.w - 1,im.h - 1,c);
        return pixel_val;
    }

    // check if the pixel is out of the row edge of the old image size
    if(y <= 0)
    {
        int left = floor(x);
        int right = ceil(x);

        int left_width = x - left;
        int right_width = right - x;

        pixel_val = (get_pixel(im,left,0,c)*right_width)
                  + (get_pixel(im,right,0,c)*left_width);

        return pixel_val;
    }

     if(y >= im.h)
    {
        int left = floor(x);
        int right = ceil(x);

        int left_width = x - left;
        int right_width = right - x;

        pixel_val = (get_pixel(im,left,im.h - 1,c)*right_width)
                  + (get_pixel(im,right,im.h - 1,c)*left_width);

        return pixel_val;
    }

    // check if the pixel is out of the column edge of the old image size
    if(x <= 0)
    {
        int top = floor(y);
        int bottom = ceil(y);

        int top_width = y - top;
        int bottom_width = bottom - y;

        pixel_val = (get_pixel(im,0,top,c)*bottom_width)
                  + (get_pixel(im,0,bottom,c)*top_width);

        return pixel_val;
    }

    if(x >= im.w)
    {
        int top = floor(y);
        int bottom = ceil(y);

        int top_width = y - top;
        int bottom_width = bottom - y;

        pixel_val = (get_pixel(im,im.w - 1,top,c)*bottom_width)
                  + (get_pixel(im,im.w - 1,bottom,c)*top_width);

        return pixel_val;
    }

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
    float m_x = (float)im.w/w;
    float c_x = m_x*(w - 0.5) - im.w + 0.5;
    float m_y = (float)im.h/h;
    float c_y = m_y*(h - 0.5) - im.h + 0.5;

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

