//
// Created by fedor on 7/28/24.
//

#ifndef BINT_H
#define BINT_H

#include "../../CONSTANTS.h"

class BInt {
public:
    template<typename T>
    static T read(std::ifstream &fin, const unsigned bits) {
        T result = 0;
        for (unsigned bit = 0; bit < bits; bit++) {
            result <<= 1;
            if (read_bit_from_input_buffer(fin)) {
                ++result;
            }
        }
        return result;
    }

    static void clear_input_buffer();

    template<typename T>
    static void print(std::ofstream &fout, T val, const unsigned bits) {
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

    static void clear_output_buffer(std::ofstream &fout);

private:
    inline static unsigned char input_buffer = 0, output_buffer = 0;
    inline static unsigned input_buffer_sz = 0, output_buffer_sz = 0;

    static void check_input_buffer(std::ifstream &fin);

    static bool read_bit_from_input_buffer(std::ifstream &fin);

    static void check_output_buffer(std::ofstream &fout);

    static void add_bit_to_output_buffer(std::ofstream &fout, int symb);
};



#endif //BINT_H
