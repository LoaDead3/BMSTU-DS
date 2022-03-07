cmake_minimum_required(VERSION 3.20)
project(tids_lr3_test C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_04
        src/main.c
        src/sl_list.c
        head/sl_list.h
        src/stack.c
        head/stack.h
        src/err.c
        head/err.h
        head/const.h
        src/calc.c
        head/calc.h
       )

#add_executable(lab_04_cmp
#        src/cmp.c
#        src/sl_list.c
#        head/sl_list.h
#        src/stack.c
#        head/stack.h
#        src/err.c
#        head/err.h
#        head/const.h
#        src/calc.c
#        head/calc.h
#        )