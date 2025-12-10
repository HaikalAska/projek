#ifndef PROJEK_UPDATERUTE_H
#define PROJEK_UPDATERUTE_H

#include <stdio.h>
#include <string.h>
#include "createRute.h"

void editRute() {
    char lanjut;
    char cariID[50];
    Rute r;

    do {
        // Bersihin area input biar ga numpuk
        clearLine(11, 35, 70);
        clearLine(13, 35, 70);
        clearLine(14, 35, 70);
        clearLine(16, 35, 70);
        clearLine(17, 35, 70);
        clearLine(19, 35, 70);
        clearLine(21, 35, 70);

        FILE *fp = fopen("rute.dat", "rb+");
        if (fp == NULL) {
            gotoxy(35, 11); printf("File tidak ditemukan!");
            return;
        }

        gotoxy(35, 11);
        printf("ID Rute yang ingin diedit : ");
        scanf("%s", cariID);
        getchar(); // bersihin enter

        int ketemu = 0;
        long posisi;

        // cari data rute
        while (fread(&r, sizeof(Rute), 1, fp)) {
            if (strcmp(r.id, cariID) == 0) {
                ketemu = 1;

                // simpan posisi record
                posisi = ftell(fp) - sizeof(Rute);

                gotoxy(35, 13); printf("Kota Awal sebelumnya      : %s", r.kotaAwal);
                gotoxy(35, 14); printf("Kota Tujuan sebelumnya    : %s", r.kotaTujuan);
                gotoxy(35, 15); printf("Harga sebelumnya          : %d", r.harga);

                gotoxy(35, 16); printf("Kota Awal baru            : ");
                scanf("%s", r.kotaAwal);

                gotoxy(35, 17); printf("Kota Tujuan baru          : ");
                scanf("%s", r.kotaTujuan);

                gotoxy(35, 18); printf("Harga baru                : ");
                scanf("%d", &r.harga);

                // kembali ke posisi data lama
                fseek(fp, posisi, SEEK_SET);
                fwrite(&r, sizeof(Rute), 1, fp);

                gotoxy(35, 19); printf("Rute berhasil diupdate!!");
                break;
            }
        }

        if (!ketemu) {
            gotoxy(35, 19); printf("ID tidak ditemukan!!");
        }

        fclose(fp);

        gotoxy(35, 21);
        printf("Edit rute lain? (y/n) : ");
        scanf(" %c", &lanjut);

    } while (lanjut == 'y' || lanjut == 'Y');
}

#endif

