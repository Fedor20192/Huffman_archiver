cmake_minimum_required(VERSION 3.28)
project(hse_archiver)

set(CMAKE_CXX_STANDARD 20)

#set(BUILD_SHARED_LIBS OFF)
#set(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")

add_executable(hse_archiver
        src/main.cpp
        src/encoder/encoder.cpp
        src/encoder/encoder.h
        src/structures/Bor.h
        src/structures/PriorityQueue.h
        src/CONSTANTS.h
        src/structures/BorNode.h
        src/structures/BInt.h
        src/decoder/decoder.cpp
        src/decoder/decoder.h
)
