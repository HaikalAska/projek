#ifndef PROJEK_READKENDARAAN_H
#define PROJEK_READKENDARAAN_H

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "../FrameTabel.h"
#include "createKendaraan.h"

// ================= PAGING =================
#define MAX_ROWS_PER_PAGE 8

void readKendaraan() {

    FILE *fp;
    Kendaraan all_kendaraan[1000];
    int total_kendaraan = 0;

    int startX = 37;
    int startY = 12;

    // ===== LEBAR KOLOM =====
    int wNo     = 3;
    int wKat    = 10;
    int wKap    = 10;
    int wFas    = 25;
    int wNama   = 18;
    int wPlat   = 12;
    int wTahun  = 6;
    int wStatus = 10;

    int rowsPerPage = 8;
    int current_page = 1;
    int total_pages = 1;
    char key;

    bentukframe(34, 11, 121, 35);

    fp = fopen("kendaraan.dat", "rb");
    if (!fp) {
        gotoxy(startX, startY);
        printf("File kendaraan.dat tidak ditemukan!");
        getch();
        return;
    }

    Kendaraan data;
    while (fread(&data, sizeof(Kendaraan), 1, fp) == 1) {
        if (total_kendaraan < 1000) {
            all_kendaraan[total_kendaraan++] = data;
        }
    }
    fclose(fp);

    // ================= BUBBLE SORT BERDASARKAN ID (CHAR) =================
    // DESCENDING (ID terbesar di atas)
    for (int i = 0; i < total_kendaraan - 1; i++) {
        for (int j = 0; j < total_kendaraan - i - 1; j++) {
            if (strcmp(all_kendaraan[j].id_kendaraan,
                       all_kendaraan[j + 1].id_kendaraan) < 0) {

                Kendaraan temp = all_kendaraan[j];
                all_kendaraan[j] = all_kendaraan[j + 1];
                all_kendaraan[j + 1] = temp;
            }
        }
    }

    if (total_kendaraan > 0) {
        total_pages = (total_kendaraan + rowsPerPage - 1) / rowsPerPage;
    }

    int totalWidth =
        1 +
        (wNo+2) +
        (wKat+2) +
        (wKap+2) +
        (wFas+2) +
        (wNama+2) +
        (wPlat+2) +
        (wTahun+2) +
        (wStatus+2);

    char line[300];
    memset(line, '-', totalWidth);
    line[totalWidth] = '\0';

    do {
        clearArea(startX, startY, totalWidth + 5, rowsPerPage + 10);

        gotoxy(80, 13);
        printf("=== DAFTAR KENDARAAN ===");

        int row = startY + 2;

        gotoxy(startX, row++);
        printf("%s", line);

        // ===== HEADER =====
        gotoxy(startX, row++);
        printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
            wNo+1, "No",
            wKat+1, "Kategori",
            wKap+1, "Kapasitas",
            wFas+1, "Fasilitas",
            wNama+1, "Nama Armada",
            wPlat+1, "No Plat",
            wTahun+1, "Tahun",
            wStatus+1, "Status"
        );

        gotoxy(startX, row++);
        printf("%s", line);

        int start_index = (current_page - 1) * rowsPerPage;
        int end_index = start_index + rowsPerPage;
        if (end_index > total_kendaraan) end_index = total_kendaraan;

        for (int i = start_index; i < end_index; i++) {
            Kendaraan k = all_kendaraan[i];

            char kategori[15], kapasitas[15], fasilitas[30];
            char nama[25], plat[20], tahun[10], status[15];

            snprintf(kategori, wKat+1, "%s", k.kategori);
            snprintf(kapasitas, wKap+1, "%s", k.kapasitas);
            snprintf(fasilitas, wFas+1, "%s", k.fasilitas);
            snprintf(nama, wNama+1, "%s", k.nama_armada);
            snprintf(plat, wPlat+1, "%s", k.plat_nomor);
            snprintf(tahun, wTahun+1, "%s", k.tahun);
            snprintf(status, wStatus+1, "%s", k.status);

            if (strlen(k.fasilitas) > wFas) {
                fasilitas[wFas-2] = '.';
                fasilitas[wFas-1] = '.';
            }

            if (strlen(k.nama_armada) > wNama) {
                nama[wNama-2] = '.';
                nama[wNama-1] = '.';
            }

            gotoxy(startX, row++);
            printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
                wNo+1,    i + 1,
                wKat+1,   kategori,
                wKap+1,   kapasitas,
                wFas+1,   fasilitas,
                wNama+1,  nama,
                wPlat+1,  plat,
                wTahun+1, tahun,
                wStatus+1, status
            );
        }

        gotoxy(startX, row++);
        printf("%s", line);

        // ===== INFO NAVIGASI =====
        bentukframe(3, 11, 27, 12);
        gotoxy(6, 13); printf("[SPASI] Lanjut");
        gotoxy(6, 15); printf("[BACKSPACE] Kembali");
        gotoxy(6, 17); printf("[ENTER] Keluar");
        gotoxy(6, 19); printf("Halaman: %d/%d", current_page, total_pages);
        gotoxy(6, 21); printf("Total  : %d data", total_kendaraan);

        key = getch();

        if (key == ' ') {
            if (current_page < total_pages) current_page++;
        } else if (key == 8) {
            if (current_page > 1) current_page--;
        }

    } while (key != 13);
}

#endif
