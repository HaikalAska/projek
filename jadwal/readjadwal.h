#ifndef PROJEK_READJADWAL_H
#define PROJEK_READJADWAL_H

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "../FrameTabel.h"
#include "createjadwal.h"

#define MAX_ROWS_PER_PAGE 8
#define MAX_DATA 1000

// ================== BUAT DATA DUMMY ==================
void buatDummyJadwal() {

    FILE *fp = fopen("jadwal.dat", "wb");
    if (!fp) return;

    jadwal j;

    char *kota[] = {
        "Jakarta","Bekasi","Bandung","Cirebon","Semarang",
        "Yogyakarta","Solo","Surabaya","Malang","Kediri"
    };

    char *armada[] = { "Agramas", "Blue Star", "Blue Bird", "Adi Putro" };
    char *kategori[] = { "Ekonomi", "Bisnis", "Eksekutif" };
    char *jam[] = {
        "06:00","08:30","10:00","12:00","14:30",
        "16:00","18:00","19:30","21:00"
    };

    for (int i = 0; i < 50; i++) {

        strcpy(j.kotaAsal, kota[i % 10]);
        strcpy(j.kotaTujuan, kota[(i + 1) % 10]);
        strcpy(j.armada, armada[i % 3]);
        strcpy(j.kategori, kategori[i % 3]);
        strcpy(j.jamBerangkat, jam[i % 9]);

        sprintf(j.tanggal, "%02d/12/2025", (i % 28) + 1);
        j.harga = 75000 + (i * 5000);

        fwrite(&j, sizeof(jadwal), 1, fp);
    }

    fclose(fp);
}

// ================== BACA JADWAL ==================
void bacaJadwal() {

    FILE *fp;
    jadwal all_jadwal[MAX_DATA];
    int total_data = 0;

    int startX = 37;
    int startY = 12;

    int wNo = 3, wAwal = 15, wAkhir = 15, wArmada = 15;
    int wTgl = 12, wKategori = 10, wJam = 8, wHarga = 12;

    int current_page = 1;
    int total_pages = 1;
    char key;

    bentukframe(34, 11, 121, 35);

    // ===== CEK FILE, JIKA TIDAK ADA → BUAT DUMMY =====
    fp = fopen("jadwal.dat", "rb");
    if (!fp) {
        buatDummyJadwal();
        fp = fopen("jadwal.dat", "rb");
    }

    if (!fp) {
        gotoxy(startX, startY);
        printf("Gagal membuka jadwal.dat");
        getch();
        return;
    }

    jadwal data;
    while (fread(&data, sizeof(jadwal), 1, fp) == 1) {
        all_jadwal[total_data++] = data;
    }
    fclose(fp);

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

        gotoxy(startX, row++); printf("%s", line);
        gotoxy(startX, row++);
        printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
            wNo+1,"No", wAwal+1,"Kota Awal", wAkhir+1,"Kota Akhir",
            wArmada+1,"Armada", wTgl+1,"Tanggal",
            wKategori+1,"Kategori", wJam+1,"Jam", wHarga+1,"Harga"
        );
        gotoxy(startX, row++); printf("%s", line);

        int start = (current_page - 1) * MAX_ROWS_PER_PAGE;
        int end = start + MAX_ROWS_PER_PAGE;
        if (end > total_data) end = total_data;

        for (int i = start; i < end; i++) {
            char hargaStr[25];
            formatHarga(all_jadwal[i].harga, hargaStr);

            gotoxy(startX, row++);
            printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
                wNo+1, i+1,
                wAwal+1, all_jadwal[i].kotaAsal,
                wAkhir+1, all_jadwal[i].kotaTujuan,
                wArmada+1, all_jadwal[i].armada,
                wTgl+1, all_jadwal[i].tanggal,
                wKategori+1, all_jadwal[i].kategori,
                wJam+1, all_jadwal[i].jamBerangkat,
                wHarga+1, hargaStr
            );
        }

        gotoxy(startX, row++); printf("%s", line);

        bentukframe(3, 11, 27, 12);
        gotoxy(6, 13); printf("[SPASI] Lanjut");
        gotoxy(6, 15); printf("[BACKSPACE] Kembali");
        gotoxy(6, 17); printf("[ENTER] Keluar");
        gotoxy(6, 19); printf("Halaman: %d/%d", current_page, total_pages);
        gotoxy(6, 21); printf("Total  : %d data", total_data);

        key = getch();
        if (key == ' ' && current_page < total_pages) current_page++;
        else if (key == 8 && current_page > 1) current_page--;

    } while (key != 13);
}

#endif