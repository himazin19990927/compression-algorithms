#include <fstream>
#include <iostream>
#include <string>

#include "histgram.hpp"
#include "huffman_tree.hpp"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Not enough arguments" << std::endl;
    }

    std::string input_filename = argv[1];
    std::string output_filename = argv[2];

    std::ifstream input_file(input_filename);
    // input_file.open(input_filename, std::ios::in);

    Histgram hist;

    char c;
    while (input_file.get(c)) {
        hist.push_char(c);
    }

    HuffmanTree tree = make_huffman_tree(hist);

    for (int i = 0; i < data_size; i++) {
        if (hist.data[i] > 0) {
            char c = (char)i;
            auto data = tree.encode(c);
            std::cout << c << ": ";
            for (bool d : data) {
                if (d) {
                    std::cout << 1;
                } else {
                    std::cout << 0;
                }
            }
            std::cout << std::endl;
        }
    }

    return 0;
}