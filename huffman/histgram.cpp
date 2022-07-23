#include "histgram.hpp"

#include <iostream>

Histgram::Histgram() : data(data_size, 0) {
}

void Histgram::push_char(char c) {
    if (c < 0) {
        std::cerr << "Invalid character: " << (int)c << "is given.";
        return;
    }

    this->data[c] += 1;
}

void Histgram::show_all() {
    for (int i = 0; i < data_size; i++) {
        std::cout << '\'' << (char)i << "\': " << this->data[(int)i]
                  << std::endl;
    }
}