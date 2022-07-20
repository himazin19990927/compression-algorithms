#include "image.h"

// 画像データの作成
// width: 画像の横幅
// height: 画像の縦幅
// depth: 1ピクセルあたりのビット数(8 or 24)
ImageData* create_image(int width, int height, int depth) {
    if (width < 0 || height < 0) {
        return NULL;
    }
    if (depth != 8 && depth != 24) {
        return NULL;
    }

    ImageData* image = malloc(sizeof(ImageData));
    if (image == NULL) {
        return NULL;
    }

    // 1ピクセルあたりのバイト数(色数)を求める
    int byte_per_pixel = depth / 8;
    image->pixels =
        malloc(sizeof(BYTE) * byte_per_pixel * width * width * height);
    if (image->pixels == NULL) {
        free(image);
        return NULL;
    }

    // 各プロパティを設定
    image->width = width;
    image->height = height;
    image->depth = depth;

    return image;
}

// 画像データの破棄
void dispose_image(ImageData* image) {
    if (image == NULL) {
        return;
    }

    if (image->pixels != NULL) {
        free(image->pixels);
    }
    free(image);
    return;
}

int get_pixel(ImageData* image, int x, int y, Pixel* pixel) {
    if (image == NULL) {
        return -1;
    }

    if (image->pixels == NULL) {
        return -1;
    }

    int return_value = 1;
    // 画像外の座標が指定された場合の処理
    // 最も近い画像上のピクセルを参照する
    if (x < 0) {
        x = 0;
        return_value = 0;
    }

    if (x >= image->width) {
        x = image->width - 1;
        return_value = 0;
    }

    if (y < 0) {
        y = 0;
        return_value = 0;
    }

    if (y >= image->height) {
        y = image->height - 1;
        return_value = 0;
    }

    int depth = image->depth;
    int address = x + y * image->width;
    BYTE* pixels = image->pixels;

    if (depth == 8) {
        // グレースケールの場合はRGBにそれぞれ同じ値をセットする
        int gray_value = pixels[address];
        pixel->r = gray_value;
        pixel->g = gray_value;
        pixel->b = gray_value;
    } else if (depth == 24) {
        pixels += (address * 3);
        pixel->r = (*pixels);
        pixels++;
        pixel->g = (*pixels);
        pixels++;
        pixel->b = (*pixels);
    } else {
        return -1;
    }

    return return_value;
}

int correct_pixel_value(int value, int max) {
    if (value < 0) {
        return 0;
    }

    if (value > max) {
        return max;
    }

    return value;
}

// 画像データ上のピクセルを変更する
// x, y 画素の座標
// pixel セットするピクセル
int set_pixel(ImageData* image, int x, int y, Pixel* pixel) {
    if (image == NULL) {
        return -1;
    }

    if (image->pixels == NULL) {
        return -1;
    }

    // 画像外の座標が指定されたら何もしない
    if (x < 0 || x >= image->width || y < 0 || y >= image->height) {
        return 0;
    }

    int depth = image->depth;
    int address = x + y * image->width;
    BYTE* pixels = image->pixels;
    if (depth == 8) {
        pixels[address] = correct_pixel_value(pixel->r, PIXELMAX);
    } else if (depth == 24) {
        pixels += (address * 3);
        (*pixels) = correct_pixel_value(pixel->r, PIXELMAX);
        pixels++;
        (*pixels) = correct_pixel_value(pixel->g, PIXELMAX);
        pixels++;
        (*pixels) = correct_pixel_value(pixel->b, PIXELMAX);
        pixels++;
    } else {
        return -1;
    }

    return 1;
}