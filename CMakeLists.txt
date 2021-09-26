cmake_minimum_required(VERSION 3.17)
project(Y2_Num_Algo C)

set(CMAKE_C_STANDARD 11)

include_directories(TP_1)

add_executable(TP_1
        TP_1/main.c
        TP_1/matrices.h TP_1/toolbox.h)
