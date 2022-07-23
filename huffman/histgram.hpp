#ifndef HUFFMAN_HISTGRAM_H__
#define HUFFMAN_HISTGRAM_H__

#include <vector>

const int data_size = 128;

class Histgram {
   public:
    std::vector<int> data;

    Histgram();

    void push_char(char c);
    void show_all();
};

#endif