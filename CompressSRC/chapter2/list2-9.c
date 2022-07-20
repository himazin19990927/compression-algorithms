#include "bmp.h"
#include "image.h"

int main(int argc, char *argv[]) {
    Pixel white;
    white.r = 254;
    white.g = 254;
    white.b = 254;

    Pixel black;
    black.r = 1;
    black.g = 1;
    black.b = 1;

    int width = 9;
    int height = 9;
    ImageData *image = create_image(width, height, 24);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x % 2 == y % 2) {
                set_pixel(image, x, y, &white);
            } else {
                set_pixel(image, x, y, &black);
            }
        }
    }

    
    write_BMP_file("out.bmp", image);
    dispose_image(image);
}