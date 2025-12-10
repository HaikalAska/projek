#ifndef PROJEK_MENU_H
#define PROJEK_MENU_H
#include "FrameTabel.h"
#include "PesanTiket.h"
#include "superadmin/KelolaStaff.h"
#include "Rute/rute.h"



void menuSuperAdmin() {
    int pilih;

    while (1) {
        clearscreen();
        fillBackground(0x90);
        printBorder(1, 1, 153, 43);
        FrameYangTengah(31, 1, 43);
        FrameYangHider(1,9,153);
        tampilanlogin("GAMBARASCI.txt", 60, 3);
        gotoxy(8,5); printf("Kelompok 5");



        gotoxy(3, 11); printf("===== MENU SUPERADMIN =====\n");
        gotoxy(3, 13); printf("[1] Kelola Data Staff\n");
        gotoxy(3, 15);printf("[2] Lihat Laporan\n");
        gotoxy(3, 17);printf("[3] Kelola Kategori\n");
        gotoxy(3, 19);printf("[4] Log Out\n");
        pilih = menuNavigasi(4, 13, 3);

        switch (pilih) {
            case 1:
                MenukelolaStaff();
            case 2:
                menuAdminRute();
                break;
            case 3:
                break;
            case 4:
               break;
        }

        gotoxy(3, 19); printf("====== Anda Log Out ======");
        getchar();
        getchar();
        return;

    }

}



static void menuStaff() {
    int pilih;

    while (1) {
        clearscreen();
        fillBackground(0x90);
        printBorder(1, 1, 153, 43);
        FrameYangTengah(31, 1, 43);
        FrameYangHider(1,9,153);
        tampilanlogin("GAMBARASCI.txt", 60, 3);
        gotoxy(8,5); printf("Kelompok 5");



        gotoxy(3, 11); printf("===== MENU STAFF =====\n");
        gotoxy(3, 13); printf("[1] Pemesanan Tiket\n");
        gotoxy(3, 15);printf("[2] Refund Tiket\n");
        gotoxy(3, 17);printf("[3] Log Out\n");
        pilih = menuNavigasi(3, 13, 3);

        switch (pilih) {
            case 1:
                PesanTiket();
                break;
            case 2:
                menuAdminRute();
                break;
            case 3:
                break;
        }

        gotoxy(3, 19); printf("====== Anda Log Out ======");
        getchar();
        getchar();
        return;
    }
}




static void menuManager() {
    int pilih;

    while (1) {
        clearscreen();
        fillBackground(0x90);
        printBorder(1, 1, 153, 43);
        FrameYangTengah(31, 1, 43);
        FrameYangHider(1,9,153);
        tampilanlogin("GAMBARASCI.txt", 60, 3);
        gotoxy(8,5); printf("Kelompok 5");



        gotoxy(3, 11);printf("===== MENU MANAGER =====\n");
        gotoxy(3, 13);printf("[1] Lihat Laporan\n");
        gotoxy(3, 15);printf("[2] Lihat Pendapatan\n");
        gotoxy(3, 17);printf("[3] Log Out\n");
        pilih = menuNavigasi(3, 13, 3);

        switch (pilih) {
            case 1:
                // Laporan();
                break;
            case 2:
                // Pendapatan();
                break;
            case 3:
                break;
        }

        gotoxy(3, 19); printf("====== Anda Log Out ======");
        getchar();
        getchar();
        return;
    }
}

#endif
