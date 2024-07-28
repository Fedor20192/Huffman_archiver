//
// Created by fedor on 7/26/24.
//

#include <fstream>
#include <filesystem>
#include <iostream>
#include <algorithm>

#include "encoder.h"
#include "../structures/Bor.h"
#include "../structures/BInt.h"
#include "../CONSTANTS.h"

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

bool cmp(const std::pair<LCHAR, std::string> &a, const std::pair<LCHAR, std::string> &b) {
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
    code.insert(0, "1");
}

void huffman_code_to_canonical(std::string codes[], std::pair<LCHAR, std::string> arr[]) {
    for (LCHAR ind = 0; ind < LCHAR_RANGE; ind++) {
        arr[ind] = {ind, codes[ind]};
    }
    std::sort(arr, arr + LCHAR_RANGE, cmp);
    std::string last;
    for (LCHAR ind = 0; ind < LCHAR_RANGE && !arr[ind].second.empty(); ind++) {
        while (last.size() < arr[ind].second.size()) {
            last += '0';
        }
        arr[ind].second = last;
        codes[arr[ind].first] = last;
        next_code(last);
    }
}

void get_cnt_of_length(unsigned cnt_of_length[], std::pair<LCHAR, std::string> arr[]) {
    for (LCHAR ind = 0; ind < LCHAR_RANGE && !arr[ind].second.empty(); ind++) {
        cnt_of_length[arr[ind].second.size()]++;
    }
}

void print_code(std::ofstream &fout, std::string &code) {
    for (const char c: code) {
        BInt::print(fout, c - '0', SIZE_OF_BIT);
    }
}

void print_name(std::string &filename, std::ofstream &fout, std::string codes[]) {
    for (const char c: filename) {
        print_code(fout, codes[static_cast<unsigned char>(c)]);
    }
}

void print_file(std::ifstream &fin, std::ofstream &fout, std::string codes[]) {
    fin.clear(), fin.seekg(0, std::ios::beg);
    char in;
    while (fin.read(&in, sizeof(char))) {
        print_code(fout, codes[static_cast<unsigned char>(in)]);
    }
}

int encode(int argc, char *argv[]) {
    unsigned long long cnt_of_symbols[LCHAR_RANGE] = {};
    cnt_of_symbols[FILENAME_END] = cnt_of_symbols[ONE_MORE_FILE] = cnt_of_symbols[ARCHIVE_END] = 1;
    unsigned cnt_of_files = 0;

    fs::path output_path = argv[2];
    std::ofstream fout(output_path, std::ios::binary);

    for (int ind = 3; ind < argc; ind++) {
        fs::path input_path = argv[ind];
        if (!exists(input_path)) {
            std::cout << input_path << " is not exist" << std::endl;
            return 111;
        }

        cnt_of_files++;

        std::string filename = input_path.filename().string();
        get_cnt(filename, cnt_of_symbols);

        std::ifstream fin(input_path, std::ios::binary);
        get_cnt(fin, cnt_of_symbols);
        fin.close();
    }

    auto bor = Bor(cnt_of_symbols);
    std::string codes[LCHAR_RANGE];
    bor.get_codes(codes);
    const LCHAR alphabet_sz = bor.get_alphabet_sz();


    std::pair<LCHAR, std::string> arr[LCHAR_RANGE];
    huffman_code_to_canonical(codes, arr);

    unsigned max_sz = 0;
    BInt::print(fout, alphabet_sz, SIZE_OF_LCHAR);
    for (LCHAR ind = 0; ind < LCHAR_RANGE && !arr[ind].second.empty(); max_sz = arr[ind++].second.size()) {
        BInt::print(fout, arr[ind].first, SIZE_OF_LCHAR);
    }

    auto cnt_of_length = new unsigned[max_sz + 1]{};
    get_cnt_of_length(cnt_of_length, arr);
    for (unsigned ind = 1; ind <= max_sz; ind++) {
        BInt::print(fout, cnt_of_length[ind], SIZE_OF_LCHAR);
    }
    delete[] cnt_of_length;

    for (int ind = 3; ind < argc; ind++) {
        fs::path input_path = argv[ind];

        std::string filename = input_path.filename().string();
        print_name(filename, fout, codes);
        print_code(fout, codes[FILENAME_END]);
        std::ifstream fin(input_path, std::ios::binary);
        print_file(fin, fout, codes);
        fin.close();

        if (--cnt_of_files) {
            print_code(fout, codes[ONE_MORE_FILE]);
        }
    }

    print_code(fout, codes[ARCHIVE_END]);
    BInt::clear_output_buffer(fout);
    fout.close();
    return 0;
}
