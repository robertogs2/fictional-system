#include <converters.h>

struct YUV_Color YUVfromRGB(double R, double G, double B)
{
  struct YUV_Color color;
  color.Y = (int) floor(0.299 * R + 0.587 * G + 0.114 * B);
  color.U = (int) floor(-0.14713 * R - 0.28886 * G + 0.436 * B);
  color.V = (int) floor(0.615 * R - 0.51499 * G - 0.10001 * B);
  //printf("Y:%d, U:%d, V:%d\n",color.Y, color.U, color.V);
  return color;
}

struct RGB_Color RGBfromYUV(double Y, double U, double V){
  struct RGB_Color color;
  color.R = floor(Y             		+ 1.13983 * V);
  color.G = floor(Y - 0.39465 * U 		- 0.58060 * V);
  color.B = floor(Y + 2.03211 * U);
  //if(color.B < 0) color.B = 0;
  //printf("R:%d, G:%d, B:%d\n",color.R, color.G, color.B);
  return color;
}

void print_array(int a[], int size){
  printf("[");
  for(int i = 0; i < size; ++i){
    printf("%d ", a[i]);
  }
  printf("]\n");
}