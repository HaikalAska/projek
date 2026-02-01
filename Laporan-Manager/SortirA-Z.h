#ifndef PROJEK_SORTIRA_Z_H
#define PROJEK_SORTIRA_Z_H
#include "../FrameTabel.h"
#include "Laporan-Bulanan.h"

void SortirLaporan() {
     FILE *fp;
    tiket all_data[1000];
    int total_all = 0;
    long total_pendapatan = 0;

    int startX = 33;
    int startY = 12;

    // ===== LEBAR KOLOM =====
    int wNo = 3, wID = 8, wNama = 20, wTelp = 13;
    int wRute = 17, wTgl = 12, wJam = 5, wStatus = 7, wHarga = 15;

    clearArea(32,32,126,10);

    // Baca semua data
    fp = fopen("tiket.dat", "rb");
    if (!fp) {
        bentukframe(34, 11, 80, 15);
        gotoxy(startX, startY);
        printf("File tiket.dat tidak ditemukan!");
        getch();
        return;
    }

    while (fread(&all_data[total_all], sizeof(tiket), 1, fp) == 1) {
        if (total_all < 1000) total_all++;
    }
    fclose(fp);

    if (total_all == 0) {
        bentukframe(34, 11, 80, 15);
        gotoxy(startX, startY);
        printf("Belum ada data tiket!");
        getch();
        return;
    }

    // (Bubble Sort)
    for (int i = 0; i < total_all - 1; i++) {
        for (int j = 0; j < total_all - i - 1; j++) {
            if (strcmp(all_data[j].nama_penumpang, all_data[j + 1].nama_penumpang) > 0) {
                // Swap
                tiket temp = all_data[j];
                all_data[j] = all_data[j + 1];
                all_data[j + 1] = temp;
            }
        }
    }

    // Hitung total pendapatan
    for (int i = 0; i < total_all; i++) {
        total_pendapatan += all_data[i].harga;
    }

    // Clear aaja
    clearArea(3,8,27,18);

    // Tampilkan tabel
    int rowsPerPage = 10;
    int total_pages = (total_all + rowsPerPage - 1) / rowsPerPage;
    int current_page = 1;
    char key;

    int totalWidth =
        1 + (wNo+2)+(wID+2)+(wNama+2)+(wTelp+2)+
        (wRute+2)+(wTgl+2)+(wJam+2)+(wStatus+2)+(wHarga+3);

    char garis[300];
    memset(garis, '-', totalWidth);
    garis[totalWidth] = '\0';

    do {
        int start = (current_page - 1) * rowsPerPage;
        int end = start + rowsPerPage;
        if (end > total_all) end = total_all;

        clearArea(startX, startY + 1, totalWidth, 20);

        gotoxy(80, 13);
        printf("=== LAPORAN TIKET (A-Z) ===");

        int row = startY + 2;

        // ===== HEADER TABEL =====
        gotoxy(startX, row++); printf("%s", garis);

        gotoxy(startX, row++);
        printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
               wNo+1,"No",
               wID+1,"ID Tiket",
               wNama+1,"Nama",
               wTelp+1,"Telepon",
               wRute+1,"Rute",
               wTgl+1,"Tanggal",
               wJam+1,"Jam",
               wStatus+1,"Status",
               wHarga+2,"Harga");

        gotoxy(startX, row++); printf("%s", garis);

        // ===== ISI DATA =====
        for (int i = start; i < end; i++) {
            char rute[60];
            sprintf(rute, "%s-%s",
                    all_data[i].rute_awal,
                    all_data[i].tujuan);

            gotoxy(startX, row++);


            char ruteTampil[25];

            if (strlen(rute) > wRute) {
                strncpy(ruteTampil, rute, wRute - 3);
                ruteTampil[wRute - 3] = '\0';
                strcat(ruteTampil, "...");
            } else {
                strcpy(ruteTampil, rute);
            }


            // cetak kolom sebelum harga
            printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
                   wNo+1, i+1,
                   wID+1, all_data[i].id_tiket,
                   wNama+1, all_data[i].nama_penumpang,
                   wTelp+1, all_data[i].notlpn,
                   wRute+1, ruteTampil,
                   wTgl+1, all_data[i].tanggal_berangkat,
                   wJam+1, all_data[i].jam_berangkat,
                   wStatus+1, all_data[i].status);

            char hargaStr[30];

            if (strcmp(all_data[i].status, "Batal") == 0) {
                formatHarga(all_data[i].harga, hargaStr);
            } else {
                formatHarga(all_data[i].harga, hargaStr);
            }

            printf(" %-*s|", wHarga+1, hargaStr);
        }

        gotoxy(startX, row++); printf("%s", garis);

        // Total pendapatan
        gotoxy(startX, row + 1);
        printf("Total Tiket      : %d tiket", total_all);
        gotoxy(startX, row + 2);
        printf("Total Pendapatan : ");
        tampilanhargatiket(total_pendapatan);

        // ===== NAVIGASI =====
        bentukframe(3, 11, 27, 12);
        gotoxy(6, 13); printf("[SPASI] Lanjut");
        gotoxy(6, 15); printf("[BACKSPACE] Kembali");
        gotoxy(6, 17); printf("[ENTER] Keluar");
        gotoxy(6, 19); printf("Halaman: %d/%d", current_page, total_pages);
        gotoxy(6, 21); printf("Total  : %d data", total_all);

        key = getch();

        if (key == 13) {
            Laporan();
            break;
        }
        else if (key == ' ' && current_page < total_pages)
            current_page++;
        else if (key == 8 && current_page > 1)
            current_page--;

    } while (1);
    system("cls");
}





#endif //PROJEK_SORTIRA_Z_H