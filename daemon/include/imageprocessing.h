// imagepreocessing.h

#ifndef _IMAGEPROCESSING_H
#define _IMAGEPROCESSING_H

#include <stdlib.h>
#include <wand/MagickWand.h>
#include <converters.h>

int classify(const char* imagepath, const char* imagename, const char* destinypath);

#endif // _IMAGEPROCESSING_H
