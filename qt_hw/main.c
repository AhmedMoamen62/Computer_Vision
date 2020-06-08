#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"
#include "args.h"

int main()
{

    image img = load_image("data/dog.jpg"); //data/dog.jpg
//    image f = make_gaussian_filter(2);
//    image temp = convolve_image(img,f,1);
    image temp = nn_resize(img,img.w/7,img.h/7);
    save_image(temp, "editable_dog");

//    for(int row = 390 ; row < 394; row++)
//    {
//        for(int col = 206 ; col < 209 ; col++)
//        {
//            if(im.c == 3)
//            {
//                int red = get_pixel(im,col,row,0)*255;
//                int green = get_pixel(im,col,row,1)*255;
//                int blue = get_pixel(im,col,row,2)*255;
//                printf("x = %d , y = %d , red = %d , green = %d , blue = %d\n",col+1,row+1,red,green,blue);
//            }
//            else
//            {
//                int gray = get_pixel(im,col,row,0)*255;
//                printf("x = %d , y = %d , gray = %d\n",col+1,row+1,gray);
//            }
//        }
//    }

    system("shotwell editable_dog.jpg");

    return 0;
}
