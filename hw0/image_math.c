#include "image_math.h"

int three_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? 0 : 2) : ( (b > c) ? 1 : 2) ;
}
int three_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? 0 : 2) : ( (b < c) ? 1 : 2) ;
}
