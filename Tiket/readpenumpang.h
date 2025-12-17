#ifndef PROJEK_READPENUMPANG_H
#define PROJEK_READPENUMPANG_H

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "../FrameTabel.h"
#include "createTiket.h"

// ===== Paging =====
#define MAX_ROWS_PER_PAGE 8

void readpenumpang() {

    FILE *fp;
    penumpang all_data[1000];
    int total_data = 0;

    int startX = 47;
    int startY = 12;

    // ===== Lebar kolom =====
    int wNo    = 3;
    int wNama  = 18;
    int wHP    = 14;
    int wRute  = 8;
    int wEmail = 30;

    int current_page = 1;
    int total_pages = 1;
    char key;

    bentukframe(34, 11, 121, 35);

    // ===== Buka file =====
    fp = fopen("penumpang.dat", "rb");
    if (!fp) {
        gotoxy(startX, startY);
        printf("File penumpang.dat tidak ditemukan!");
        getch();
        return;
    }

    penumpang data;
    while (fread(&data, sizeof(penumpang), 1, fp)) {
        if (total_data < 1000) {
            all_data[total_data++] = data;
        }
    }
    fclose(fp);

    if (total_data > 0) {
        total_pages = (total_data + MAX_ROWS_PER_PAGE - 1) / MAX_ROWS_PER_PAGE;
    }

    // ===== Garis tabel =====
    int totalWidth = 1 +
                     (wNo+2) +
                     (wNama+2) +
                     (wHP+2) +
                     (wRute+2) +
                     (wEmail+7);

    char line[200];
    memset(line, '-', totalWidth);
    line[totalWidth] = '\0';

    do {
        clearArea(startX, startY, totalWidth + 5, MAX_ROWS_PER_PAGE + 10);

        gotoxy(78, 13);
        printf("=== DAFTAR PENUMPANG ===");

        int row = startY + 2;

        gotoxy(startX, row++);
        printf("%s", line);

        // ===== HEADER TABEL (TANPA ID) =====
        gotoxy(startX, row++);
        printf("| %-*s | %-*s | %-*s | %-*s | %-*s |",
               wNo,    "No",
               wNama,  "Nama",
               wHP,    "No HP",
               wRute,  "Rute",
               wEmail, "Email"
        );

        gotoxy(startX, row++);
        printf("%s", line);

        int start_index = (current_page - 1) * MAX_ROWS_PER_PAGE;
        int end_index = start_index + MAX_ROWS_PER_PAGE;
        if (end_index > total_data) end_index = total_data;

        // ===== ISI DATA =====
        for (int i = start_index; i < end_index; i++) {
            penumpang p = all_data[i];

            gotoxy(startX, row++);
            printf("| %-*d | %-*s | %-*s | %-*s | %-*s |",
                   wNo,    i + 1,
                   wNama,  p.nama,
                   wHP,    p.no_hp,
                   wRute,  p.rute,
                   wEmail, p.email
            );
        }

        gotoxy(startX, row++);
        printf("%s", line);

        // ===== NAVIGASI =====
        bentukframe(3, 11, 27, 12);
        gotoxy(6, 13); printf("[SPASI] Lanjut");
        gotoxy(6, 15); printf("[BACKSPACE] Kembali");
        gotoxy(6, 17); printf("[ENTER] Keluar");
        gotoxy(6, 19); printf("Halaman: %d/%d", current_page, total_pages);
        gotoxy(6, 21); printf("Total  : %d data", total_data);

        key = getch();

        if (key == ' ') {
            if (current_page < total_pages) current_page++;
        }
        else if (key == 8) {
            if (current_page > 1) current_page--;
        }

    } while (key != 13);
}

#endif
