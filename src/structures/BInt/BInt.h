//
// Created by fedor on 7/28/24.
//

#ifndef BINT_H
#define BINT_H

#include "../../CONSTANTS.h"

class BInt {
public:
    static LCHAR read(std::ifstream &fin, unsigned bits);

    static void clear_input_buffer();

    static void print(std::ofstream &fout, unsigned val, unsigned bits);

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
