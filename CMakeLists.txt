cmake_minimum_required(VERSION 4.0)
project(projek C)

set(CMAKE_C_STANDARD 23)

add_executable(projek
#        masterAdmin.c
        main.c
        Menu.h
        PesanTiket.h
        FrameTabel.h
        Rute/rute.h
        Rute/createRute.h
        Rute/readRute.h
        Rute/updateRute.h
        Rute/deleteRute.h
)
