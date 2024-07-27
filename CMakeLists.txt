cmake_minimum_required(VERSION 3.28)
project(hse_archiver)

set(CMAKE_CXX_STANDARD 20)

add_executable(hse_archiver
        src/main.cpp
        src/encoder/encoder.cpp
        src/encoder/encoder.h
        src/structures/Bor.h
        src/structures/PriorityQueue.h
        src/CONSTANTS.h
        src/structures/BorNode.h
        src/structures/BInt.h
)
