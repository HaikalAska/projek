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

            // ===== NAVIGASI =====
            gotoxy(5,30); printf("MENU");
            gotoxy(4,32); printf("ENTER Mulai Edit");
            gotoxy(4,34); printf("ESC Keluar");

            // ===== DATA LAMA =====
            gotoxy(54,30); printf("DATA LAMA");
            gotoxy(40,32); printf("Kategori  : %s", data.kategori);
            gotoxy(40,33); printf("Kapasitas : %s", data.kapasitas);
            gotoxy(40,34); printf("Fasilitas : %s", data.fasilitas);
            gotoxy(40,35); printf("Armada    : %s", data.nama_armada);
            gotoxy(40,36); printf("Tahun     : %s", data.tahun);
            gotoxy(40,37); printf("Status    : %s", data.status);

            // ===== DATA BARU (KOSONG DULU) =====
            gotoxy(102,30); printf("DATA BARU");
            gotoxy(85,32); printf("│ "); gotoxy(88,32); printf("Kategori  : ");
            gotoxy(85,33); printf("│ "); gotoxy(88,33); printf("Kapasitas : ");
            gotoxy(85,34); printf("│ "); gotoxy(88,34); printf("Fasilitas : ");
            gotoxy(85,35); printf("│ "); gotoxy(88,35); printf("Armada    : ");
            gotoxy(85,36); printf("│ "); gotoxy(88,36); printf("Tahun     : ");
            gotoxy(85,37); printf("│ "); gotoxy(88,37); printf("Status    : ");

            gotoxy(88,40);
            printf("Kategori-(E=Ekonomi  B=Bisnis  X=Executive)");
            gotoxy(88,41);
            printf("Status-(T=Tersedia  M=Maintenance  D=Perjalanan  N=Tidak aktif)");

            // ================= TUNGGU ENTER UNTUK MULAI =================
            while (1) {
                int ch = _getch();
                if (ch == 13) break;  // ENTER → mulai edit
                if (ch == 27) {       // ESC → keluar
                    fclose(fp);
                    fclose(tmp);
                    remove("temp.dat");
                    return;
                }
            }

            char tempData[100];
            int cancelEdit = 0;

            // ================= 1. KATEGORI =================
            gotoxy(85, 32); printf(">>"); // Panah aktif
            clearArea(inputX, 32, 35, 1);
            strcpy(tempData, data.kategori);
            gotoxy(inputX, 32);
            inputKategoriKendaraan(data.kategori, 32, inputX);

            if (strlen(data.kategori) == 0) {
                strcpy(data.kategori, tempData);
                cancelEdit = 1;
            }

            if (!cancelEdit) {
                clearArea(inputX, 32, 35, 1);
                gotoxy(inputX, 32);
                printf("%s", data.kategori);
                gotoxy(85, 32); printf("│ "); // Panah selesai
            } else {
                fclose(fp);
                fclose(tmp);
                remove("temp.dat");
                return;
            }

            // ================= 2. KAPASITAS =================
            gotoxy(85, 33 ); printf(">>"); // Panah aktif
            clearArea(inputX, 33, 35, 1);
            strcpy(tempData, data.kapasitas);
            gotoxy(inputX, 33);
            inputKapasitas2Digit(data.kapasitas, 33, inputX);

            if (strlen(data.kapasitas) == 0) {
                strcpy(data.kapasitas, tempData);
                cancelEdit = 1;
            }

            if (!cancelEdit) {
                clearArea(inputX, 33, 35, 1);
                gotoxy(inputX, 33);
                printf("%s", data.kapasitas);
                gotoxy(85, 33); printf("│ "); // Panah selesai
            } else {
                fclose(fp);
                fclose(tmp);
                remove("temp.dat");
                return;
            }

            // ================= 3. FASILITAS =================
            gotoxy(85, 34); printf(">>"); // Panah aktif
            clearArea(inputX, 34, 35, 1);
            strcpy(tempData, data.fasilitas);
            gotoxy(inputX, 34);
            inputFasilitas(data.fasilitas, 34, inputX);

            if (strlen(data.fasilitas) == 0) {
                strcpy(data.fasilitas, tempData);
                cancelEdit = 1;
            }

            if (!cancelEdit) {
                clearArea(inputX, 34, 35, 1);
                gotoxy(inputX, 34);
                printf("%s", data.fasilitas);
                gotoxy(85, 34); printf("│ "); // Panah selesai
            } else {
                fclose(fp);
                fclose(tmp);
                remove("temp.dat");
                return;
            }

            // ================= 4. ARMADA =================
            gotoxy(85, 35); printf(">>"); // Panah aktif
            clearArea(inputX, 35, 35, 1);
            strcpy(tempData, data.nama_armada);
            gotoxy(inputX, 35);
            inputNamaArmada(data.nama_armada, 35, inputX);

            if (strlen(data.nama_armada) == 0) {
                strcpy(data.nama_armada, tempData);
                cancelEdit = 1;
            }

            if (!cancelEdit) {
                clearArea(inputX, 35, 35, 1);
                gotoxy(inputX, 35);
                printf("%s", data.nama_armada);
                gotoxy(85, 35); printf("│ "); // Panah selesai
            } else {
                fclose(fp);
                fclose(tmp);
                remove("temp.dat");
                return;
            }

            // ================= 5. TAHUN =================
            gotoxy(85, 36); printf(">>"); // Panah aktif
            clearArea(inputX, 36, 35, 1);
            strcpy(tempData, data.tahun);
            gotoxy(inputX, 36);
            inputTahun(data.tahun, 36, inputX);

            if (strlen(data.tahun) == 0) {
                strcpy(data.tahun, tempData);
                cancelEdit = 1;
            }

            if (!cancelEdit) {
                clearArea(inputX, 36, 35, 1);
                gotoxy(inputX, 36);
                printf("%s", data.tahun);

                // Validasi umur bus
                int tahunBus = atoi(data.tahun);
                int tahunSekarang = getTahunSekarang();
                int umur = tahunSekarang - tahunBus;

                gotoxy(inputX + 6, 36);
                if (umur > 10) {
                    printf("[Tidak Layak | %d th]", umur);
                } else {
                    printf("[Layak | %d th]", umur);
                }
                gotoxy(85, 36); printf("│ "); // Panah selesai
            } else {
                fclose(fp);
                fclose(tmp);
                remove("temp.dat");
                return;
            }

            // ================= 6. STATUS =================
            gotoxy(85, 37); printf(">>"); // Panah aktif
            clearArea(inputX, 37, 35, 1);
            strcpy(tempData, data.status);
            gotoxy(inputX, 37);
            inputStatusKendaraan(data.status, 37, inputX);

            if (strlen(data.status) == 0) {
                strcpy(data.status, tempData);
                cancelEdit = 1;
            }

            if (!cancelEdit) {
                clearArea(inputX, 37, 35, 1);
                gotoxy(inputX, 37);
                printf("%s", data.status);
                gotoxy(85, 37); printf("│ "); // Panah selesai
            } else {
                fclose(fp);
                fclose(tmp);
                remove("temp.dat");
                return;
            }

            // ================= SIMPAN =================
            fwrite(&data, sizeof(Kendaraan), 1, tmp);
        }
        else {
            fwrite(&data, sizeof(Kendaraan), 1, tmp);
        }

        currentNo++;
    }

    fclose(fp);
    fclose(tmp);

    // ================= HASIL =================
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