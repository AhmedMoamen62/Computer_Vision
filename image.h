#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include "matrix.h"
#define TWOPI 6.2831853

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

// DO NOT CHANGE THIS FILE

typedef struct{
    int w,h,c;
    float *data;
} image;

// A 2d point.
// float x, y: the coordinates of the point.
typedef struct{
    float x, y;
} point;

// A descriptor for a point in an image.
// point p: x,y coordinates of the image pixel.
// int n: the number of floating point values in the descriptor.
// float *data: the descriptor for the pixel.
typedef struct{
    point p;
    int n;
    float *data;
} descriptor;

// A match between two points in an image.
// point p, q: x,y coordinates of the two matching pixels.
// int ai, bi: indexes in the descriptor array. For eliminating duplicates.
// float distance: the distance between the descriptors for the points.
typedef struct{
    point p, q;
    int ai, bi;
    float distance;
} match;


// Maximum and Minimum
int three_max(float a, float b, float c);
int three_min(float a, float b, float c);
int four_max(float a, float b, float c, float d);
int four_min(float a, float b, float c, float d);
float four_max_value(float a, float b, float c, float d);
float four_min_value(float a, float b, float c, float d);

// Basic operations
int clip_axis(int axis,int min,int max);
float get_pixel_padding(image im, int x, int y, int c);
float get_pixel(image im, int x, int y, int c);
void set_pixel(image im, int x, int y, int c, float v);
image copy_image(image im);
image rgb_to_grayscale(image im);
image average_image(image im);
image grayscale_to_rgb(image im, float r, float g, float b);
void rgb_to_hsv(image im);
void hsv_to_rgb(image im);
void shift_image(image im, int c, float v);
void scale_image(image im, int c, float v);
void clamp_image(image im);
void set_channel(image out,int ch_out,image in, int ch_in);
image get_channel(image im, int c);
int same_image(image a, image b);
image sub_image(image a, image b);
image add_image(image a, image b);


// Loading and saving
image make_image(int w, int h, int c);
image load_image(char *filename);
void save_image(image im, const char *name);
void save_png(image im, const char *name);
void free_image(image im);

// Resizing
float nn_interpolate(image im, float x, float y, int c);
image nn_resize(image im, int w, int h);
float bilinear_interpolate(image im, float x, float y, int c);
image bilinear_resize(image im, int w, int h);

// Filtering
image convolve_image(image im, image filter, int preserve);
float convolve_1_in_1(int start_row_img,int start_col_img,int ch_img,int ch_kernel,image img,image kernel);
image calculate_avg(image img,image im,image filter,int mode);
image make_box_filter(int w);
image make_highpass_filter();
image make_sharpen_filter();
image make_emboss_filter();
image make_gaussian_filter(float sigma);
image make_1d_gaussian(float sigma);
image make_gx_filter();
image make_gy_filter();
void l1_normalize(image im);
void feature_normalize(image im);
void threshold_image(image im, float thresh);
image *sobel_image(image im);
image colorize_sobel(image im);
image image_transpose(image img);
image make_integral_image(image im);
image box_filter_image(image im, int s);
image smooth_image(image im, float sigma);

// Harris and Stitching
image structure_matrix(image im, float sigma);
image cornerness_response(image S);
image nms_image(image im, int w);
int count_responses(image img,float thresh);
float check_window_maximum(image img,int ch,int start_row_img,int start_col_img,int window_size,float value);
void free_descriptors(descriptor *d, int n);
image cylindrical_project(image im, float f);
void mark_corners(image im, descriptor *d, int n);
image find_and_draw_matches(image a, image b, float sigma, float thresh, int nms);
void detect_and_draw_corners(image im, float sigma, float thresh, int nms);
int model_inliers(matrix H, match *m, int n, float thresh);
void swap_matches(match *m, int i, int j);
image combine_images(image a, image b, matrix H);
match *match_descriptors(descriptor *a, int an, descriptor *b, int bn, int *mn);
descriptor *harris_corner_detector(image im, float sigma, float thresh, int nms, int *n);
image panorama_image(image a, image b, float sigma, float thresh, int nms, float inlier_thresh, int iters, int cutoff);

// Optical Flow
image optical_flow_images(image im, image prev, int smooth, int stride);
void optical_flow_webcam(int smooth, int stride, int div,int camera_index);
void draw_flow(image im, image v, float scale);

#ifndef __cplusplus
    #ifdef OPENCV
        #include "opencv2/highgui/highgui_c.h"
        #include "opencv2/imgproc/imgproc_c.h"
        #include "opencv2/core/version.hpp"
        #if CV_MAJOR_VERSION == 3
            #include "opencv2/videoio/videoio_c.h"
            #include "opencv2/imgcodecs/imgcodecs_c.h"
        #endif
        image get_image_from_stream(CvCapture *cap);
        int show_image(image im, const char *name, int ms);
    #endif
#endif

// Machine Learning

typedef enum{LINEAR, LOGISTIC, RELU, LRELU, SOFTMAX} ACTIVATION;

typedef struct {
    matrix in;              // Saved input to a layer
    matrix w;               // Current weights for a layer
    matrix dw;              // Current weight updates
    matrix v;               // Past weight updates (for use with momentum)
    matrix out;             // Saved output from the layer
    ACTIVATION activation;  // Activation the layer uses
} layer;

typedef struct{
    matrix X;
    matrix y;
} data;

typedef struct {
    layer *layers;
    int n;
} model;

data load_classification_data(char *images, char *label_file, int bias);
void free_data(data d);
data random_batch(data d, int n);
char *fgetl(FILE *fp);

#endif
