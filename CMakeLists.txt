cmake_minimum_required(VERSION 4.0)
project(projek C)

set(CMAKE_C_STANDARD 23)

add_executable(projek
#        masterAdmin.c
        main.c
        Menu.h
        PesanTiket.h
        FrameTabel.h
        kategori/create.h
        kategori/read.h
        kategori/update.h
        kategori/delete.h
        kategori/menukategori.h
)
