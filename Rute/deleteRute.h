#ifndef PROJEK_DELETERUTE_H
#define PROJEK_DELETERUTE_H

#include <stdio.h>
#include "createRute.h"

void hapusRute() {
    char id[20];
    int found = 0;

    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);
    gotoxy(8,5); printf("Kelompok 5");

    FILE *rutefile = fopen("rute.dat", "rb");
    FILE *tempfile = fopen("temp.dat", "wb");

    if (!rutefile || !tempfile) return;

    clearscreen();
    gotoxy(35, 11); printf("Masukkan ID Rute yang ingin dihapus: ");
    scanf("%s", id);

    Rute r;
    while (fread(&r, sizeof(Rute), 1, rutefile)) {
        if (strcmp(r.id, id) != 0) {
            fwrite(&r, sizeof(Rute), 1, tempfile);
        } else {
            found = 1;
        }
    }

    fclose(rutefile);
    fclose(tempfile);

    remove("rute.dat");
    rename("temp.dat", "rute.dat");

    gotoxy(35, 15);
    if (found)
        printf("Rute berhasil dihapus!");
    else
        printf("ID tidak ditemukan!");

    getch();
}

#endif
