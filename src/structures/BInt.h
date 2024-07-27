//
// Created by fedor on 7/27/24.
//

#ifndef BINT_H
#define BINT_H

#include <fstream>

#include "../CONSTANTS.h"

class BInt {
public:
    static void print(std::ofstream &fout, const unsigned short val, const int bits) { //todo: use templates in val
        for (int bit = bits - 1; bit >= 0; bit--) {
            add_bit_to_output_buffer(fout, (val >> bit) & 1);
        }
    }

    static void clear_output_buffer(std::ofstream &fout) {
        while (output_buffer_sz != 0 && output_buffer_sz < SIZE_OF_CHAR) {
            output_buffer <<= 1;
            output_buffer_sz++;
        }
        fout.write(&output_buffer, sizeof(char));
        output_buffer = 0, output_buffer_sz = 0;
    }

private:
    inline static char input_buffer = 0, input_buffer_sz = 0, output_buffer = 0, output_buffer_sz = 0;

    static void check_output_buffer(std::ofstream &fout) {
        if (output_buffer_sz == SIZE_OF_CHAR) {
            fout.write(&output_buffer, sizeof(char));
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
