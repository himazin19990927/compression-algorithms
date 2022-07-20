#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;

int decode_data(FILE *fp_input, FILE *fp_output);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        exit(EXIT_FAILURE);
    }

    FILE *fp_input = fopen(argv[1], "rb");
    if (fp_input == NULL) {
        fprintf(stderr, "Input File cannot open\n");
        exit(EXIT_FAILURE);
    }

    // 圧縮処理
    FILE *fp_output = fopen(argv[2], "wb");
    if (fp_output == NULL) {
        fprintf(stderr, "Output File cannot open\n");
        exit(EXIT_FAILURE);
    }
    decode_data(fp_input, fp_output);
    fclose(fp_input);
    fclose(fp_output);
}

// fp_inputで指定されているファイルデータをランレングス符号化による圧縮結果とし、
// それを展開して、結果をfp_outputで指定されるファイルに出力する
int decode_data(FILE *fp_input, FILE *fp_output) {
    for (;;) {
        int length = fgetc(fp_input);
        if (length == EOF) {
            break;
        }

        int code = fgetc(fp_input);
        if (code == EOF) {
            // エラー
            return 0;
        }

        for (int i = 0; i < length; i++) {
            fputc(code, fp_output);
        }
    }

    return 1;
}