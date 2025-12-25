//
// Created by Asus on 16/12/2025.
//

#ifndef PROJEK_READPEMBATALAN_H
#define PROJEK_READPEMBATALAN_H

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "../FrameTabel.h"
#include "createpembatalan.h"

// ===== Paging =====
#define MAX_ROWS_PER_PAGE 8

void readPembatalan() {

    FILE *fp;
    pembatalan all_data[1000];
    int total_data = 0;

    int startX = 47;
    int startY = 12;

    // ===== Lebar kolom =====
    int wNo          = 3;
    int wIdPesan     = 15;
    int wRefund      = 15;

    int current_page = 1;
    int total_pages = 1;
    char key;

    bentukframe(34, 11, 121, 35);

    // ===== Buka file =====
    fp = fopen("pembatalan.dat", "rb");
    if (!fp) {
        gotoxy(startX, startY);
        printf("File pembatalan.dat tidak ditemukan!");
        getch();
        return;
    }

    pembatalan data;
    while (fread(&data, sizeof(pembatalan), 1, fp)) {
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
                     (wNo + 2) +
                     (wIdPesan + 2) +
                     (wRefund + 5);

    char line[200];
    memset(line, '-', totalWidth);
    line[totalWidth] = '\0';

    do {
        clearArea(startX, startY, totalWidth + 5, MAX_ROWS_PER_PAGE + 10);

        gotoxy(78, 13);
        printf("=== DAFTAR PEMBATALAN ===");

        int row = startY + 2;

        gotoxy(startX, row++);
        printf("%s", line);

        // ===== HEADER =====
        gotoxy(startX, row++);
        printf("| %-*s | %-*s | %-*s |",
               wNo,      "No",
               wIdPesan, "ID Pemesanan",
               wRefund,  "Pengembalian"
        );

        gotoxy(startX, row++);
        printf("%s", line);

        int start_index = (current_page - 1) * MAX_ROWS_PER_PAGE;
        int end_index = start_index + MAX_ROWS_PER_PAGE;
        if (end_index > total_data) end_index = total_data;

        // ===== ISI DATA =====
        for (int i = start_index; i < end_index; i++) {
            pembatalan p = all_data[i];

            gotoxy(startX, row++);
            printf("| %-*d | %-*s | %-*.0f%% |",
                   wNo,      i + 1,
                   wIdPesan, p.id_pemesanan,
                   wRefund - 1, p.pengembalian*100
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



#endif //PROJEK_READPEMBATALAN_H