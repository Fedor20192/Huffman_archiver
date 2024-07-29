//
// Created by fedor on 7/28/24.
//

#include <fstream>

#include "BInt.h"

void BInt::clear_input_buffer() {
    input_buffer = 0, input_buffer_sz = 0;
}


void BInt::clear_output_buffer(std::ofstream &fout) {
    while (output_buffer_sz != 0 && output_buffer_sz < SIZE_OF_CHAR) {
        output_buffer <<= 1;
        output_buffer_sz++;
    }
    const auto out = static_cast<char>(output_buffer);
    fout.write(&out, sizeof(char));
    output_buffer = 0, output_buffer_sz = 0;
}

void BInt::check_input_buffer(std::ifstream &fin) {
    if (input_buffer_sz == 0) {
        char in;
        fin.read(&in, sizeof(char));
        input_buffer = static_cast<unsigned char>(in), input_buffer_sz = SIZE_OF_CHAR;
    }
}

bool BInt::read_bit_from_input_buffer(std::ifstream &fin) {
    check_input_buffer(fin);
    return input_buffer >> --input_buffer_sz & 1;
}

void BInt::check_output_buffer(std::ofstream &fout) {
    if (output_buffer_sz == SIZE_OF_CHAR) {
        const char out = static_cast<char>(output_buffer);
        fout.write(&out, sizeof(char));
        output_buffer = 0, output_buffer_sz = 0;
    }
}

void BInt::add_bit_to_output_buffer(std::ofstream &fout, const int symb) {
    output_buffer <<= 1;
    output_buffer_sz++;
    if (symb) {
        output_buffer++;
    }
    check_output_buffer(fout);
}
