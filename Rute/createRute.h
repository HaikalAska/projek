#ifndef PROJEK_CREATERUTES_H
#define PROJEK_CREATERUTES_H

#include <stdio.h>
#include "../FrameTabel.h"

typedef struct {
    char id[5];
    char kotaAwal[50];
    char kotaTujuan[50];
    int harga;
} Rute;

//======================================
// Prosedur untuk input data rute.dat
//======================================
void buatRute() {
    char lanjut;
    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);
    gotoxy(8,5); printf("Kelompok 5");

    do {
        // Bersihin area tengah supaya input selalu fresh
        for (int y = 10; y <= 27; y++) {
            clearLine(y, 35, 95);
        }

        FILE *rutefile = fopen("rute.dat", "ab");
        Rute r;

        // =======================
        //    HEADER FORM
        // =======================
        gotoxy(35, 10); printf("============================================");
        gotoxy(35, 11); printf("            FORM INPUT DATA RUTE            ");
        gotoxy(35, 12); printf("============================================");

        // =======================
        //       INPUT AREA
        // =======================
        gotoxy(35, 14); printf("ID Rute        : ");
        scanf("%s", r.id);

        gotoxy(35, 16); printf("Kota Awal      : ");
        scanf("%s", r.kotaAwal);

        gotoxy(35, 18); printf("Kota Tujuan    : ");
        scanf("%s", r.kotaTujuan);

        gotoxy(35, 20); printf("Harga          : ");
        scanf("%d", &r.harga);

        fwrite(&r, sizeof(Rute), 1, rutefile);
        fclose(rutefile);

        // =======================
        //   NOTIF BERHASIL
        // =======================
        gotoxy(35, 22); printf("============================================");
        gotoxy(35, 23); printf("       ✓  Rute berhasil dibuat!            ");
        gotoxy(35, 24); printf("============================================");

        gotoxy(35, 26); printf("Tambah lagi? (y/n) : ");
        scanf(" %c", &lanjut);

    } while (lanjut == 'y' || lanjut == 'Y');
}

#endif
