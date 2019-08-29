#include <stdlib.h>
#include <wand/MagickWand.h>
#include <converters.h>


int main(int argc,char **argv){

  long y;

  MagickBooleanType status;

  MagickPixelPacket pixel;

  MagickWand *yuv_wand, *image_wand;

  PixelIterator *yuv_iterator, *iterator;

  PixelWand **yuv_pixels, **pixels;

  register long x;

  unsigned long width;

  float red, green, blue;

  int histogram_data_equ[256];
  int histogram_data[256];    
  int max_intensity = 255;
  int acc_equ = 0;

  for(int i = 0; i < 256; ++i){
    histogram_data[i] = 0;
  }

  if (argc != 3)
    {
      (void) fprintf(stdout,"Usage: %s image sigmoidal-image\n",argv[0]);
      exit(0);
    }
  /*
    Read an image.
  */
  MagickWandGenesis();
  image_wand=NewMagickWand();
  status=MagickReadImage(image_wand,argv[1]);
  if (status == MagickFalse)
    printf("Error al abrir la imagen.\n");
  yuv_wand=CloneMagickWand(image_wand);


  int m = (int) MagickGetImageHeight(image_wand); 
  int n = (int) MagickGetImageWidth(image_wand);
  int total = m * n;

  short Ys[total];
  short Us[total];
  short Vs[total];
  printf("HERE\n");

  iterator=NewPixelIterator(image_wand);
  if ((iterator == (PixelIterator *) NULL))
    printf("Error con iterador.\n");
  for (y=0; y < (long) MagickGetImageHeight(image_wand); y++)
  {
    pixels=PixelGetNextIteratorRow(iterator,&width);
    if ((pixels == (PixelWand **) NULL))
      break;
    for (x=0; x < (long) width; x++)
    {
      PixelGetMagickColor(pixels[x],&pixel);
      red = PixelGetRed(pixels[x])*255;
      green = PixelGetGreen(pixels[x])*255;
      blue = PixelGetBlue(pixels[x])*255;

      struct YUV_Color yuv_pixel = YUVfromRGB(red, green, blue);
      histogram_data[yuv_pixel.Y] += 1;
      Ys[y*n+x] = yuv_pixel.Y;
      Us[y*n+x] = yuv_pixel.U;
      Vs[y*n+x] = yuv_pixel.V;
    }
  }

  //histogram equalisation
  for(int i = 0; i < 256; ++i){
    acc_equ += histogram_data[i];
    histogram_data_equ[i] = round((max_intensity * acc_equ) / (m*n));
  }

  //mapping new values
  for(int i = 0; i < total; ++i){
    Ys[i] = histogram_data_equ[Ys[i]];
  }

  char buffer[50];

  yuv_iterator=NewPixelIterator(yuv_wand);
  if ((yuv_iterator == (PixelIterator *) NULL))
    printf("Error con iterador.\n");
  for (y=0; y < (long) MagickGetImageHeight(yuv_wand); y++)
  {
    yuv_pixels=PixelGetNextIteratorRow(yuv_iterator,&width);
    if ((yuv_pixels == (PixelWand **) NULL))
      break;
    for (x=0; x < (long) width; x++)
    {
      struct RGB_Color rgb_pixel = RGBfromYUV(Ys[y*n+x],Us[y*n+x],Vs[y*n+x]);
      sprintf(buffer, "rgb(%d,%d,%d)", rgb_pixel.R,rgb_pixel.G,rgb_pixel.B);
      PixelSetColor(yuv_pixels[x], buffer);
    }

    (void) PixelSyncIterator(yuv_iterator);
  }

  if (y < (long) MagickGetImageHeight(image_wand))
    printf("Error con la imagen.\n");
  yuv_iterator=DestroyPixelIterator(yuv_iterator);
  iterator=DestroyPixelIterator(iterator);
  image_wand=DestroyMagickWand(image_wand);
  /*
    Write the image then destroy it.
  */
  status=MagickWriteImages(yuv_wand,argv[2],MagickTrue);
  if (status == MagickFalse)
    printf("Error con la escritura de la imagen.\n");
  yuv_wand=DestroyMagickWand(yuv_wand);
  MagickWandTerminus();
  return(0);
}

