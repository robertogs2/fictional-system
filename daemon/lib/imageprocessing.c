#include <imageprocessing.h>

void classify(const char* image_path, const char* image_name, const char* destiny_path) {
    char buffer[100];
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

    MagickWandGenesis();
    image_wand = NewMagickWand();

    sprintf(buffer, "%s%s", image_path, image_name);

    status = MagickReadImage(image_wand, buffer);\
    printf("%s\n", buffer);
    if (status == MagickFalse)
        printf("Can't open image.\n");
    copy_wand = CloneMagickWand(image_wand);

    int total = (int) MagickGetImageHeight(image_wand) * MagickGetImageWidth(image_wand);

    iterator = NewPixelIterator(image_wand);
    if ((iterator == (PixelIterator *) NULL))
        printf("Iterator error.\n");
    for (y = 0; y < (long) MagickGetImageHeight(image_wand); y++) {
        pixels = PixelGetNextIteratorRow(iterator, &width);
        if ((pixels == (PixelWand **) NULL))
            break;
        for (x = 0; x < (long) width; x++) {
            acc_red += PixelGetRed(pixels[x]) * 255;
            acc_green += PixelGetGreen(pixels[x]) * 255;
            acc_blue += PixelGetBlue(pixels[x]) * 255;
        }
    }

    acc_red /= total;
    acc_green /= total;
    acc_blue /= total;

    printf("R: %f, G: %f, B: %f\n", acc_red, acc_green, acc_blue);

    if (acc_red >= acc_green && acc_red >= acc_blue) sprintf(buffer, "%sred/%s", destiny_path, image_name);
    else if (acc_green >= acc_red && acc_green >= acc_blue) sprintf(buffer, "%sgreen/%s", destiny_path, image_name);
    else if (acc_blue >= acc_green && acc_blue >= acc_red) sprintf(buffer, "%sblue/%s", destiny_path, image_name);

    iterator = DestroyPixelIterator(iterator);
    image_wand = DestroyMagickWand(image_wand);

    // Write the image then destroy it.

    status = MagickWriteImages(copy_wand, buffer, MagickTrue);
    if (status == MagickFalse)
        printf("Can't write image.\n");
    copy_wand = DestroyMagickWand(copy_wand);
    MagickWandTerminus();
}

void histogram(const char* image_path, const char* image_name, const char* destiny_path){
  long y;
  MagickBooleanType status;
  MagickPixelPacket pixel;
  MagickWand *contrast_wand, *image_wand;
  PixelIterator *contrast_iterator, *iterator;
  PixelWand **contrast_pixels, **pixels;

  register long x;
  unsigned long width;
  float red, green, blue;

  int histogram_data_equ[256];
  int histogram_data[256];    
  int max_intensity = 255;
  int acc_equ = 0;
  char buffer[256];

  for(int i = 0; i < 256; ++i){
    histogram_data[i] = 0;
  }

  sprintf(buffer, "%s%s", image_path, image_name);

  /*
    Read an image.
  */
  MagickWandGenesis();
  image_wand=NewMagickWand();
  status=MagickReadImage(image_wand, buffer);
  if (status == MagickFalse)
    printf("Error al abrir la imagen.\n");
  contrast_wand=CloneMagickWand(image_wand);


  int m = (int) MagickGetImageHeight(image_wand); 
  int n = (int) MagickGetImageWidth(image_wand);
  int total = m * n;

  short Ys[total];
  short Us[total];
  short Vs[total];

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

      struct YUV_Color contrast_pixel = YUVfromRGB(red, green, blue);
      histogram_data[contrast_pixel.Y] += 1;
      Ys[y*n+x] = contrast_pixel.Y;
      Us[y*n+x] = contrast_pixel.U;
      Vs[y*n+x] = contrast_pixel.V;
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

  contrast_iterator=NewPixelIterator(contrast_wand);
  if ((contrast_iterator == (PixelIterator *) NULL))
    printf("Error con iterador.\n");
  for (y=0; y < (long) MagickGetImageHeight(contrast_wand); y++)
  {
    contrast_pixels=PixelGetNextIteratorRow(contrast_iterator,&width);
    if ((contrast_pixels == (PixelWand **) NULL))
      break;
    for (x=0; x < (long) width; x++)
    {
      struct RGB_Color rgb_pixel = RGBfromYUV(Ys[y*n+x],Us[y*n+x],Vs[y*n+x]);
      sprintf(buffer, "rgb(%d,%d,%d)", rgb_pixel.R,rgb_pixel.G,rgb_pixel.B);
      PixelSetColor(contrast_pixels[x], buffer);
    }

    (void) PixelSyncIterator(contrast_iterator);
  }

  if (y < (long) MagickGetImageHeight(image_wand))
    printf("Error con la imagen.\n");
  contrast_iterator=DestroyPixelIterator(contrast_iterator);
  iterator=DestroyPixelIterator(iterator);
  image_wand=DestroyMagickWand(image_wand);

  sprintf(buffer, "%s%s", destiny_path, image_name);
  /*
    Write the image then destroy it.
  */
  status=MagickWriteImages(contrast_wand,buffer,MagickTrue);
  if (status == MagickFalse)
    printf("Error con la escritura de la imagen.\n");
  contrast_wand=DestroyMagickWand(contrast_wand);
  MagickWandTerminus();

}
