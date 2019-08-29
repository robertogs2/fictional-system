#include <stdlib.h>
#include <wand/MagickWand.h>

int main(int argc,char **argv){

  if (argc != 2){
    (void) fprintf(stdout,"Usage: %s image \n",argv[0]);
    exit(0);
  }

  long y;

  MagickBooleanType status;

  MagickWand *copy_wand, *image_wand;

  PixelIterator *iterator;

  PixelWand **pixels;

  register long x;

  unsigned long width;

  float acc_red = 0;
  float acc_green = 0;
  float acc_blue = 0;

  /*
    Read an image.
  */
  MagickWandGenesis();
  image_wand=NewMagickWand();
  status=MagickReadImage(image_wand,argv[1]);
  if (status == MagickFalse)
    printf("Error al abrir la imagen.\n");
  copy_wand=CloneMagickWand(image_wand);

  int total = (int) MagickGetImageHeight(image_wand) * MagickGetImageWidth(image_wand); 

  iterator=NewPixelIterator(image_wand);
  if ((iterator == (PixelIterator *) NULL))
    printf("Error con iterador.\n");
  for (y=0; y < (long) MagickGetImageHeight(image_wand); y++){

    pixels=PixelGetNextIteratorRow(iterator,&width);
    if ((pixels == (PixelWand **) NULL))
      break;
    for (x=0; x < (long) width; x++){

      acc_red += PixelGetRed(pixels[x])*255;
      acc_green += PixelGetGreen(pixels[x])*255;
      acc_blue += PixelGetBlue(pixels[x])*255;

    }

  }

  acc_red /= total;
  acc_green /= total;
  acc_blue /= total;

  char buffer[100];

  printf("R: %f, G: %f, B: %f\n", acc_red, acc_green, acc_blue);

  if(acc_red >= acc_green && acc_red >= acc_blue) sprintf(buffer, "../classification/red/%s", argv[1]); 
  else if(acc_green >= acc_red && acc_green >= acc_blue) sprintf(buffer, "../classification/green/%s", argv[1]); 
  else if(acc_blue >= acc_green && acc_blue >= acc_red) sprintf(buffer, "../classification/blue/%s", argv[1]); 

  iterator=DestroyPixelIterator(iterator);
  image_wand=DestroyMagickWand(image_wand);

  /*
    Write the image then destroy it.
  */

  status=MagickWriteImages(copy_wand,buffer,MagickTrue);
  if (status == MagickFalse)
    printf("Error con la escritura de la imagen.\n");
  copy_wand=DestroyMagickWand(copy_wand);
  MagickWandTerminus();
  return(0);
}

