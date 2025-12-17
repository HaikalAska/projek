#ifndef PROJEK_READJADWAL_H
#define PROJEK_READJADWAL_H

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "../FrameTabel.h"
#include "createjadwal.h"

#define MAX_ROWS_PER_PAGE 8

void bacaJadwal() {

    FILE *fp;
    jadwal all_jadwal[1000];
    int total_data = 0;

    int startX = 37;
    int startY = 12;

    // Lebar kolom
    int wNo      = 3;
    int wAwal    = 15;
    int wAkhir   = 15;
    int wArmada  = 15;
    int wTgl     = 12;
    int wKategori= 10;
    int wJam     = 8;
    int wHarga   = 12;

    int current_page = 1;
    int total_pages = 1;
    char key;

    bentukframe(34, 11, 121, 35);

    fp = fopen("jadwal.dat", "rb");
    if (!fp) {
        gotoxy(startX, startY);
        printf("File jadwal.dat tidak ditemukan!");
        getch();
        return;
    }

    jadwal data;
    while (fread(&data, sizeof(jadwal), 1, fp) == 1) {
        all_jadwal[total_data++] = data;
    }
    fclose(fp);

    if (total_data > 0)
        total_pages = (total_data + MAX_ROWS_PER_PAGE - 1) / MAX_ROWS_PER_PAGE;

    int totalWidth =
        1 + (wNo+2) + (wAwal+2) + (wAkhir+2) + (wArmada+2) +
        (wTgl+2) + (wKategori+2) + (wJam+2) + (wHarga+1);

    char line[250];
    memset(line, '-', totalWidth);
    line[totalWidth] = '\0';

    do {
        clearArea(startX, startY, totalWidth + 5, MAX_ROWS_PER_PAGE + 10);

        gotoxy(70, 13);
        printf("=== DAFTAR JADWAL ===");

        int row = startY + 2;

        gotoxy(startX, row++);
        printf("%s", line);

        gotoxy(startX, row++);
        printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
            wNo+1,      "No",
            wAwal+1,    "Kota Awal",
            wAkhir+1,   "Kota Akhir",
            wArmada+1,  "Armada",
            wTgl+1,     "Tanggal",
            wKategori+1,"Kategori",
            wJam+1,     "Jam",
            wHarga+1,   "Harga"
        );

        gotoxy(startX, row++);
        printf("%s", line);

        int start_index = (current_page - 1) * MAX_ROWS_PER_PAGE;
        int end_index = start_index + MAX_ROWS_PER_PAGE;
        if (end_index > total_data) end_index = total_data;

        for (int i = start_index; i < end_index; i++) {

            char hargaStr[25];
            formatHarga(all_jadwal[i].harga, hargaStr);

            gotoxy(startX, row++);
            printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
                wNo+1,      i + 1,
                wAwal+1,    all_jadwal[i].kotaAsal,
                wAkhir+1,   all_jadwal[i].kotaTujuan,
                wArmada+1,  all_jadwal[i].armada,
                wTgl+1,     all_jadwal[i].tanggal,
                wKategori+1,all_jadwal[i].kategori,
                wJam+1,     all_jadwal[i].jamBerangkat,
                wHarga+1,   hargaStr
            );
        }

        gotoxy(startX, row++);
        printf("%s", line);

        // Panel Navigasi
        bentukframe(3, 11, 27, 12);
        gotoxy(6, 13); printf("[SPASI] Lanjut");
        gotoxy(6, 15); printf("[BACKSPACE] Kembali");
        gotoxy(6, 17); printf("[ENTER] Keluar");
        gotoxy(6, 19); printf("Halaman: %d/%d", current_page, total_pages);
        gotoxy(6, 21); printf("Total  : %d data", total_data);

        key = getch();

        if (key == ' ' && current_page < total_pages)
            current_page++;
        else if (key == 8 && current_page > 1)
            current_page--;

    } while (key != 13);
}

#endif
