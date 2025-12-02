#ifndef PROJEK_MENU_H
#define PROJEK_MENU_H
#include "login.h"
#include "FrameTabel.h"
#include "PesanTiket.h"


static void tampilanMenu() {
    char filename [50];
    int pilihan;
    clearscreen();
    fillBackground(0x70);
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
    gotoxy(3,23);
    printf("Masukkan pilihan [1-4]: ");
    scanf("%d", &pilihan);

    if (pilihan == 1) {
        PesanTiket();
    }

    getchar();
    getchar();
};
#endif
