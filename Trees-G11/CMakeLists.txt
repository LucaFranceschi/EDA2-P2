cmake_minimum_required(VERSION 3.14)
project(Lab2 C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(Lab2
        include/commons.h
        src/main.c
        include/main.h
        src/tree.c
        include/tree.h
        include/utils.h
        src/utils.c

        include/generate_candidates.h src/generate_candidates.c)
