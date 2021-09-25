cmake_minimum_required(VERSION 3.20)
project(TP_1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(TP_1
        main.c
        matrices.h)
