//
// Created by fedor on 7/26/24.
//

#include <fstream>
#include <filesystem>
#include <iostream>
#include <algorithm>

#include "encoder.h"
#include "../structures/Bor.h"
#include "../CONSTANTS.h"
#include "../structures/BInt.h"

namespace fs = std::filesystem;

void get_cnt(std::ifstream &fin, unsigned long long cnt_of_symbols[]) {
    fin.clear(), fin.seekg(0, std::ios::beg);
    char input_byte;
    while (fin.read(&input_byte, sizeof(char))) {
        cnt_of_symbols[static_cast<unsigned char>(input_byte)]++;
    }
}


void get_cnt(std::string &s, unsigned long long cnt_of_symbols[]) {
    for (const char c: s) {
        cnt_of_symbols[static_cast<unsigned char>(c)]++;
    }
}

bool cmp(const std::pair<unsigned short, std::string> &a, const std::pair<unsigned short, std::string> &b) {
    if (a.second.empty() && b.second.empty()) {
        return a.first < b.first;
    }
    if (a.second.empty()) {
        return false;
    }
    if (b.second.empty()) {
        return true;
    }
    return a.second.size() < b.second.size() || (a.second.size() == b.second.size() && a.first < b.first);
}

void next_code(std::string &code) {
    for (int i = static_cast<int>(code.size()) - 1; i >= 0; i--) {
        if (code[i] == '0') {
            code[i] = '1';
            return;
        }
        code[i] = '0';
    }
    code.insert(code.begin(), 0, '1');
}

void huffman_code_to_canonical(std::string codes[], std::pair<unsigned short, std::string> arr[]) {
    for (unsigned short ind = 0; ind < UCHAR_RANGE; ind++) {
        arr[ind] = {ind, codes[ind]};
    }
    std::sort(arr, arr + UCHAR_RANGE, cmp);
    std::string last;
    for (unsigned short ind = 0; ind < UCHAR_RANGE; ind++) {
        if (arr[ind].second.empty()) {
            break;
        }
        while (last.size() < arr[ind].second.size()) {
            last += '0';
        }
        arr[ind].second = last;
        codes[arr[ind].first] = last;
        next_code(last);
    }
}

void encode(int argc, char *argv[]) {
    unsigned long long cnt_of_symbols[UCHAR_RANGE] = {};
    fs::path output_path = argv[2];
    std::ofstream fout(output_path);
    for (int ind = 3; ind < argc; ind++) {
        fs::path input_path = argv[ind];
        if (!exists(input_path)) {
            std::cout << input_path << " is not exist\n";
            continue;
        }
        std::string filename = input_path.filename().string();
        get_cnt(filename, cnt_of_symbols);
        std::ifstream fin(input_path);
        get_cnt(fin, cnt_of_symbols);
        fin.close();
    }
    cnt_of_symbols[FILENAME_END] = cnt_of_symbols[ONE_MORE_FILE] = cnt_of_symbols[ARCHIVE_END] = 1;
    auto bor = Bor(cnt_of_symbols);
    std::string codes[UCHAR_RANGE];
    bor.get_codes(codes);
    std::pair<unsigned short, std::string> arr[UCHAR_RANGE];
    huffman_code_to_canonical(codes, arr);
    const unsigned short alphabet_sz = bor.get_alphabet_sz();

    for (unsigned short ind = 0; ind < UCHAR_RANGE; ind++) {
         if (!codes[ind].empty()) {
             fout << ind << ' ' << codes[ind] << '\n';
         }
    }

}
