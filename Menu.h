#ifndef PROJEK_MENU_H
#define PROJEK_MENU_H
#include "FrameTabel.h"
#include "PesanTiket.h"


static void tampilanMenu() {
    char filename [50];
    int pilihan;


    while (1) {
        clearscreen();
        fillBackground(0x90);
        printBorder(1, 1, 153, 43);
        FrameYangTengah(31, 1, 43);
        FrameYangHider(1,9,153);
        tampilanlogin("GAMBARASCI.txt", 60, 3);

        gotoxy(8,5);
        printf("Kelompok 5");

        gotoxy(3,11);
        printf("[1] Pemesanan Tiket");
        gotoxy(3,13);
        printf("[2] Reffund");
        gotoxy(3,15);
        printf("[3] Kelola Data Dan Laporan");
        gotoxy(3,17);
        printf("[4] Info Pribadi");
        gotoxy(3,19);
        printf("[5] Log Out");

        pilihan = menuNavigasi(5, 11, 3);

        // pilihan hasil dari 0–4
        switch (pilihan) {
            case 0:
                PesanTiket();
                break;

            case 1:
                // Refund();
                break;

            case 2:
                // KelolaData();
                break;

            case 3:
                // InfoPribadi();
                break;

            case 4:
                printf("Logout berhasil!");
                getchar();
                getchar();
                return;
        }
    }

    getchar();
    getchar();
};
#endif
