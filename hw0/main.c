#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "args.h"


int main()
{
    image img = load_image("data/dog.jpg");
    image gray = rgb_to_grayscale(img);
    save_image(gray,"editable_dog");
    system("shotwell editable_dog.jpg");
    return 0;
}
