#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"
#include "args.h"

int main()
{

    image img = load_image("data/dogsmall.jpg"); //data/dog.jpg
    image image = nn_resize(img,img.w*4,img.h*4);
    save_image(image,"editable_dog");
    system("shotwell editable_dog.jpg");

    //printf("D1 = %.6f \n", D1);

    return 0;
}
