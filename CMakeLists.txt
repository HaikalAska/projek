cmake_minimum_required(VERSION 4.0)
project(projek C)

set(CMAKE_C_STANDARD 23)

add_executable(projek
#        masterAdmin.c
        main.c
        login.h
        Menu.h
        FrameTabel.h
        superadmin/create.h
        superadmin/delete.h
        superadmin/read.h
        superadmin/update.h
        Kendaraan/menuKendaraan.h
        Kendaraan/createKendaraan.h
        Kendaraan/readKendaraan.h
        Kendaraan/updateKendaraan.h
        Kendaraan/deleteKendaraan.h
)


#BUAT BRANCH BARU RUTE


