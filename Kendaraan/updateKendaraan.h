//
// Created by yoyop on 14/12/2025.
//

#ifndef PROJEK_UPDATEKENDARAAN_H
#define PROJEK_UPDATEKENDARAAN_H

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "../FrameTabel.h"
#include "createKendaraan.h"

// ======================================================
// ================= UPDATE KENDARAAN ===================
// ======================================================

static void inputKategoriKendaraans(char *kategori) {
    char ch;
    char temp[50] = "";   // simpan pilihan sementara

    while (1) {
        ch = getch();

        // ESC → batal
        if (ch == 27) {
            kategori[0] = '\0';
            return;
        }

        // ENTER → konfirmasi pilihan
        if (ch == 13) {
            if (strlen(temp) == 0) {
                // belum pilih apa-apa
                printf(" [Pilih kategori dulu]");
                Sleep(800);

                // Hapus peringatan
                printf("\r");
                for (int k = 0; k < 50; k++) {
                    printf(" ");
                }
                printf("\r");
                continue;
            }

            strcpy(kategori, temp); // simpan final
            return;
        }

        // PILIHAN KATEGORI
        switch (ch) {
            case 'e':
            case 'E':
                strcpy(temp, "Ekonomi");
                break;

            case 'b':
            case 'B':
                strcpy(temp, "Bisnis");
                break;

            case 'x':
            case 'X':
                strcpy(temp, "Executive");
                break;

            case 'p':
            case 'P':
                strcpy(temp, "Pariwisata");
                break;

            case 'm':
            case 'M':
                strcpy(temp, "Mania");
                break;

            default:
                continue; // tombol lain (termasuk Tab) diabaikan
        }

        // TAMPILKAN PILIHAN (bisa berubah-ubah)
        // Hapus text lama dulu
        // printf("\r");
        for (int k = 0; k < 50; k++) {
            // printf(" ");
        }
        // printf("\r");

        // Tampilkan pilihan baru
        gotoxy(112,32); printf("%-30s", temp);
    }
}

void inputKategoriUpdate(char *kategori) {

    int i = 0;
    char ch;

    while (1) {
        ch = getch();

        if (ch == 13) { // ENTER
            if (i == 0) continue;
            kategori[i] = '\0';
            break;
        }
        else if (ch == 27) { // ESC
            kategori[0] = '\0';
            break;
        }
        else if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        }
        else if (i < 29 && ch >= 32 && ch <= 126) {
            kategori[i++] = ch;
            printf("%c", ch);
        }
    }
}

