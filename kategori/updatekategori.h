//
// Created by ASUS on 12/8/2025.
//

#ifndef PROJEK_UPDATEKATEGORI_H
#define PROJEK_UPDATEKATEGORI_H

#include "createkategori.h"
//=========================================
//prosedur untuk mengedit file kategori.dat
//=========================================
void editkategori() {
    char lanjut;
    char cariID[50];
    kategori k;

    do {
        clearLine(11,60,70);
        clearLine(13,35,70);
        clearLine(14,35,70);
        clearLine(16,35,70);
        clearLine(17,35,70);
        clearLine(19,35,70);
        clearLine(21,35,70);

        FILE *fp = fopen("kategori.dat", "rb+");
        if (fp == NULL) {
            gotoxy(35,11); printf("File tidak ditemukan!");
            return;
        }

        gotoxy(35,11);
        printf("ID yang ingin disunting : ");
        scanf("%s", cariID);
        getchar();

        int ketemu = 0;
        long posisi;

        // cari datanya
        while (fread(&k, sizeof(kategori), 1, fp)) {
            if (strcmp(k.id, cariID) == 0) {
                ketemu = 1;

                // simpan posisi data
                posisi = ftell(fp) - sizeof(kategori);

                gotoxy(35,13); printf("Kategori sebelumnya      : %s", k.nama);
                gotoxy(35,14); printf("Deskripsi sebelumnya     : %s", k.deskripsi);

                gotoxy(35,16); printf("Kategori baru            : ");
                scanf(" %[^\n]", k.nama);

                gotoxy(35,17); printf("Deskripsi baru           : ");
                scanf(" %[^\n]", k.deskripsi);

                // kembali ke posisi data
                fseek(fp, posisi, SEEK_SET);
                fwrite(&k, sizeof(kategori), 1, fp);

                gotoxy(35,19); printf("Kategori berhasil diupdate!!");
                break;
            }
        }

        if (!ketemu) {
            gotoxy(35,19); printf("ID tidak ditemukan!!");
        }

        fclose(fp);

        gotoxy(35,21);
        printf("Edit kategori lain? (y/n) : ");
        scanf(" %c", &lanjut);

    } while (lanjut == 'y' || lanjut == 'Y');
}


#endif //PROJEK_UPDATE_H