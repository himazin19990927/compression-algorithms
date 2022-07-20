#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 102400

typedef unsigned char BYTE;

void encode_data(FILE *fp, BYTE *datas, int data_size);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        exit(EXIT_FAILURE);
    }

    FILE *fp_input = fopen(argv[1], "rb");
    if (fp_input == NULL) {
        fprintf(stderr, "Input File cannot open\n");
        exit(EXIT_FAILURE);
    }

    // ファイルデータをバッファに取り込む
    int data_size = 0;
    int c;
    unsigned char buffer[BUFFER_SIZE];
    while (data_size < BUFFER_SIZE && (c = fgetc(fp_input)) != EOF) {
        buffer[data_size] = c;
        data_size++;
    }
    fclose(fp_input);

    // 圧縮処理をする
    FILE *fp_output = fopen(argv[2], "wb");
    if (fp_output == NULL) {
        fprintf(stderr, "Output File cannot open\n");
        exit(EXIT_FAILURE);
    }
    encode_data(fp_output, buffer, data_size);
    fclose(fp_output);

    return 0;
}

// 同じデータが並んでいる部分の長さを取得する
// datas中のx番目の位置を調べ、同じデータ値が並んでいる長さ(ラン長)をrunに、
// データ値をcodeに返す
// datasの大きさはdata_sizeで指定する
// ラン長の最大値はlimitまでに制限する
// 戻り地は、次に処理対象となるデータの位置
int get_run_length(BYTE *datas, int x, int data_size, int limit, int *run,
                   int *code) {
    // 処理中のデータ位置
    int processing_point = x;

    *run = 1;
    *code = datas[processing_point];
    processing_point += 1;

    while (processing_point < data_size && *code == datas[processing_point] &&
           *run < limit) {
        processing_point += 1;
        *run += 1;
    }

    return processing_point;
}

// ランレングス圧縮して、結果をfpで指定されるファイルに出力する
void encode_data(FILE *fp, BYTE *datas, int data_size) {
    int processing_point = 0;
    int run, code;
    while (processing_point < data_size) {
        processing_point = get_run_length(datas, processing_point, data_size,
                                          0xff, &run, &code);
        fputc(run, fp);
        fputc(code, fp);
    }
}