void updateKendaraan() {

    FILE *fp, *temp;
    Kendaraan data;

    char strNo[10];
    int targetNo = 0;
    int currentNo = 1;
    int found = 0;
    int idx = 0;

    int startX = 50;
    int startY = 29;

    // ================= INPUT NOMOR URUT =================
    gotoxy(3, 25);
    printf("Pilih No Urut Kendaraan: ");

    while (1) {
        char ch = _getch();

        if (ch == 27) return;            // ESC
        else if (ch == 13) {             // ENTER
            strNo[idx] = '\0';
            targetNo = atoi(strNo);
            break;
        }
        else if (ch == 8 && idx > 0) {   // BACKSPACE
            idx--;
            printf("\b \b");
        }
        else if (ch >= '0' && ch <= '9' && idx < 9) {
            strNo[idx++] = ch;
            printf("%c", ch);
        }
    }

    if (targetNo <= 0) {
        gotoxy(startX, startY);
        printf("Nomor urut tidak valid!");
        getch();
        return;
    }

    fp   = fopen("kendaraan.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (!fp || !temp) {
        gotoxy(startX, startY);
        printf("Gagal membuka file kendaraan!");
        getch();
        return;
    }

    // ================= PROSES UPDATE =================
    while (fread(&data, sizeof(Kendaraan), 1, fp) == 1) {

        if (currentNo == targetNo) {
            found = 1;

            // ===== DATA LAMA =====
            bentukframe(48, 29, 45, 10);
            gotoxy(63, 30); printf("DATA LAMA");

            gotoxy(startX, startY + 2); printf("ID        : %s", data.id_kendaraan);
            gotoxy(startX, startY + 3); printf("Kategori  : %s", data.kategori);
            gotoxy(startX, startY + 4); printf("Kapasitas : %s", data.kapasitas);
            gotoxy(startX, startY + 5); printf("Fasilitas : %s", data.fasilitas);
            gotoxy(startX, startY + 6); printf("Armada    : %s", data.nama_armada);
            gotoxy(startX, startY + 7); printf("Tahun     : %s", data.tahun);


            // ===== DATA BARU =====
            bentukframe(95, 29, 55, 10);
            gotoxy(113, 30); printf("DATA BARU");

            gotoxy(99, 32); printf("Kategori  : ");
            gotoxy(99, 33); printf("Kapasitas : ");
            gotoxy(99, 34); printf("Fasilitas : ");
            gotoxy(99, 35); printf("Armada    : ");
            gotoxy(99, 36); printf("Tahun     : ");
            gotoxy(99, 37); printf("[ SIMPAN PERUBAHAN ]");

            int selected = 0;
            int totalField = 5;
            int editing = 1;

            while (editing) {

                // Bersihkan indikator
                for (int i = 0; i <= totalField; i++) {
                    gotoxy(97, 32 + i);
                    printf("  ");
                }

                // Tampilkan indikator
                gotoxy(97, 32 + selected);
                printf(">>");

                int ch = _getch();

                // ===== NAVIGASI =====
                if (ch == 0 || ch == 224) {
                    int arrow = _getch();
                    if (arrow == 72)
                        selected = (selected - 1 + totalField + 1) % (totalField + 1);
                    else if (arrow == 80)
                        selected = (selected + 1) % (totalField + 1);
                }

                // ===== ENTER =====
                else if (ch == 13) {

                    if (selected == totalField) {
                        editing = 0;
                        break;
                    }

                    int inputX = 112;
                    int inputY = 32 + selected;

                    clearArea(inputX, inputY, 35, 1);
                    gotoxy(inputX, inputY);

                    switch (selected) {

                        case 0: // KATEGORI
                            clearArea(112, 32, 30, 1);
                            gotoxy(112, 32);
                            inputKategoriKendaraans(data.kategori);
                            break;

                        case 1: // KAPASITAS
                            clearArea(112, 33, 5, 1);
                            gotoxy(112, 33);
                            inputKapasitas2Digit(data.kapasitas);
                            break;

                        case 2: // FASILITAS
                            clearArea(112, 34, 35, 1);
                            gotoxy(112, 34);
                            inputFasilitas(data.fasilitas, sizeof(data.fasilitas));
                            break;

                        case 3: // ARMADA
                            clearArea(112, 35, 25, 1);
                            gotoxy(112, 35);
                            INPUTNama(data.nama_armada);
                            break;
                        case 4:
                            clearArea(112, 36, 10, 1);
                            gotoxy(112, 36);
                            inputTahun(data.tahun);
                            break;

                    }


                    selected = (selected + 1) % (totalField + 1);
                }

                // ===== ESC =====
                else if (ch == 27) {
                    goto batal;
                }
            }

            fwrite(&data, sizeof(Kendaraan), 1, temp);

        } else {
            fwrite(&data, sizeof(Kendaraan), 1, temp);
        }

        currentNo++;
    }

batal:
    fclose(fp);
    fclose(temp);

    if (found) {
        remove("kendaraan.dat");
        rename("temp.dat", "kendaraan.dat");
        gotoxy(startX, startY + 12);
        printf("Data kendaraan berhasil diupdate!");
    } else {
        remove("temp.dat");
        gotoxy(startX, startY + 12);
        printf("Nomor urut tidak ditemukan!");
    }

    getch();
}

#endif
