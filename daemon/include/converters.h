// converters.h

#ifndef _CONVERTERS_H
#define _CONVERTERS_H

#include <math.h>
#include <stdio.h>

struct RGB_Color{
  int R;
  int G;
  int B;
};

struct YUV_Color{
  int Y;
  int U;
  int V;
};

struct YUV_Color YUVfromRGB(double R, double G, double B);
struct RGB_Color RGBfromYUV(double Y, double U, double V);
void print_array(int a[], int size);

#endif // _CONVERTERS_H
