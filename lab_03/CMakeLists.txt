cmake_minimum_required(VERSION 3.20)
project(tids_lr3_test C)

set(CMAKE_C_STANDARD 99)

#add_executable(lab_03
#        main.c
#        matrix.c
#        matrix.h
#        matrix_io.c
#        matrix_io.h
#        error.c
#        error.h
#        )

add_executable(lab_03_cmp
        cmp.c
        matrix.c
        matrix.h
        matrix_io.c
        matrix_io.h
        error.c
        error.h
        )

#add_compile_options(-std=c99 -Wall -Werror)
