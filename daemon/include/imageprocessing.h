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

void classify(const char* image_path, const char* image_name, const char* destiny_path);
void histogram(const char* image_path, const char* image_name, const char* destiny_path);
void append_file(const char* path, const char* content);
void write_file(const char* path, const char* content);
int read_file(const char* path);
void getDate(char* buffer, int buffer_size);
#endif // _IMAGEPROCESSING_H
