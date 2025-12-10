//
// Created by ASUS on 12/8/2025.
//

#ifndef PROJEK_DELETEKATEGORI_H
#define PROJEK_DELETEKATEGORI_H


#include "createkategori.h"

//=================================================================
//prosedur untuk menghapus data yang ada di dalam file kategori.dat
//=================================================================
//=======================================
// prosedur untuk hapus data kategori.dat
//=======================================
void hapuskategori() {
    char lanjut;
    char cariID[50];
    kategori k;

    do {
        clearLine(11,35,70);
        clearLine(13,35,80);
        clearLine(15,35,70);

        FILE *fp = fopen("kategori.dat", "rb");
        if (fp == NULL) {
            gotoxy(35,11); printf("File kategori.dat tidak ditemukan!");
            return;
        }

        gotoxy(35,11);
        printf("ID yang ingin dihapus : ");
        scanf("%s", cariID);

        FILE *temp = fopen("temp.dat", "wb");
        int ketemu = 0;

        // Baca semua data kategori
        while (fread(&k, sizeof(kategori), 1, fp)) {
            if (strcmp(k.id, cariID) == 0) {
                ketemu = 1;
                continue; // skip data yang mau dihapus
            }
            fwrite(&k, sizeof(kategori), 1, temp);
        }

        fclose(fp);
        fclose(temp);

        // Ganti file lama
        remove("kategori.dat");
        rename("temp.dat", "kategori.dat");

        if (ketemu) {
            gotoxy(35,13);
            printf("Kategori dengan ID %s berhasil dihapus!!", cariID);
        } else {
            gotoxy(35,13);
            printf("ID tidak ditemukan!");
        }

        gotoxy(35,15);
        printf("Hapus kategori lain? (y/n) : ");
        scanf(" %c", &lanjut);

    } while (lanjut == 'y' || lanjut == 'Y');
}


#endif //PROJEK_DELETE_K_H