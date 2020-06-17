#include <math.h>
#include "image.h"
#include "image_math.h"

float nn_interpolate(image im, float x, float y, int c)
{
    // TODO Fill in
    int neighboor_x = round(x);
    int neighboor_y = round(y);

    float pixel_value = get_pixel(im, neighboor_x, neighboor_y, c);

    return pixel_value;
}

image nn_resize(image im, int w, int h)
{
    // TODO Fill in (also fix that first line)
    image img = make_image(w,h,im.c);
    // calculate m and c parameter of the first order euation
    float m_x,c_x,m_y,c_y;

    m_x = (float)im.w/w;
    c_x = m_x*0.5 - 0.5;

    m_y = (float)im.h/h;
    c_y = m_y*0.5 - 0.5;

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
    c_x = m_x*0.5 - 0.5;

    m_y = (float)im.h/h;
    c_y = m_y*0.5 - 0.5;

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

