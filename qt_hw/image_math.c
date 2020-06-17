#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image_math.h"
int three_max(float a, float b, float c)
{
    float arr[3];

    arr[0] = a;
    arr[1] = b;
    arr[2] = c;

    int max = 0;
    for(int i = 1; i < 3 ; i++)
    {
        if(arr[i] > arr[max])
        {
            max = i;
        }
    }
    return max;
}
int three_min(float a, float b, float c)
{
    float arr[3];

    arr[0] = a;
    arr[1] = b;
    arr[2] = c;

    int min = 0;
    for(int i = 1; i < 3 ; i++)
    {
        if(arr[i] < arr[min])
        {
            min = i;
        }
    }
    return min;
}
int four_max(float a, float b, float c, float d)
{
    float arr[4];

    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;

    int max = 0;
    for(int i = 1; i < 4 ; i++)
    {
        if(arr[i] > arr[max])
        {
            max = i;
        }
    }
    return max;
}
int four_min(float a, float b, float c, float d)
{
    float arr[4];

    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;

    int min = 0;
    for(int i = 1; i < 4 ; i++)
    {
        if(arr[i] < arr[min])
        {
            min = i;
        }
    }
    return min;
}

float four_max_value(float a, float b, float c, float d)
{
    float arr[4];

    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;

    float max = arr[0];
    for(int i = 1; i < 4 ; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}
float four_min_value(float a, float b, float c, float d)
{
    float arr[4];

    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
    arr[3] = d;

    float min = arr[0];
    for(int i = 1; i < 4 ; i++)
    {
        if(arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}
