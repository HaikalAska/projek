#ifndef PROJEK_DELETE_JADWAL_H
#define PROJEK_DELETE_JADWAL_H

#include "../FrameTabel.h"
#include "createJadwal.h"
#include <windows.h>
#include <ctype.h>

//======================//
//Untuk menghapus jadwal//
//(versi NONAKTIFKAN)   //
void hapusjadwal() {


    FILE *fp, *temp;
    jadwal list[200];
    jadwal data;
    int count = 0;
    int pilihan = 0;
    char konfirmasi = '\0';
    int found = 0;

    // ===== BUKA FILE =====
    fp = fopen("jadwal.dat", "rb");
    if (!fp) {
        gotoxy(3, 13);
        printf("File jadwal.dat tidak ditemukan!");
        getch();
        return;
    }

    // ===== BACA DATA =====
    while (fread(&data, sizeof(jadwal), 1, fp) == 1) {
        list[count++] = data;
    }
    fclose(fp);

    if (count == 0) {
        gotoxy(3, 13);
        printf("Tidak ada data jadwal!");
        getch();
        return;
    }
    // ===== BUBBLE SORT BERDASARKAN ID (DESCENDING) =====
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(list[j].id, list[j + 1].id) < 0) {
                jadwal tmp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = tmp;
            }
        }
    }

    // ===== INPUT NOMOR URUT =====
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

            if (ch == 13 && idx > 0) {
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

        if (pilihan < 1 || pilihan > count) {
            gotoxy(3, 26);
            printf("Pilihan tidak valid!");
            Sleep(1000);
            gotoxy(3, 26);
            printf("                     ");
            continue;
        }

        jadwal pilih = list[pilihan - 1];

        // ===== JIKA SUDAH NONAKTIF =====
        if (pilih.status == 0) {
            gotoxy(3, 26);
            printf("Jadwal sudah nonaktif!");
            Sleep(1200);
            gotoxy(3, 26);
            printf("                         ");
            continue;   // 🔥 BALIK KE INPUT NO URUT
        }

        // ===== DETAIL JADWAL =====
        bentukframe(35, 27, 60, 15);
        gotoxy(55, 27); printf("=== DETAIL JADWAL ===");

        gotoxy(37, 29); printf("Tanggal      : %s", pilih.tanggal);
        gotoxy(37, 30); printf("Kota Awal    : %s", pilih.kotaAsal);
        gotoxy(37, 31); printf("Kota Akhir   : %s", pilih.kotaTujuan);
        gotoxy(37, 32); printf("Jam          : %s", pilih.jamBerangkat);
        gotoxy(37, 33); printf("Kategori     : %s", pilih.kategori);
        gotoxy(37, 34); printf("Armada       : %s", pilih.nama_armada);

        char hargaStr[25];
        formatHarga(pilih.harga, hargaStr);
        gotoxy(37, 35); printf("Harga        : %s", hargaStr);

        gotoxy(37, 36);
        printf("Status       : Aktif");

        // ===== KONFIRMASI =====
        gotoxy(37, 37);
        printf("Yakin ingin menonaktifkan jadwal ini? (y/n): ");
        gotoxy(83, 37);

        konfirmasi = '\0';

        while (1) {
            char ch2 = getch();

            if (ch2 == 27) {
                gotoxy(37, 38);
                printf("Dibatalkan!");
                getch();
                return;
            }

            if (ch2 == 8 && konfirmasi != '\0') {
                konfirmasi = '\0';
                gotoxy(83, 37);
                printf(" ");
                gotoxy(83, 37);
                continue;
            }

            ch2 = tolower(ch2);

            if ((ch2 == 'y' || ch2 == 'n') && konfirmasi == '\0') {
                konfirmasi = ch2;
                printf("%c", ch2);
            }

            if (ch2 == 13 && konfirmasi != '\0') break;
        }

        if (konfirmasi != 'y') {
            gotoxy(37, 38);
            printf("Dibatalkan!");
            getch();
            return;
        }

        // ===== PROSES NONAKTIFKAN =====
        fp = fopen("jadwal.dat", "rb");
        temp = fopen("temp.dat", "wb");

        while (fread(&data, sizeof(jadwal), 1, fp) == 1) {
            if (strcmp(data.id, pilih.id) == 0) {
                strcpy(data.status, "Nonaktif");
                found = 1;
            }
            fwrite(&data, sizeof(jadwal), 1, temp);
        }

        fclose(fp);
        fclose(temp);

        if (found) {
            remove("jadwal.dat");
            rename("temp.dat", "jadwal.dat");
            gotoxy(37, 38);
            printf("Jadwal berhasil dinonaktifkan!");
        } else {
            remove("temp.dat");
            gotoxy(37, 38);
            printf("Gagal menonaktifkan jadwal!");
        }

        getch();
        return;
    }
}

#endif