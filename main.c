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

//    image a = load_image("data/dog_a.jpg");
//    image b = load_image("data/dog_b.jpg");
//    image flow = optical_flow_images(b, a, 15, 8);
//    draw_flow(a, flow, 8);
//    save_image(a, "lines");

//    optical_flow_webcam(15,4,8,0);

    //    image img = load_image("data/dog.jpg");
    //    image box = box_filter_image(img,7);
    //    save_image(box,"test_hw");

    //    image im1 = load_image("data/helens4.jpg");
    //    image im2 = load_image("data/helens5.jpg");

    //    image pan = panorama_image(im1, im2,2,2,3,2,10000,30);
    //    save_image(pan, "helens_panorama_1");

    //        image im1 = load_image("data/helens1.jpg");
    //        image im2 = load_image("data/helens2.jpg");
    //        image im3 = load_image("data/helens3.jpg");
    //        image im4 = load_image("data/helens4.jpg");
    //        image im5 = load_image("data/helens5.jpg");
    //        image im6 = load_image("data/helens6.jpg");

    //        im1 = cylindrical_project(im1, 1200);
    //        im2 = cylindrical_project(im2, 1200);
    //        im3 = cylindrical_project(im3, 1200);
    //        im4 = cylindrical_project(im4, 1200);
    //        im5 = cylindrical_project(im5, 1200);
    //        im6 = cylindrical_project(im6, 1200);

    //        save_image(im1, "cylindrical_projection");

    //        image pan = panorama_image(im1, im2,2,2,3,3,50000,30);
    //        save_image(pan, "field_panorama_1");
    //        image pan2 = panorama_image(pan, im3,2,2,3,3,50000,30);
    //        save_image(pan2, "field_panorama_4");
    //        image pan3 = panorama_image(pan2, im4,2,2,3,3,50000,30);
    //        save_image(pan3, "field_panorama_5");

    //    image im1 = load_image("data/field1.jpg");
    //    image im2 = load_image("data/field2.jpg");
    //    image im3 = load_image("data/field3.jpg");
    //    image im4 = load_image("data/field4.jpg");
    //    image im5 = load_image("data/field5.jpg");
    //    image im6 = load_image("data/field6.jpg");
    //    image im7 = load_image("data/field7.jpg");
    //    image im8 = load_image("data/field8.jpg");

    //    im1 = cylindrical_project(im1, 1200);
    //    im2 = cylindrical_project(im2, 1200);
    //    im3 = cylindrical_project(im3, 1200);
    //    im4 = cylindrical_project(im4, 1200);
    //    im5 = cylindrical_project(im5, 1200);
    //    im6 = cylindrical_project(im6, 1200);
    //    im7 = cylindrical_project(im7, 1200);
    //    im8 = cylindrical_project(im8, 1200);
    //    save_image(im1, "cylindrical_projection");

    //    image pan = panorama_image(im5, im6,2,2,3,3,50000,30);
    //    save_image(pan, "field_panorama_1");
    //    image pan2 = panorama_image(pan, im7,2,2,3,3,50000,30);
    //    save_image(pan2, "field_panorama_2");
    //    image pan3 = panorama_image(pan2, im8,2,2,3,3,50000,30);
    //    save_image(pan3, "field_panorama_3");
    //    image pan4 = panorama_image(pan3, im4,2,2,3,3,50000,30);
    //    save_image(pan4, "field_panorama_4");
    //    image pan5 = panorama_image(pan4, im3,2,2,3,3,50000,30);
    //    save_image(pan5, "field_panorama_5");

    //        image im1 = load_image("data/sun1.jpg");
    //        image im2 = load_image("data/sun2.jpg");
    //        image im3 = load_image("data/sun3.jpg");
    //        image im4 = load_image("data/sun4.jpg");
    //        image im5 = load_image("data/sun5.jpg");
    //        image pan = panorama_image(im1,im2,2,2,3,2,10000,30);
    //        save_image(pan, "rainier_panorama_1");
    //        image pan2 = panorama_image(pan,im3,2,2,3,2,10000,30);
    //        save_image(pan2, "rainier_panorama_2");
    //        image pan3 = panorama_image(pan2,im4,2,2,3,2,10000,30);
    //        save_image(pan3, "rainier_panorama_3");
    //        image pan4 = panorama_image(pan3,im5,2,2,3,2,10000,30);
    //        save_image(pan4, "rainier_panorama_4");

    //        image im1 = load_image("data/helens1.jpg");
    //        image im2 = load_image("data/helens2.jpg");
    //        image im3 = load_image("data/helens3.jpg");
    //        image im4 = load_image("data/helens4.jpg");
    //        image im5 = load_image("data/helens5.jpg");
    //        image im6 = load_image("data/helens6.jpg");
    //        image pan = panorama_image(im1,im2,2,2,3,2,50000,30);
    //        save_image(pan, "rainier_panorama_1");
    //        image pan2 = panorama_image(pan,im3,2,2,3,2,50000,30);
    //        save_image(pan2, "rainier_panorama_2");
    //        image pan3 = panorama_image(pan2,im4,2,2,3,2,50000,30);
    //        save_image(pan3, "rainier_panorama_3");
    //        image pan4 = panorama_image(pan3,im5,2,2,3,2,50000,30);
    //        save_image(pan4, "rainier_panorama_4");
    //        image pan5 = panorama_image(pan4,im6,2,2,3,2,50000,30);
    //        save_image(pan5, "rainier_panorama_5");


    //        image im1 = load_image("data/Rainier1.png");
    //        image im2 = load_image("data/Rainier2.png");
    //        image im3 = load_image("data/Rainier3.png");
    //        image im4 = load_image("data/Rainier4.png");
    //        image im5 = load_image("data/Rainier5.png");
    //        image im6 = load_image("data/Rainier6.png");
    //        image pan = panorama_image(im1, im2,2,5,3,2,10000,30);
    //        save_image(pan, "rainier_panorama_1");
    //        image pan2 = panorama_image(pan, im5,2,5,3,2,10000,30);
    //        save_image(pan2, "rainier_panorama_2");
    //        image pan3 = panorama_image(pan2, im6,2,5,3,2,10000,30);
    //        save_image(pan3, "rainier_panorama_3");
    //        image pan4 = panorama_image(pan3, im3,2,5,3,2,10000,30);
    //        save_image(pan4, "rainier_panorama_4");
    //        image pan5 = panorama_image(pan4, im4,2,5,3,2,10000,30);
    //        save_image(pan5, "rainier_panorama_5");

    //    image img_1 = load_image("data/Rainier1.png");
    //    image img_2 = load_image("data/Rainier2.png");
    ////    image matches = find_and_draw_matches(img_1,img_2,2,50,3);
    ////    save_image(matches,"matches_edit");

    ////    image matches_edit = load_image("matches_edit.jpg");
    ////    image matches_original = load_image("figs/matches.jpg");

    ////    image sub = sub_image(matches_edit,matches_original);
    ////    clamp_image(sub);
    //    image panorama = panorama_image(img_1,img_2,2,50,3,2,10000,30);

    ////    image inliers_o = load_image("figs/inliers.jpg");
    ////    image inliers = load_image("inliers.jpg");
    ////    image in_diff = sub_image(inliers,inliers_o);
    ////    clamp_image(in_diff);
    //    save_image(panorama,"test_hw");

    //    image img = load_image("data/Rainier1.png");
    //    detect_and_draw_corners(img,2,50,3);
    //    save_image(img,"jpg_to_png");
    //    image convert = load_image("jpg_to_png.jpg");
    //    image corner = load_image("figs/corners.jpg");
    //    image sub = sub_image(convert,corner);
    //    //clamp_image(sub);
    //    save_image(sub,"editable_dog");

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

    //system("shotwell lines.jpg");

    return 0;
}
