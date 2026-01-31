//
// Created by ASUS on 12/14/2025.
//

#ifndef PROJEK_DELETERUTE_H
#define PROJEK_DELETERUTE_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "../FrameTabel.h"
#include "createrute.h"


// ==================================================
// FORMAT HARGA RUPIAH
// ==================================================
void formatHargass(int harga, char *out) {
    int juta = harga / 1000000;
    int ribu = (harga / 1000) % 1000;
    int sisa = harga % 1000;

    if (juta > 0) {
        sprintf(out, "Rp%d.%03d.%03d,00", juta, ribu, sisa);
    } else if (ribu > 0) {
        sprintf(out, "Rp%d.%03d,00", ribu, sisa);
    } else {
        sprintf(out, "Rp%d,00", sisa);
    }
}

// ==================================================
// DELETE RUTE (UBAH STATUS JADI NONAKTIF)
// ==================================================
void deleterute() {
    FILE *fp;
    Rute data;
    Rute list[1000];
    int count = 0;
    int pilihan;
    char konfirmasi;
    int found = 0;

    // ===== BUKA FILE =====
    fp = fopen("rute.dat", "rb");
    if (!fp) {
        gotoxy(3, 27); printf("File rute.dat tidak ditemukan!");
        getch();
        return;
    }

    // ===== BACA DATA =====
    while (fread(&data, sizeof(Rute), 1, fp) == 1) {
        list[count++] = data;
    }
    fclose(fp);

    // ===== SORTING (descending by ID) =====
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(list[i].id, list[j].id) < 0) {
                Rute temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }

    if (count == 0) {
        gotoxy(3, 27); printf("Tidak ada data rute!");
        getch();
        return;
    }

    // ===== INPUT NOMOR =====
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
                    break;
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

        if (idx == 0) continue;

        if (pilihan >= 1 && pilihan <= count) break;

        gotoxy(3, 26);
        printf("Pilihan tidak valid!");
        Sleep(1500);
        gotoxy(3, 26);
        printf("                     ");
    }

    Rute terpilih = list[pilihan - 1];

    // ===== VALIDASI: CEK APAKAH RUTE SUDAH NONAKTIF =====
    if (strcmp(terpilih.statusRute, "Nonaktif") == 0) {
        bentukframe(37, 27, 108, 8);
        gotoxy(75, 27); printf("=== PERINGATAN ===");
        gotoxy(39, 30); printf("Rute %s sudah nonaktif!", terpilih.id);
        gotoxy(39, 31); printf("Tidak dapat dihapus lagi.");
        gotoxy(39, 33); printf("Tekan tombol apa saja untuk kembali...");
        getch();
        return;
    }

    // ===== DETAIL RUTE =====
    char hargaStr[25];
    formatHargass((int)terpilih.harga, hargaStr);

    bentukframe(37, 27, 108, 12);
    gotoxy(75, 27); printf("=== DETAIL RUTE ===");

    gotoxy(39, 28); printf("ID            : %s", terpilih.id);
    gotoxy(39, 29); printf("Kota Asal     : %s", terpilih.kotaAsal);
    gotoxy(39, 30); printf("Kota Tujuan   : %s", terpilih.kotaTujuan);
    gotoxy(39, 31); printf("Harga         : %s", hargaStr);
    gotoxy(39, 32); printf("Jam Berangkat : %s", terpilih.jamBerangkat);
    gotoxy(39, 33); printf("Jam Tiba      : %s", terpilih.jamTiba);
    gotoxy(39, 34); printf("Status Rute   : %s", terpilih.statusRute);

    // ===== KONFIRMASI =====
    gotoxy(38, 36);
    printf("Yakin ingin menonaktifkan rute ini? (y/n): ");
    gotoxy(80, 36);

    konfirmasi = '\0';
    while (1) {
        char ch = getch();

        if (ch == 27) {
            gotoxy(38, 37);
            printf("Penonaktifan dibatalkan!");
            getch();
            return;
        }

        if (ch == 8 && konfirmasi != '\0') {
            konfirmasi = '\0';
            gotoxy(80, 36);
            printf(" ");
            gotoxy(80, 36);
            continue;
        }

        ch = tolower(ch);

        if ((ch == 'y' || ch == 'n') && konfirmasi == '\0') {
            konfirmasi = ch;
            printf("%c", ch);
        }

        if (ch == 13 && konfirmasi != '\0') {
            break;
        }
    }

    if (konfirmasi != 'y') {
        gotoxy(38, 37);
        printf("Penonaktifan dibatalkan!");
        getch();
        return;
    }

    // ===== PROSES UBAH STATUS JADI NONAKTIF =====
    fp = fopen("rute.dat", "rb+");
    if (!fp) {
        gotoxy(38, 37); printf("Gagal membuka file!");
        getch();
        return;
    }

    while (fread(&data, sizeof(Rute), 1, fp) == 1) {
        if (strcmp(data.id, terpilih.id) == 0) {
            // Ubah status jadi Nonaktif
            strcpy(data.statusRute, "Nonaktif");

            // Mundur 1 record untuk overwrite
            fseek(fp, -sizeof(Rute), SEEK_CUR);
            fwrite(&data, sizeof(Rute), 1, fp);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found) {
        gotoxy(38, 37); printf("Rute %s berhasil dinonaktifkan!", terpilih.id);
    } else {
        gotoxy(38, 37); printf("Gagal menonaktifkan rute!");
    }

    getch();
}

#endif // PROJEK_DELETERUTE_H