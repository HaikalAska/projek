#ifndef RUTE_MENU_H
#define RUTE_MENU_H

#include "../FrameTabel.h"
#include <stdio.h>
#include "../PesanTiket.h"
#include "../Menu.h"
#include <string.h>
#include <conio.h>
#include "createRute.h"
#include "deleteRute.h"
#include "updateRute.h"
#include "readRute.h"

// ================ STRUKTUR DATA ================


void tampilkanSemuaRute();
void tambahRuteBaru();
void editRute();
void hapusRute();
void cariRute();


// Data Global
Rute daftarRute[100];
int jumlahRute = 0;

// ================ FUNGSI DASAR ================
void buatrutejir() {
    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);
    gotoxy(8,5); printf("Kelompok 5");
}

// ================ MENU ADMIN RUTE ================
void menuAdminRute() {

    int pilih;
    do {
        clearscreen();
        fillBackground(0x90);
        printBorder(1, 1, 153, 43);
        FrameYangTengah(31, 1, 43);
        FrameYangHider(1,9,153);
        tampilanlogin("GAMBARASCI.txt", 60, 3);
        gotoxy(8,5); printf("Kelompok 5");
        // tampilkanSemuaRute();

        // Header
        gotoxy(3, 11); printf("==========================");
        gotoxy(3, 12); printf("    MANAJEMEN RUTE BUS    ");
        gotoxy(3, 13); printf("==========================");

        // Menu pilihan
        gotoxy(3, 15); printf("   Lihat Semua Rute");
        gotoxy(3, 17); printf("   Tambah Rute Baru");
        gotoxy(3, 19); printf("   Edit Rute");
        gotoxy(3, 21); printf("   Hapus Rute");
        gotoxy(3, 23); printf("   Cari Rute");
        gotoxy(3, 25); printf("   Kembali ke Menu Utama");

        pilih = menuNavigasi(6, 15, 3);

        // Deklarasi fungsi dari header lain

        switch(pilih) {
            case 1:
                tampilkanSemuaRute();
                break;
            case 2:
                buatRute();
                break;
            case 3:
                editRute();
                break;
            case 4:
                hapusRute();
                break;
            case 5:

                break;
            case 0:
                return;
            default:
                gotoxy(55, 25); printf("Pilihan tidak valid!");
                getch();
        }
    } while (pilih != 0);
}

#endif