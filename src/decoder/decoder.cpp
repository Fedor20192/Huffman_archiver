//
// Created by fedor on 7/28/24.
//

#include <filesystem>
#include <iostream>
#include <fstream>

#include "decoder.h"
#include "../structures/BInt/BInt.h"
#include "../structures/Bor/Bor.h"

void new_read(std::ifstream &fin) {
    fin.clear(), fin.seekg(0, std::ios::beg);
    BInt::clear_input_buffer();
    const LCHAR alphabet_sz = BInt::read(fin, SIZE_OF_LCHAR);
    for (LCHAR ind = 0; ind < alphabet_sz; ind++) {
        BInt::read(fin, SIZE_OF_LCHAR);
    }
}

void next_cod(std::string &code) {
    for (int i = static_cast<int>(code.size()) - 1; i >= 0; i--) {
        if (code[i] == '0') {
            code[i] = '1';
            return;
        }
        code[i] = '0';
    }
    code.insert(0, "1");
}

void get_canonical_codes(const unsigned max_length_of_code, const LCHAR symbols[], const unsigned cnt_of_length[], std::string codes[]) {
    std::string last;
    LCHAR symb_ind = 0;
    for (unsigned lenght = 1; lenght <= max_length_of_code; lenght++) {
        last += '0';
        for (unsigned ind = 0; ind < cnt_of_length[lenght]; ind++, symb_ind++) {
            codes[symbols[symb_ind]] = last;
            next_cod(last);
        }
    }
}

int decode(std::ifstream &fin, fs::path &output_dir) {
    auto start = std::chrono::steady_clock::now();
    const LCHAR alphabet_sz = BInt::read(fin, SIZE_OF_LCHAR);
    auto symbols = new LCHAR[alphabet_sz];
    for (LCHAR ind = 0; ind < alphabet_sz; ind++) {
        symbols[ind] = BInt::read(fin, SIZE_OF_LCHAR);
    }

    LCHAR cnt = 0;
    unsigned max_length_of_code = 0;
    while (cnt < alphabet_sz) {
        max_length_of_code++;
        cnt += BInt::read(fin, SIZE_OF_LCHAR);
    }
    auto cnt_of_length = new unsigned[max_length_of_code + 1];
    std::string codes[LCHAR_RANGE];

    new_read(fin);

    for (unsigned lenght_of_code = 1; lenght_of_code <= max_length_of_code; lenght_of_code++) {
        cnt_of_length[lenght_of_code] = BInt::read(fin, SIZE_OF_LCHAR);
    }

    get_canonical_codes(max_length_of_code, symbols, cnt_of_length, codes);

    auto bor = Bor(codes);

    bool is_filename_active = true;

    std::ofstream fout;

    while (!fin.eof()) {
        const LCHAR bit = BInt::read(fin, SIZE_OF_BIT);
        bor.add(bit);
        if (bor.is_terminal()) {
            const LCHAR symb = bor.get_symb();
            bor.reset();
            if (symb == FILENAME_END) {
                is_filename_active = false;
                fout.open(output_dir, std::ios::binary);
                output_dir.remove_filename();
            } else if (symb == ONE_MORE_FILE) {
                is_filename_active = true;
                fout.close();
            } else if (symb == ARCHIVE_END) {
                break;
            } else if (is_filename_active) {
                output_dir.operator+=(static_cast<char>(symb));
            } else {
                char out = static_cast<char>(symb);
                fout.write(&out, sizeof(char));
            }
        }
    }

    delete[] cnt_of_length;
    delete[] symbols;
    auto end = std::chrono::steady_clock::now();
    std::cout << "TIME: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " MS\n";
    return 0;
}
