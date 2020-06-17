#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "image.h"
#include "args.h"
#include "test.h"
int main()
{
    //run_tests();
    image img = load_image("data/Rainier1.png");
    detect_and_draw_corners(img,2,50,3);
    image corner = load_image("figs/corners.jpg");
    image sub = sub_image(img,corner);
    clamp_image(sub);
    save_image(sub,"editable_dog");
//    clock_t start, end;
//    float cpu_time_used;

//    image img = load_image("data/dog.jpg");

//    start = clock();
//    image gaussian = make_gaussian_filter(2);
//    image smoothed_2d = convolve_image(img,gaussian,1);
//    end = clock();
//    cpu_time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
//    printf("time for 2D Gaussian = %.6f\n",cpu_time_used);

//    start = clock();
//    image smoothed_1d = smooth_image(img,2);
//    end = clock();
//    cpu_time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
//    printf("time for 1D Gaussian = %.6f\n",cpu_time_used);

//    image sub = sub_image(smoothed_1d,smoothed_2d);

//    save_image(sub,"editable_dog");

//    image img = load_image("data/dog.jpg");

//    image structure = structure_matrix(img,2);

//    image cornerness = cornerness_response(structure);
//    feature_normalize(cornerness);

//    save_image(cornerness,"editable_dog");

//    image img = load_image("data/dog.jpg");

//    image smooth = smooth_image(img,2);

//    save_image(smooth,"editable_dog");

//    image img = load_image("data/dog.jpg");

//    image matrix = structure_matrix(img,2);
//    feature_normalize(matrix);

//    save_image(matrix,"editable_dog");

    //    image im = load_image("data/dog.jpg"); //data/dog.jpg
    //    //image theta = load_image("figs/theta.png");
    ////    image * sobel = sobel_image(im);

    ////    feature_normalize(sobel[0]);
    ////    feature_normalize(sobel[1]);

    ////    rgb_to_hsv(im);
    ////    hsv_to_rgb(im);


    //    image gaussian = make_gaussian_filter(3);
    //    image smooth = convolve_image(im,gaussian,1);
    //    image color = colorize_sobel(smooth);

    ////    image sub = sub_image(sobel[1],theta);
    ////    clamp_image(sub);

    //    save_image(color, "editable_dog");

    // to band a frequencies in the image , subtract smoothed images with difference sigma
    //    image img = load_image("data/dog.jpg"); //data/dog.jpg
    //    image g0 = make_gaussian_filter(1);
    //    image g1 = make_gaussian_filter(2);
    //    image img_0 = convolve_image(img,g0,1);
    //    image img_1 = convolve_image(img,g1,1);
    //    image diff = sub_image(img_1,img_0);
    //    save_image(diff, "editable_dog");

    //    image im = load_image("data/dog.jpg"); //data/dog.jpg
    //    image f = make_gaussian_filter(2);
    //    image lfreq = convolve_image(im, f, 1);
    //    image hfreq = sub_image(im,lfreq);
    //    clamp_image(hfreq);
    //    image reconstruct = add_image(lfreq,hfreq);
    //    save_image(lfreq, "low-frequency");
    //    save_image(hfreq, "high-frequency");
    //    save_image(reconstruct, "reconstruct");

//    image im = load_image("data/dog.jpg");
//    image hp = make_highpass_filter();
//    image im_filtered = convolve_image(im,hp,0);
//    clamp_image(im_filtered);
//    image high = load_image("figs/dog-highpass.png");
//    image temp = sub_image(im_filtered,high);
//    save_image(im_filtered, "editable_dog");
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
