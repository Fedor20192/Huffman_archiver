//
// Created by fedor on 7/26/24.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <filesystem>

using LCHAR = unsigned short;

namespace fs = std::filesystem;

constexpr unsigned LCHAR_RANGE = 259;
constexpr unsigned SIZE_OF_LCHAR = 9;
constexpr unsigned SIZE_OF_BIT = 1;
constexpr unsigned SIZE_OF_CHAR = 8;
constexpr LCHAR FILENAME_END = 256;
constexpr LCHAR ONE_MORE_FILE = 257;
constexpr LCHAR ARCHIVE_END = 258;
#endif //CONSTANTS_H
