// imagepreocessing.h

#ifndef _IMAGEPROCESSING_H
#define _IMAGEPROCESSING_H

#include <converters.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wand/MagickWand.h>

/**
 Clasiffies an image

 const char* image_path: Image directory input
 const char* image_name: Image name
 const char* destiny_path: Image directory output
*/

void classify(const char* image_path, const char* image_name, const char* destiny_path);

/**
 Applies histogram to an image

 const char* image_path: Image directory input
 const char* image_name: Image name
 const char* destiny_path: Image directory output
*/

void histogram(const char* image_path, const char* image_name, const char* destiny_path);

/**
 Appends to a file

 const char* path: File path
 const char* content: Content to add
*/

void append_file(const char* path, const char* content);

/**
 Writes to a file

 const char* path: File path
 const char* content: Content to put
*/

void write_file(const char* path, const char* content);

/**
 Reads byte size of a file

 const char* path: File path
*/

int read_file(const char* path);

/**
 Get the date

 const char* buffer: Buffer to place date
 int buffer_size: Content to put
*/

void getDate(char* buffer, int buffer_size);
#endif // _IMAGEPROCESSING_H
