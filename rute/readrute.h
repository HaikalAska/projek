//
// Created by ASUS on 12/14/2025.
//

#ifndef PROJEK_READRUTE_H
#define PROJEK_READRUTE_H

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "../FrameTabel.h"

#define MAX_ROWS_PER_PAGE 10

// ==================================================
// FORMAT HARGA RUPIAH (AMAN, TIDAK DOBEL .000)
// ==================================================
void formatHarga(int harga, char *out) {
    int juta = harga / 1000000;
    int ribu = (harga / 1000) % 1000;
    int sisa = harga % 1000;

    if (juta > 0) {
        sprintf(out, "Rp%d.%03d.%03d,00", juta, ribu, sisa);
    }
    else if (ribu > 0) {
        sprintf(out, "Rp%d.%03d,00", ribu, sisa);
    }
    else {
        sprintf(out, "Rp%d,00", sisa);
    }
}

// ==================================================
// BACA DATA RUTE + PAGING
// ==================================================
void bacaRute() {

    FILE *fp;
    Rute all_rute[1000];
    int total_rute = 0;

    int startX = 37;
    int startY = 12;

    // Lebar kolom
    int wNo = 3;
    int wAsal = 18;
    int wTujuan = 18;
    int wHarga = 18;
    int wBerangkat = 12;
    int wTiba = 12;
    int wStatus = 12;

    int current_page = 1;
    int total_pages = 1;
    char key;

    bentukframe(34, 11, 121, 35);

    // ===== BUKA FILE =====
    fp = fopen("rute.dat", "rb");
    if (!fp) {
        gotoxy(startX, startY);
        printf("File rute.dat tidak ditemukan!");
        getch();
        return;
    }

    while (fread(&all_rute[total_rute], sizeof(Rute), 1, fp) == 1) {
        if (total_rute < 1000) total_rute++;
    }
    fclose(fp);

    for (int i = 0; i < total_rute - 1; i++) {
        for (int j = i + 1; j < total_rute; j++) {
            if (strcmp(all_rute[i].id, all_rute[j].id) < 0) {
                Rute temp = all_rute[i];
                all_rute[i] = all_rute[j];
                all_rute[j] = temp;
            }
        }
    }


    if (total_rute > 0) {
        total_pages = (total_rute + MAX_ROWS_PER_PAGE - 1) / MAX_ROWS_PER_PAGE;
    }

    int totalWidth = 1 + (wNo+2) + (wAsal+2) + (wTujuan+2)
                   + (wHarga+2) + (wBerangkat+2) + (wTiba+2) + (wStatus+2);

    char line[200];
    memset(line, '-', totalWidth);
    line[totalWidth] = '\0';

    // ===== LOOP TAMPIL =====
    do {
        clearArea(startX, startY, totalWidth + 5, MAX_ROWS_PER_PAGE + 12);

        gotoxy(80, 13);
        printf("=== DAFTAR RUTE ===");

        int row = startY + 2;

        gotoxy(startX, row++);
        printf("%s", line);

        gotoxy(startX, row++);
        printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
               wNo+1, "No",
               wAsal+1, "Kota Asal",
               wTujuan+1, "Kota Tujuan",
               wHarga+1, "Harga",
               wBerangkat+1, "Berangkat",
               wTiba+1, "Tiba",
               wStatus+1, "Status");

        gotoxy(startX, row++);
        printf("%s", line);

        int start_index = (current_page - 1) * MAX_ROWS_PER_PAGE;
        int end_index = start_index + MAX_ROWS_PER_PAGE;
        if (end_index > total_rute) end_index = total_rute;

        for (int i = start_index; i < end_index; i++) {
            char hargaStr[25];
            formatHarga((int)all_rute[i].harga, hargaStr);

            gotoxy(startX, row++);
            printf("|%-*d|%-*s|%-*s|%*s|%-*s|%-*s|%-*s|",
                   wNo+1, i + 1,
                   wAsal+1, all_rute[i].kotaAsal,
                   wTujuan+1, all_rute[i].kotaTujuan,
                   wHarga+1, hargaStr,
                   wBerangkat+1, all_rute[i].jamBerangkat,
                   wTiba+1, all_rute[i].jamTiba,
                   wStatus+1, all_rute[i].statusRute);
        }

        gotoxy(startX, row++);
        printf("%s", line);

        // ===== NAVIGASI =====
        bentukframe(3, 11, 27, 12);
        gotoxy(6, 13); printf("[SPASI] Lanjut");
        gotoxy(6, 15); printf("[BACKSPACE] Kembali");
        gotoxy(6, 17); printf("[ENTER] Pilih Menu");
        gotoxy(6, 19); printf("Halaman: %d/%d", current_page, total_pages);
        gotoxy(6, 21); printf("Total  : %d data", total_rute);

        key = getch();

        if (key == ' ' && current_page < total_pages)
            current_page++;
        else if (key == 8 && current_page > 1)
            current_page--;

    } while (key != 13);
}

#endif // PROJEK_READRUTE_H
