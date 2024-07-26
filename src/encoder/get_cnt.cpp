//
// Created by fedor on 7/26/24.
//

#include <fstream>

#include "get_cnt.h"



void get_cnt(std::ifstream &fin, int cnt_of_symbols[]) {
    fin.clear(), fin.seekg(0, std::ios::beg);
    char input_byte;
    while (fin.read(&input_byte, sizeof(char))) {
        cnt_of_symbols[static_cast<unsigned char>(input_byte)]++;
    }
}


void get_cnt(std::string &s, int cnt_of_symbols[]) {
    for (const char c : s) {
        cnt_of_symbols[static_cast<unsigned char>(c)]++;
    }
}