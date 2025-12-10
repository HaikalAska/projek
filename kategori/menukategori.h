//
// Created by ASUS on 12/8/2025.
//

#ifndef PROJEK_MENUKATEGORI_H
#define PROJEK_MENUKATEGORI_H

#include "../FrameTabel.h"
#include "createkategori.h"
#include "deletekategori.h"
#include "updatekategori.h"
#include "readkategori.h"

void buatkategori();
void editkategori();
void hapuskategori();
void readkategori(int page);
void gimik();
//=========================================
//prosedur untuk menu pilihan pada kategori
//=========================================
int pagekategori = 1;

void pilihkategori() {
    int pilih;

    while (1) {
        clearscreen();
        fillBackground(0x90);
        printBorder(1, 1, 153, 43);
        FrameYangTengah(31, 1, 43);
        FrameYangHider(1,9,153);
        tampilanlogin("GAMBARASCI.txt", 60, 3);
        gotoxy(8,5); printf("Kelompok 5");

        // === YANG PENTING ===
        readkategori(pagekategori);

        gotoxy(3,11); printf("== KELOLA DATA KATEGORI ==");
        gotoxy(3,13); printf("   Buat");
        gotoxy(3,15); printf("   Sunting");
        gotoxy(3,17); printf("   Hapus");
        gotoxy(3,19); printf("   Selanjutnya");
        gotoxy(3,21); printf("   Sebelumnya");
        gotoxy(3,23); printf("   Kembali");

        pilih = menuNavigasi(6,13,3);

        clearscreen();
        fillBackground(0x90);
        printBorder(1, 1, 153, 43);
        FrameYangTengah(31, 1, 43);
        FrameYangHider(1,9,153);
        tampilanlogin("GAMBARASCI.txt", 60, 3);
        gotoxy(8,5); printf("Kelompok 5");
        gimik();

        switch (pilih) {
            case 1:
                buatkategori();
                break;
            case 2:
                editkategori();
                break;
            case 3:
                hapuskategori();
                break;
            case 4:
                pagekategori++;
                break;
            case 5:
                if (pagekategori > 1) pagekategori--;
                break;
            case 6:
                return;
        }
    }
}


void gimik() {

    gotoxy(3,11); printf("== KELOLA DATA KATEGORI ==");
    gotoxy(3,13); printf("   Buat");
    gotoxy(3,15); printf("   Sunting");
    gotoxy(3,17); printf("   Hapus");
    gotoxy(3,19); printf("   Selanjutnya");
    gotoxy(3,21); printf("   Sebelumnya");
    gotoxy(3,23); printf("   Kembali");
}

#endif //PROJEK_MENUKATEGORI_H