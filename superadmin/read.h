#ifndef PROJEK_READ_H
#define PROJEK_READ_H
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "../FrameTabel.h"
#include "update.h"

void baca() {
    FILE *fp;
    staff data;

    int startX = 35;
    int row = 12;

    int wNo = 3;
    int wUsr = 15;
    int wPw = 10;
    int wGen = 13;
    int wTgl = 12;
    int wTelp = 13;

    fp = fopen("staff.dat", "rb");
    if (!fp) {
        gotoxy(startX, row); printf("File staff.dat tidak ditemukan!");
        return;
    }

    // Hitung lebar kolom berdasarkan data
    while (fread(&data, sizeof(staff), 1, fp) == 1) {
        if (strlen(data.username) > wUsr) wUsr = strlen(data.username);
        if (strlen(data.password) > wPw)  wPw  = strlen(data.password);
        if (strlen(data.gender)   > wGen) wGen = strlen(data.gender);
        if (strlen(data.tgl)      > wTgl) wTgl = strlen(data.tgl);
        if (strlen(data.notlpn)   > wTelp) wTelp = strlen(data.notlpn);
    }

    rewind(fp);

    // Total width tanpa kolom ID
    int totalWidth = 1 + (wNo+3) + (wUsr+3) + (wPw+3) + (wGen+3) + (wTgl+3) + (wTelp+3);

    char line[255];
    memset(line, '=', totalWidth);
    line[totalWidth] = '\0';

    // Header tabel
    gotoxy(startX, row++);
    printf("%s", line);

    gotoxy(startX, row++);
    printf("| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |",
           wNo,  "No",
           wUsr, "Nama Lengkap",
           wPw,  "Kata Sandi",
           wGen, "Jenis Kelamin",
           wTgl, "Tgl Lahir",
           wTelp,"No Telepon"
    );

    gotoxy(startX, row++);
    printf("%s", line);

    // Isi tabel
    int no = 1;
    while (fread(&data, sizeof(staff), 1, fp) == 1) {
        // Ubah password menjadi asterisk
        char maskedPassword[255];
        int pwLen = strlen(data.password);
        for (int i = 0; i < pwLen && i < 254; i++) {
            maskedPassword[i] = '*';
        }
        maskedPassword[pwLen] = '\0';

        gotoxy(startX, row++);
        printf("| %-*d | %-*s | %-*s | %-*s | %-*s | %-*s |",
               wNo,  no++,
               wUsr, data.username,
               wPw,  maskedPassword,
               wGen, data.gender,
               wTgl, data.tgl,
               wTelp,data.notlpn
        );
    }

    gotoxy(startX, row++);
    printf("%s", line);

    fclose(fp);
}

#endif