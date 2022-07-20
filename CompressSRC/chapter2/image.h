#ifndef COMPRESSION_IMAGE_H_
#define COMPRESSION_IMAGE_H_

#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef unsigned char BYTE;

typedef struct {
    int width;
    int height;
    int depth;
    void *pixels;
} ImageData;

#define PIXELMAX 255

typedef struct {
    int r;
    int g;
    int b;
} Pixel;

ImageData *create_image(int width, int height, int depth);
void dispose_image(ImageData *image);

int get_pixel(ImageData *image, int x, int y, Pixel *pixel);
int set_pixel(ImageData *image, int x, int y, Pixel *pixel);

#endif // COMPRESSION_IMAGE_H
