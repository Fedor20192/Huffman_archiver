//
// Created by fedor on 7/26/24.
//

#include <cstring>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "encoder/encoder.h"
#include "decoder/decoder.h"
#include "CONSTANTS.h"


void help_message() {
    std::cout << "Archiver\n";
    std::cout << "Commands:\n";
    std::cout << "archiver -c archive_name file1 [file2...]\t\tto compress file and save result in archive_name\n";
    std::cout << "archiver -d archive_name\t\t\t\t\t\tto uncompress archive\n";
    std::cout << "archiver -h\t\t\t\t\t\t\t\t\t\tto see help_message" << std::endl;
}



int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "-c") == 0) {
        return encode(argc, argv);
    } else if (strcmp(argv[1], "-d") == 0) {
        std::ifstream fin(argv[2]);
        if (!fin) {
            std::cout << argv[2] << " is not exists" << std::endl;
            return 1;
        }
        fs::path output_dir = fs::current_path();
        output_dir.operator+=('/');
        return decode(fin, output_dir);
    }
}
