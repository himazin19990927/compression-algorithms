#include "bmp.h"
#include "image.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        exit(EXIT_FAILURE);
    }

    ImageData *image;
    int res = read_BMP_file(argv[1], &image);
    printf("read_BMP_file: %d\n", res);

    write_BMP_file(argv[2], image);
    dispose_image(image);
}