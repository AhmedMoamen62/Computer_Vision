#include <math.h>
#include "image.h"
#include "image_math.h"

float nn_get_nearest_neighbor(image im, float x, float y, int c)
{
    int x_right = ceil(x);
    int x_left = floor(x);
    int y_bottom = ceil(y);
    int y_top = floor(y);


    float left_width = x - x_left;
    float right_width = x_right - x;
    float top_width = y - y_top;
    float bottom_width = y_bottom - y;

    //printf("left_width = %.6f, right_width = %.6f, top_width = %.6f, bottom_width = %.6f \n", left_width,right_width,top_width,bottom_width);

    float D1 = sqrt((float)pow(left_width,2) + (float)pow(top_width,2));
    float D2 = sqrt((float)pow(right_width,2) + (float)pow(top_width,2));
    float D3 = sqrt((float)pow(left_width,2) + (float)pow(bottom_width,2));
    float D4 = sqrt((float)pow(right_width,2) + (float)pow(bottom_width,2));

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

float nn_interpolate(image im, float x, float y, int c)
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

        float left_width = x - left;
        float right_width = right - x;

        if(left_width > right_width)
        {
            return get_pixel(im,right,0,c);
        }

        else
        {
            return get_pixel(im,left,0,c);
        }
    }

    if(y >= im.h)
    {
        int left = floor(x);
        int right = ceil(x);

        float left_width = x - left;
        float right_width = right - x;

        if(left_width > right_width)
        {
            return get_pixel(im,right,im.h - 1,c);
        }

        else
        {
            return get_pixel(im,left,im.h - 1,c);
        }
    }

    // check if the pixel is out of the column edge of the old image size
    if(x <= 0)
    {
        int top = floor(y);
        int bottom = ceil(y);

        float top_width = y - top;
        float bottom_width = bottom - y;

        if(top_width > bottom_width)
        {
            return get_pixel(im,0,bottom,c);
        }

        else
        {
            return get_pixel(im,0,top,c);
        }
    }

    if(x >= im.w)
    {
        int top = floor(y);
        int bottom = ceil(y);

        float top_width = y - top;
        float bottom_width = bottom - y;

        if(top_width > bottom_width)
        {
            return get_pixel(im,im.w - 1,bottom,c);
        }

        else
        {
            return get_pixel(im,im.w - 1,top,c);
        }
    }

    return nn_get_nearest_neighbor(im,x,y,c);
}

image nn_resize(image im, int w, int h)
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

