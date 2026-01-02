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
    int isInput = 0;   

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
            bentukframe(85,29,55,14);

            // ===== NAVIGASI =====
            gotoxy(5,30); printf("MENU");
            gotoxy(4,32); printf("↑ ↓ Navigasi");
            gotoxy(4,34); printf("ENTER Edit");
            gotoxy(4,36); printf("ESC Keluar");

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
            gotoxy(88,38); printf("[SIMPAN PERUBAHAN]");

            gotoxy(88,40);
            printf("(E,B,X) Kategori | (T,M,D,N) Status");

            int selected = 0;
            int maxField = 6;

            // ================= MODE NAVIGASI =================
            while (1) {

                // panah navigasi
                for (int i = 0; i <= maxField; i++) {
                    gotoxy(85, 32 + i);
                    printf(i == selected ? ">>" : "│ ");
                }
            }

                int ch = _getch();

                // BLOK NAVIGASI SAAT INPUT
                if (!isInput && (ch == 0 || ch == 224)) {
                    ch = _getch();
                    if (ch == 72) selected--;
                    if (ch == 80) selected++;
                    if (selected < 0) selected = maxField;
                    if (selected > maxField) selected = 0;
                }

                // ENTER → INPUT
                else if (ch == 13) {

                    if (selected == maxField) break; // SIMPAN

                    isInput = 1; // KUNCI NAVIGASI
                    clearArea(inputX, 32 + selected, 35, 1);

                    switch (selected) {
                        case 0:
                            gotoxy(inputX,32);
                            inputKategoriKendaraan(data.kategori,32,inputX);
                            break;

                        case 1:
                            gotoxy(inputX,33);
                            inputKapasitas2Digit(data.kapasitas,33,inputX);
                            break;

                        case 2:
                            gotoxy(inputX,34);
                            inputFasilitas(data.fasilitas,34,inputX);
                            break;

                        case 3:
                            gotoxy(inputX,35);
                            inputNamaArmada(data.nama_armada,35,inputX);
                            break;

                        case 4:
                            gotoxy(inputX,36);
                            inputTahun(data.tahun,36,inputX);
                            break;

                        case 5:
                            gotoxy(inputX,37);
                            inputStatusKendaraan(data.status,37,inputX);
                            break;
                    }

                    isInput = 0; //BUKA NAVIGASI
                }

                // ESC
                else if (ch == 27) {
                    fclose(fp);
                    fclose(tmp);
                    remove("temp.dat");
                    return;
                }
                gotoxy(85, 36); printf("│ "); // Panah selesai
            } else {
                fclose(fp);
                fclose(tmp);
                remove("temp.dat");
                return;
            }

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
        gotoxy(50,47);
        printf("Data kendaraan berhasil diupdate!");
    } else {
        remove("temp.dat");
        gotoxy(50,47);
        printf("Nomor tidak ditemukan!");
    }

    _getch();
}

#endif