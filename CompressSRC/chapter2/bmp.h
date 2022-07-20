#ifndef COMPRESSION_BMP_H_
#define COMPRESSION_BMP_H_

#include <stdio.h>

#include "image.h"

typedef unsigned long DWORD;
typedef int BOOL;
typedef unsigned short WORD;
typedef unsigned long LONG;

#define BI_RGB 0L
#define BI_RLE8 1L
#define BI_RLE4 2L
#define BI_BITFIELDS 3L

// BMPヘッダ部のデータ構造定義
typedef struct {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BitMapFileHeader;

typedef struct {
    DWORD bcSize;
    WORD bcWidth;
    WORD bcHeight;
    WORD bcPlanes;
    WORD bcBitCount;
} BitMapCoreHeader;

typedef struct {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BitMapInfoHeader;

#define MAXCOLORS 256

int fwrite_WORD(WORD val, FILE *fp);
int fwrite_DWORD(DWORD val, FILE *fp);
int freadWORD(WORD *res, FILE *fp);
int freadDWORD(DWORD *res, FILE *fp);

static BOOL is_Win_DIB(BitMapInfoHeader *pBIH);
int count_of_DIB_color_entries(int iBitCount);
int get_DIB_x_max(int width, int depth);

int read_BMP_file(char *filename, ImageData **image);
int write_BMP_file(char *filename, ImageData *image);

#endif // COMPRESSION_BMP_H_
