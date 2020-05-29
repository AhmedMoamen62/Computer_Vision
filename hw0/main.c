#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"
#include "args.h"

int main()
{

    image img = load_image("data/dog.jpg"); //data/dog.jpg
    image image = bilinear_resize(img,img.w/7,img.h/7);
    //image image_bilinear = bilinear_resize(image1,64,64);
    save_image(image,"editable_dog");
    system("shotwell editable_dog.jpg");

    //printf("D1 = %.6f \n", D1);

    return 0;
}
