//
// Created by fedor on 7/27/24.
//

#ifndef BINT_H
#define BINT_H

#include <fstream>

#include "../CONSTANTS.h"

class BInt {
public:
    static LCHAR read(std::ifstream &fin, const unsigned bits) {
        LCHAR result = 0;
        for (unsigned bit = 0; bit < bits; bit++) {
            result <<= 1;
            if (read_bit_from_input_buffer(fin)) {
                result++;
            }
        }
        return result;
    }

    static void clear_input_buffer() {
        input_buffer = 0, input_buffer_sz = 0;
    }

    static void print(std::ofstream &fout, const unsigned val, const unsigned bits) {//todo: use templates in val
        if (!bits) {
            return;
        }
        unsigned bit = bits - 1;
        do {
            if (bit < sizeof(val) * 8) {
                add_bit_to_output_buffer(fout, val >> bit & 1);
            } else {
                add_bit_to_output_buffer(fout, 0);
            }
        } while (bit-- > 0);
    }

    static void clear_output_buffer(std::ofstream &fout) {
        while (output_buffer_sz != 0 && output_buffer_sz < SIZE_OF_CHAR) {
            output_buffer <<= 1;
            output_buffer_sz++;
        }
        const auto out = static_cast<char>(output_buffer);
        fout.write(&out, sizeof(char));
        output_buffer = 0, output_buffer_sz = 0;
    }

private:
    inline static unsigned char input_buffer = 0, output_buffer = 0;
    inline static unsigned input_buffer_sz = 0, output_buffer_sz = 0;

    static void check_input_buffer(std::ifstream &fin) {
        if (input_buffer_sz == 0) {
            char in;
            fin.read(&in, sizeof(char));
            input_buffer = static_cast<unsigned char>(in), input_buffer_sz = SIZE_OF_CHAR;
        }
    }

    static bool read_bit_from_input_buffer(std::ifstream &fin) {
        check_input_buffer(fin);
        return input_buffer >> --input_buffer_sz & 1;
    }

    static void check_output_buffer(std::ofstream &fout) {
        if (output_buffer_sz == SIZE_OF_CHAR) {
            const char out = static_cast<char>(output_buffer);
            fout.write(&out, sizeof(char));
            output_buffer = 0, output_buffer_sz = 0;
        }
    }

    static void add_bit_to_output_buffer(std::ofstream &fout, const int symb) {
        output_buffer <<= 1;
        output_buffer_sz++;
        if (symb) {
            output_buffer++;
        }
        check_output_buffer(fout);
    }
};


#endif //BINT_H
