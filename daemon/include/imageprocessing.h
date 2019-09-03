// imagepreocessing.h

#ifndef _IMAGEPROCESSING_H
#define _IMAGEPROCESSING_H

#include <stdlib.h>
#include <wand/MagickWand.h>
#include <converters.h>

void classify(const char* image_path, const char* image_name, const char* destiny_path);
void histogram(const char* image_path, const char* image_name, const char* destiny_path);
#endif // _IMAGEPROCESSING_H
