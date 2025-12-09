//
// Created by ASUS on 12/8/2025.
//

#ifndef PROJEK_UPDATE_H
#define PROJEK_UPDATE_H

#include "create.h"
//=========================================
//prosedur untuk mengedit file kategori.dat
//=========================================
static void editkategori() {
    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);
    gotoxy(8,5); printf("Kelompok 5");
    BentukFrame(34, 11, 60, 13);

    FILE *kategorifile = fopen("kategori.dat", "rb+");

    int idCari;
    kategori k;
    int found = 0;

    gotoxy(51,12);printf("===== Edit Kategori =====");

    gotoxy(36, 14); printf("ID yang ingin di edit : ");
    scanf("%d", &idCari);
    getchar();

    rewind(kategorifile);

    while (fread(&k, sizeof(kategori), 1, kategorifile)) {
        if (k.id == idCari) {
            found = 1;

            gotoxy(36, 16); printf("Nama kategori lama : %s", k.nama);
            gotoxy(36, 17); printf("Deskripsi lama     : %s", k.deskripsi);

            gotoxy(36, 19); printf("Nama kategori baru : ");
            fgets(k.nama, sizeof(k.nama), stdin);
            k.nama[strcspn(k.nama, "\n")] = '\0';

            gotoxy(36, 21); printf("Deskripsi baru     : ");
            fgets(k.deskripsi, sizeof(k.deskripsi), stdin);
            k.deskripsi[strcspn(k.deskripsi, "\n")] = '\0';

            fseek(kategorifile, -sizeof(kategori), SEEK_CUR);

            fwrite(&k, sizeof(kategori), 1, kategorifile);

            gotoxy(36, 24); printf("Data berhasil diperbarui!\n");
            break;
        }
    }

    if (!found) {
        gotoxy(36, 24); printf("Kategori dengan ID %d tidak ditemukan!\n", idCari);
    }

    fclose(kategorifile);
}

#endif //PROJEK_UPDATE_H