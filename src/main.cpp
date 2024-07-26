//
// Created by fedor on 7/26/24.
//

#include <iostream>
#include <fstream>
#include <filesystem>

#include "encoder/get_cnt.h"

namespace fs = std::filesystem;


void help_message() {
    std::cout << "Archiver\n";
    std::cout << "Commands:\n";
    std::cout << "archiver -c archive_name file1 [file2...]\t\tto compress file and save result in archive_name\n";
    std::cout << "archiver -d archive_name\t\t\t\t\t\tto uncompress archive\n";
    std::cout << "archiver -h\t\t\t\t\t\t\t\t\t\tto see help_message" << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc < 3 || argv[1] == "-h") {
        help_message();
        return 1;
    }
    if (argv[1] == "-c") {
        constexpr int UCHAR_RANGE = 256;
        int cnt_of_symbols[UCHAR_RANGE] = {};
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
    } else {

    }
}
