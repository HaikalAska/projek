cmake_minimum_required(VERSION 4.0)
project(projek C)

set(CMAKE_C_STANDARD 23)

add_executable(projek
#        masterAdmin.c
        main.c
        login.h
        Menu.h
        PesanTiket.h
        FrameTabel.h
        kategori/createkategori.h
        kategori/readkategori.h
        kategori/updatekategori.h
        kategori/deletekategori.h
        kategori/menukategori.h
        Promo/createpromo.h
        Promo/readpromo.h
        Promo/updatepromo.h
        Promo/deletepromo.h
        Promo/menupromo.h
)
