//
// Created by fedor on 7/26/24.
//

#include <cstring>
#include <iostream>

#include "encoder/encoder.h"
#include "structures/BInt.h"


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
        return 111;
    }
    if (strcmp(argv[1], "-c") == 0) {
        encode(argc, argv);
    } else {

    }
    return 0;
}
