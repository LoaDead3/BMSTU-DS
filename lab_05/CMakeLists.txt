project(dts)

add_executable(lab_05
        src/main.c
        src/queues.c
        inc/queues.h
        src/sl_list.c
        inc/sl_list.h
        src/err.c
        inc/err.h
        src/queues_io.c inc/queues_io.h)

#add_executable(lab_05_cmp
#        src/cmp.c
#        src/queues.c
#        inc/queues.h
#        src/sl_list.c
#        inc/sl_list.h
#        src/err.c
#        inc/err.h
#        )