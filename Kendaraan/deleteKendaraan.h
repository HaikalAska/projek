//
// Created by yoyop on 14/12/2025.
//

#ifndef PROJEK_DELETEKENDARAAN_H
#define PROJEK_DELETEKENDARAAN_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#include "../FrameTabel.h"
#include "createKendaraan.h"

void deleteKendaraan() {
    FILE *fp, *temp;
    Kendaraan data;
    Kendaraan kendaraanList[100];
    int count = 0;
    int pilihan;
    char konfirmasi;
    int found = 0;

    // ===== BACA DATA =====
    fp = fopen("kendaraan.dat", "rb");
    if (fp == NULL) {
        gotoxy(3, 13);
        printf("File kendaraan.dat tidak ditemukan!");
        getch();
        return;
    }

    while (fread(&data, sizeof(Kendaraan), 1, fp) == 1) {
        kendaraanList[count++] = data;
    }
    fclose(fp);

    if (count == 0) {
        gotoxy(3, 13);
        printf("Tidak ada data kendaraan! ");
        getch();
        return;
    }

    // ===== INPUT PILIHAN =====
    while (1) {
        char buffer[10] = "";
        int idx = 0;
        char ch;

        gotoxy(3, 25);
        printf("Pilih No Urut : ");
        gotoxy(20, 25);
        printf("          ");
        gotoxy(20, 25);

        while (1) {
            ch = getch();

            if (ch == 27) {
                gotoxy(3, 26);
                printf("Dibatalkan!");
                getch();
                return;
            }

            if (ch == 13) {
                // Validasi: cek apakah kosong
                if (idx == 0) {
                    gotoxy(3, 26);
                    printf("Angka tidak boleh kosong!");
                    Sleep(1500);
                    gotoxy(3, 26);
                    printf("                          ");
                    break;  // keluar dari inner loop untuk input ulang
                }

                buffer[idx] = '\0';
                pilihan = atoi(buffer);
                break;
            }

            if (ch == 8 && idx > 0) {
                idx--;
                buffer[idx] = '\0';
                gotoxy(20, 25);
                printf("          ");
                gotoxy(20, 25);
                printf("%s", buffer);
            }

            if (ch >= '0' && ch <= '9') {
                if (idx < 9) {
                    buffer[idx++] = ch;
                    buffer[idx] = '\0';
                    printf("%c", ch);
                }
            }
        }

        // Jika user tekan ESC (sudah return di atas) atau input kosong, continue
        if (idx == 0) continue;

        if (pilihan >= 1 && pilihan <= count) break;

        gotoxy(3, 26);
        printf("Pilihan tidak valid!");
        Sleep(1500);
        gotoxy(3, 26);
        printf("                     ");
    }

    Kendaraan terpilih = kendaraanList[pilihan - 1];

    // ===== BOX DETAIL =====
    bentukframe(37, 27, 55, 10);
    gotoxy(55, 27); printf("=== DATA KENDARAAN ===");

    gotoxy(38, 28); printf("ID Kendaraan : %s", terpilih.id_kendaraan);
    gotoxy(38, 29); printf("Kategori     : %s", terpilih.kategori);
    gotoxy(38, 30); printf("Kapasitas    : %s", terpilih.kapasitas);
    gotoxy(38, 31); printf("Fasilitas    : %s", terpilih.fasilitas);
    gotoxy(38, 32); printf("Nama Armada  : %s", terpilih.nama_armada);

    // ===== KONFIRMASI (Y/N ONLY, BACKSPACE & ESC AKTIF) =====
    gotoxy(38, 34);
    printf("Yakin ingin menghapus jadwal ini? (y/n): ");
    gotoxy(78, 34);

    while (1) {
        char ch = getch();

        // ESC → batal
        if (ch == 27) {
            gotoxy(38, 35);
            printf("Penghapusan dibatalkan!");
            getch();
            return;
        }

        // BACKSPACE → hapus y/n
        if (ch == 8 && konfirmasi != '\0') {
            konfirmasi = '\0';
            gotoxy(80, 36);
            printf(" ");
            gotoxy(80, 36);
            continue;
        }

        ch = tolower(ch);

        // hanya y atau n
        if ((ch == 'y' || ch == 'n') && konfirmasi == '\0') {
            konfirmasi = ch;
            printf("%c", ch);
        }

        // ENTER setelah input valid
        if (ch == 13 && konfirmasi != '\0') {
            break;
        }
    }

    if (konfirmasi != 'y') {
        gotoxy(38, 35);
        printf("Penghapusan dibatalkan!");
        getch();
        return;
    }

    // ===== PROSES HAPUS =====
    fp = fopen("kendaraan.dat", "rb");
    temp = fopen("temp.dat", "wb");

    while (fread(&data, sizeof(Kendaraan), 1, fp) == 1) {
        if (strcmp(data.id_kendaraan, terpilih.id_kendaraan) != 0) {
            fwrite(&data, sizeof(Kendaraan), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("kendaraan.dat");
        rename("temp.dat", "kendaraan.dat");
        gotoxy(38, 35);
        printf("Data kendaraan berhasil dihapus!");
    } else {
        remove("temp.dat");
        gotoxy(38, 35);
        printf("Terjadi kesalahan saat menghapus!");
    }

    getch();
    getch();
}

#endif

