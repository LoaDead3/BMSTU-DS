project(lab)

# цель lab_02_sort для замеров
# убрать lab_02/

add_executable(lab_02
        lab_02/src/main.c
        lab_02/src/error.c
        lab_02/head/error.h
        lab_02/src/show_table.c
        lab_02/head/show_table.h
        lab_02/src/show_table_io.c
        lab_02/head/show_table_io.h
        lab_02/src/sorts.c
        lab_02/head/sorts.h
        lab_02/head/show.h)

add_executable(lab_02_sort
        lab_02/src/error.c
        lab_02/head/error.h
        lab_02/src/show_table.c
        lab_02/head/show_table.h
        lab_02/src/show_table_io.c
        lab_02/head/show_table_io.h
        lab_02/src/sorts.c
        lab_02/head/sorts.h
        lab_02/head/show.h
        lab_02/sort_cmp.c)