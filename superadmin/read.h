#ifndef PROJEK_READ_H
#define PROJEK_READ_H
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "../FrameTabel.h"
#include "update.h"

// --- Konstanta untuk Paging ---
#define MAX_ROWS_PER_PAGE 10

void baca() {
    FILE *fp;
    staff all_staff[1000];
    int total_staff = 0;

    int startX = 35;
    int row_start = 12;

    int wNo = 3;
    int wUsr = 15;
    int wPw = 10;
    int wGen = 13;
    int wTgl = 12;
    int wTelp = 13;

    // VARIABEL PAGING
    int current_page = 1;
    int total_pages = 1;
    char key;
    char second_key; // Tambahan untuk menampung kode kedua dari tombol panah

    // --- BACA SEMUA DATA DARI FILE DAN HITUNG LEBAR KOLOM ---
    fp = fopen("staff.dat", "rb");
    if (!fp) {
        gotoxy(startX, row_start); printf("File staff.dat tidak ditemukan!");
        getch();
        return;
    }

    staff data;
    while (fread(&data, sizeof(staff), 1, fp) == 1) {
        if (total_staff < 1000) {
            all_staff[total_staff++] = data;
        }

        // Hitung lebar kolom
        if (strlen(data.username) > wUsr) wUsr = strlen(data.username);
        if (strlen(data.password) > wPw)  wPw  = strlen(data.password);
        if (strlen(data.gender)   > wGen) wGen = strlen(data.gender);
        if (strlen(data.tgl)      > wTgl) wTgl = strlen(data.tgl);
        if (strlen(data.notlpn)   > wTelp) wTelp = strlen(data.notlpn);
    }
    fclose(fp);

    // Hitung total halaman
    if (total_staff > 0) {
        total_pages = (total_staff + MAX_ROWS_PER_PAGE - 1) / MAX_ROWS_PER_PAGE;
    }

    // Total width tabel
    int totalWidth = 1 + (wNo+3) + (wUsr+3) + (wPw+3) + (wGen+3) + (wTgl+3) + (wTelp+3);
    char line[255];
    memset(line, '=', totalWidth);
    line[totalWidth] = '\0';

    // --- LOOP UTAMA UNTUK MENAMPILKAN DAN PAGING ---
    do {
        // Hapus area tabel lama
        for (int i = row_start; i < row_start + MAX_ROWS_PER_PAGE + 5; i++) {
             gotoxy(startX, i); printf("%*s", totalWidth + 5, " ");
        }

        int row = row_start;

        // Header tabel (sama seperti sebelumnya)
        // ... (Kode Header Tabel)
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

        // Hitung indeks awal dan akhir untuk halaman saat ini
        int start_index = (current_page - 1) * MAX_ROWS_PER_PAGE;
        int end_index = start_index + MAX_ROWS_PER_PAGE;
        if (end_index > total_staff) {
            end_index = total_staff;
        }

        // Isi tabel untuk halaman saat ini
        for (int i = start_index; i < end_index; i++) {
            staff current_staff = all_staff[i];
            char maskedPassword[255];
            int pwLen = strlen(current_staff.password);
            for (int j = 0; j < pwLen && j < 254; j++) {
                maskedPassword[j] = '*';
            }
            maskedPassword[pwLen] = '\0';

            gotoxy(startX, row++);
            printf("| %-*d | %-*s | %-*s | %-*s | %-*s | %-*s |",
                   wNo,  i + 1,
                   wUsr, current_staff.username,
                   wPw,  maskedPassword,
                   wGen, current_staff.gender,
                   wTgl, current_staff.tgl,
                   wTelp,current_staff.notlpn
            );
        }

        // Garis penutup tabel
        gotoxy(startX, row++);
        printf("%s", line);

        // Informasi Paging diubah
        gotoxy(startX, 27);
        printf("[SPASI] -> %d dari %d <- [BACKSPACE].untuk navigasi, ENTER (Keluar).",
               current_page, total_pages);

        // --- TUNGGU INPUT KEYBOARD DAN LOGIC PAGING BARU ---
        key = getch();

        if (key == ' ') { // Spasi (ASCII 32) -> Next Page
            if (current_page < total_pages) {
                current_page++;
            }
        } else if (key == '\b' || key == 8) { // Backspace (ASCII 8) -> Previous Page
            if (current_page > 1) {
                current_page--;
            }
        }

    } while (key != 13); // Loop selama key BUKAN ENTER (ASCII 13)
}

#endif