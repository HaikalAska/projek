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

    int startX = 50;
    int row    = 12;   // baris pertama tabel
    int count  = 0;

    // Hitung jumlah data
    fp = fopen("staff.dat", "rb");
    while (fread(&data, sizeof(staff), 1, fp) == 1) {
        count++;
    }
    fclose(fp);

    // Tentukan lebar kolom
    int maxUsr = 8;
    int maxPw  = 8;
    int maxid  = 8;

    fp = fopen("staff.dat", "rb");
    while (fread(&data, sizeof(staff), 1, fp) == 1) {
        int lenUsr = strlen(data.username);
        int lenPw  = strlen(data.password);
        int lenid  = strlen(data.id);

        if (lenUsr > maxUsr) maxUsr = lenUsr;
        if (lenPw  > maxPw ) maxPw  = lenPw;
        if (lenid  > maxid ) maxid  = lenid;
    }
    fclose(fp);

    // Hitung panjang garis
    int totalWidth = 6 + maxid + maxUsr + maxPw + 6;

    char line[300];
    memset(line, '=', totalWidth);
    line[totalWidth] = '\0';

    // HEADER LINE
    gotoxy(startX, row);
    printf("%s", line);
    row++;

    // HEADER TEXT
    gotoxy(startX, row);
    printf("| %-2s | %-*s | %-*s | %-*s|",
           "No",
           maxid, "ID",
           maxUsr, "Username",
           maxPw,  "Password");
    row++;

    // HEADER BOTTOM LINE
    gotoxy(startX, row);
    printf("%s", line);
    row++;

    // ISI DATA
    fp = fopen("staff.dat", "rb");
    int no = 1;

    while (fread(&data, sizeof(staff), 1, fp) == 1) {

        gotoxy(startX, row);
        printf("| %-2d | %-*s | %-*s | %-*s|",
               no++,
               maxid,  data.id,
               maxUsr, data.username,
               maxPw,  data.password);

        row++;
    }
    fclose(fp);

    // FOOTER LINE
    gotoxy(startX, row);
    printf("%s", line);
}

#endif
