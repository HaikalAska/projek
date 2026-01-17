#ifndef PROJEK_UPDATE_KENDARAAN_H
#define PROJEK_UPDATE_KENDARAAN_H

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "../FrameTabel.h"
#include "createKendaraan.h"

void updateKendaraan() {

    FILE *fp, *tmp;
    Kendaraan data;

    char strNo[10];
    int targetNo = 0, currentNo = 1;
    int idx = 0, found = 0;

    int inputX = 100;

    // ================= INPUT NOMOR =================
    gotoxy(3,25);
    printf("Pilih No Urut Kendaraan : ");

    while (1) {
        char ch = _getch();

        if (ch == 27) return;

        if (ch == 13) {
            strNo[idx] = '\0';
            targetNo = atoi(strNo);
            break;
        }
        else if (ch == 8 && idx > 0) {
            idx--;
            printf("\b \b");
        }
        else if (ch >= '0' && ch <= '9' && idx < 9) {
            strNo[idx++] = ch;
            printf("%c", ch);
        }
    }

    if (targetNo <= 0) return;

    fp  = fopen("kendaraan.dat", "rb");
    tmp = fopen("temp.dat", "wb");
    if (!fp || !tmp) return;

    // ================= LOOP FILE =================
    while (fread(&data, sizeof(Kendaraan), 1, fp)) {

        if (currentNo == targetNo) {
            found = 1;

            // ===== FRAME =====
            bentukframe(3,29,27,10);
            bentukframe(37,29,45,14);
            bentukframe(85,29,68,14);

            // ===== MENU =====
            gotoxy(5,30); printf("MENU");
            gotoxy(4,32); printf("NAVIGASI [↑ ↓]");
            gotoxy(4,34); printf("ENTER Pilih");
            gotoxy(4,36); printf("ESC  Keluar");

            // ===== DATA LAMA =====
            gotoxy(54,30); printf("DATA LAMA");
            gotoxy(40,32); printf("Kategori  : %s", data.kategori);
            gotoxy(40,33); printf("Kapasitas : %s", data.kapasitas);
            gotoxy(40,34); printf("Fasilitas : %s", data.fasilitas);
            gotoxy(40,35); printf("Armada    : %s", data.nama_armada);
            gotoxy(40,36); printf("Tahun     : %s", data.tahun);
            gotoxy(40,37); printf("Status    : %s", data.status);

            // ===== DATA BARU =====
            gotoxy(102,30); printf("DATA BARU");
            gotoxy(88,32); printf("Kategori  : ");
            gotoxy(88,33); printf("Kapasitas : ");
            gotoxy(88,34); printf("Fasilitas : ");
            gotoxy(88,35); printf("Armada    : ");
            gotoxy(88,36); printf("Tahun     : ");
            gotoxy(88,37); printf("Status    : ");
            gotoxy(88,38); printf("[ SIMPAN PERUBAHAN ]");


            int selectedField = 0;
            int totalField = 4; // 0: kategori, 1: armada, 2: tahun, 3: status, 4: simpan
            int editing = 1;

            while (editing) {

                // ===== PANAH (HANYA UNTUK FIELD YANG BISA DIEDIT) =====
                // Kategori (0)
                gotoxy(85, 32);
                if (selectedField == 0) printf(">>");
                else printf("│ ");

                // Kapasitas & Fasilitas (SKIP - OTOMATIS)
                gotoxy(85, 33); printf("│ ");
                gotoxy(85, 34); printf("│ ");

                // Armada (1)
                gotoxy(85, 35);
                if (selectedField == 1) printf(">>");
                else printf("│ ");

                // Tahun (2)
                gotoxy(85, 36);
                if (selectedField == 2) printf(">>");
                else printf("│ ");

                // Status (3)
                gotoxy(85, 37);
                if (selectedField == 3) printf(">>");
                else printf("│ ");

                // Simpan (4)
                gotoxy(85, 38);
                if (selectedField == 4) printf(">>");
                else printf("│ ");

                int ch = _getch();

                // ===== PANAH ATAS / BAWAH =====
                if (ch == 0 || ch == 224) {
                    int arrow = _getch();
                    if (arrow == 72) { // UP
                        selectedField--;
                        if (selectedField < 0) selectedField = totalField;
                    }
                    else if (arrow == 80) { // DOWN
                        selectedField++;
                        if (selectedField > totalField) selectedField = 0;
                    }
                }

                // ===== ENTER =====
                else if (ch == 13) {

                    char backup_kategori[30];
                    char backup_kapasitas[10];
                    char backup_fasilitas[100];
                    char backup[100];

                    // ===== SIMPAN =====
                    if (selectedField == totalField) {
                        editing = 0;
                        break;
                    }

                    switch (selectedField) {

                        case 0: // KATEGORI (MENU DENGAN PREVIEW)
                            // Backup data lama
                            strcpy(backup_kategori, data.kategori);
                            strcpy(backup_kapasitas, data.kapasitas);
                            strcpy(backup_fasilitas, data.fasilitas);

                            // === CLEAR SEMUA AREA KANAN (DATA BARU) ===
                            clearArea(85, 29, 68, 15);

                            // Panggil menu kategori dengan preview
                            inputKategoriKendaraanDenganPreview(data.kategori, data.kapasitas, data.fasilitas, 32, inputX);

                            // Jika ESC (kategori kosong), restore backup
                            if (strlen(data.kategori) == 0) {
                                strcpy(data.kategori, backup_kategori);
                                strcpy(data.kapasitas, backup_kapasitas);
                                strcpy(data.fasilitas, backup_fasilitas);
                            }

                            // === GAMBAR ULANG SEMUA FRAME ===
                            bentukframe(3,29,27,10);
                            bentukframe(37,29,45,14);
                            bentukframe(85,29,68,14);

                            // ===== MENU =====
                            gotoxy(5,30); printf("MENU");
                            gotoxy(4,32); printf("NAVIGASI [↑ ↓]");
                            gotoxy(4,34); printf("ENTER Pilih");
                            gotoxy(4,36); printf("ESC  Keluar");

                            // ===== DATA LAMA =====
                            gotoxy(54,30); printf("DATA LAMA");
                            gotoxy(40,32); printf("Kategori  : %s", backup_kategori);
                            gotoxy(40,33); printf("Kapasitas : %s", backup_kapasitas);
                            gotoxy(40,34); printf("Fasilitas : %s", backup_fasilitas);
                            gotoxy(40,35); printf("Armada    : %s", data.nama_armada);
                            gotoxy(40,36); printf("Tahun     : %s", data.tahun);
                            gotoxy(40,37); printf("Status    : %s", data.status);

                            // ===== DATA BARU (HEADER) =====
                            gotoxy(102,30); printf("DATA BARU");
                            gotoxy(88,32); printf("Kategori  : ");
                            gotoxy(88,33); printf("Kapasitas : ");
                            gotoxy(88,34); printf("Fasilitas : ");
                            gotoxy(88,35); printf("Armada    : ");
                            gotoxy(88,36); printf("Tahun     : ");
                            gotoxy(88,37); printf("Status    : ");
                            gotoxy(88,38); printf("[ SIMPAN PERUBAHAN ]");

                            // === TAMPILKAN KATEGORI, KAPASITAS, FASILITAS BARU ===
                            gotoxy(inputX, 32);
                            printf("%-48s", data.kategori);
                            gotoxy(inputX, 33);
                            printf("%-48s", ""); // Clear dulu
                            gotoxy(inputX, 33);
                            printf("%s orang", data.kapasitas);
                            gotoxy(inputX, 34);
                            printf("%-48s", ""); // Clear dulu
                            gotoxy(inputX, 34);
                            printf("%s", data.fasilitas);
                            break;

                        case 1: // ARMADA
                            strcpy(backup, data.nama_armada);
                            clearArea(inputX, 35, 48, 1);
                            gotoxy(inputX,35);
                            inputNamaArmada(data.nama_armada, 35, inputX);
                            if (strlen(data.nama_armada)==0)
                                strcpy(data.nama_armada, backup);
                            break;

                        case 2: // TAHUN
                            strcpy(backup, data.tahun);
                            clearArea(inputX, 36, 48, 1);
                            gotoxy(inputX,36);
                            inputTahun(data.tahun, 36, inputX);
                            if (strlen(data.tahun)==0)
                                strcpy(data.tahun, backup);
                            break;

                        case 3: // STATUS
                            // === TAMPILKAN PETUNJUK SAAT INPUT STATUS ===
                            gotoxy(88,40);
                            printf("[T]Tersedia [M]Maintenance [D]Perjalanan [N]Nonaktif");

                            strcpy(backup, data.status);
                            clearArea(inputX, 37, 48, 1);
                            gotoxy(inputX,37);
                            inputStatusKendaraan(data.status, 37, inputX);

                            // === HAPUS PETUNJUK SETELAH INPUT ===
                            clearArea(88, 40, 55, 1);

                            if (strlen(data.status)==0)
                                strcpy(data.status, backup);
                            break;

                    }
                }

                // ===== ESC =====
                else if (ch == 27) {
                    fclose(fp);
                    fclose(tmp);
                    remove("temp.dat");
                    return;
                }
            }

            // ===== SIMPAN KE FILE =====
            fwrite(&data, sizeof(Kendaraan), 1, tmp);
        }
        else {
            fwrite(&data, sizeof(Kendaraan), 1, tmp);
        }

        currentNo++;
    }

    fclose(fp);
    fclose(tmp);

    // ===== HASIL =====
    if (found) {
        remove("kendaraan.dat");
        rename("temp.dat", "kendaraan.dat");
        gotoxy(88,39);
        printf("Data kendaraan berhasil diupdate!");
    } else {
        remove("temp.dat");
        gotoxy(88,39);
        printf("Nomor tidak ditemukan!");
    }

    _getch();
}

#endif