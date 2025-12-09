//
// Created by ASUS on 12/8/2025.
//

#ifndef PROJEK_MENUKATEGORI_H
#define PROJEK_MENUKATEGORI_H

#include "../FrameTabel.h"
#include "create.h"
#include "delete.h"
#include "update.h"

static void buatkategori();
static void editkategori();
static void hapuskategori();

//=========================================
//prosedur untuk menu pilihan pada kategori
//=========================================
static void pilihkategori() {
    int pilih;

    while (1) {
        clearscreen();
        fillBackground(0x90);
        printBorder(1, 1, 153, 43);
        FrameYangTengah(31, 1, 43);
        FrameYangHider(1,9,153);
        tampilanlogin("GAMBARASCI.txt", 60, 3);
        gotoxy(8,5); printf("Kelompok 5");
        //BentukFrame(14, 13, 60, 10);

        gotoxy(3,11); printf("===== DAFTAR KATEGORI =====");
        gotoxy(5,13); printf("   Create");
        gotoxy(5,15); printf("   Edit");
        gotoxy(5,17); printf("   Delete");
        gotoxy(5,19); printf("   Kembali");
        pilih = menuNavigasi(4,13,5);

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
                // menuSuperAdmin();
                break;
        }
    }
}

#endif //PROJEK_MENUKATEGORI_H