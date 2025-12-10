//
// Created by ASUS on 12/8/2025.
//

#ifndef PROJEK_READKATEGORI_H
#define PROJEK_READKATEGORI_H

#include "createkategori.h"

void generateDummyKategori50() {
    FILE *fp = fopen("kategori.dat", "wb");
    if (fp == NULL) return;

    kategori dummy;
    for (int i = 1; i <= 50; i++) {
        sprintf(dummy.id, "%03d", i);   // ID 001–050
        strcpy(dummy.nama, "VIP");
        strcpy(dummy.deskripsi, "Kategori VIP dengan kualitas bagus");
        fwrite(&dummy, sizeof(kategori), 1, fp);
    }

    fclose(fp);
}

int pageKategori = 1; // halaman saat ini

void readkategori(int page) {
    FILE *fp = fopen("kategori.dat", "rb");
    if (fp == NULL) {
        gotoxy(30,10); printf("File kategori.dat tidak ditemukan!");
        return;
    }

    kategori k;
    int index = 0;
    int start = (page - 1) * 20;
    int end = start + 20;

    int no = start + 1;
    int y = 11;

    gotoxy(35, y++); printf("+----+------------+----------------------+------------------------------------------+");
    gotoxy(35, y++); printf("| No | ID         | Nama Kategori        | Deskripsi                                |");
    gotoxy(35, y++); printf("+----+------------+----------------------+------------------------------------------+");

    while (fread(&k, sizeof(kategori), 1, fp)) {

        if (index >= start && index < end) {
            gotoxy(35, y++);
            printf("| %-2d | %-10s | %-20s | %-40s |", no, k.id, k.nama, k.deskripsi);
            no++;
        }
        index++;
    }

    gotoxy(35, y++);
    printf("+----+------------+----------------------+------------------------------------------+");

    fclose(fp);

    int totalPage = (index + 9) / 10;
    gotoxy(35, y+1);
    printf("Halaman %d / %d", page, totalPage);
}



#endif //PROJEK_READ_H