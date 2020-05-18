#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "args.h"


int main()
{
    image img = load_image("data/dots.png");
    image image = bilinear_resize(img,img.w*100,img.h*100);
    save_image(image,"editable_dog");
    system("shotwell editable_dog.jpg");

    //printf("c_x = %.6f, m_x = %.6f \n", c_x,m_x);

    return 0;
}
