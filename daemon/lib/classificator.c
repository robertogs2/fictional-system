#include <imageprocessing.h>

int classify(const char* imagepath, const char* imagename, const char* destinypath) {
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

    sprintf(buffer, "%s%s", imagepath, imagename);

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

    if (acc_red >= acc_green && acc_red >= acc_blue) sprintf(buffer, "%sred/%s", destinypath, imagename);
    else if (acc_green >= acc_red && acc_green >= acc_blue) sprintf(buffer, "%sgreen/%s", destinypath, imagename);
    else if (acc_blue >= acc_green && acc_blue >= acc_red) sprintf(buffer, "%sblue/%s", destinypath, imagename);

    iterator = DestroyPixelIterator(iterator);
    image_wand = DestroyMagickWand(image_wand);

    // Write the image then destroy it.

    status = MagickWriteImages(copy_wand, buffer, MagickTrue);
    if (status == MagickFalse)
        printf("Can't write image.\n");
    copy_wand = DestroyMagickWand(copy_wand);
    MagickWandTerminus();
}

/*int main(int argc, char **argv) {

    classify("../../test/", "sad.jpg", "../../test/");

    return (0);
}*/

