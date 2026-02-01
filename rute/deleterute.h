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
// NONAKTIFKAN RUTE (UBAH STATUS)
// ==================================================
void deleterute() {
    FILE *fp;
    Rute data;
    Rute list[1000];
    int count = 0;
    int pilihan;
    char konfirmasi = '\0';
    int found = 0;

    // ===== BUKA FILE =====
    fp = fopen("rute.dat", "rb");
    if (!fp) {
        gotoxy(3, 27);
        printf("File rute.dat tidak ditemukan!");
        getch();
        return;
    }

    // ===== BACA DATA =====
    while (fread(&data, sizeof(Rute), 1, fp) == 1) {
        list[count++] = data;
    }
    fclose(fp);

    if (count == 0) {
        gotoxy(3, 27);
        printf("Tidak ada data rute!");
        getch();
        return;
    }

    // ===== INPUT NOMOR URUT DENGAN VALIDASI LENGKAP =====
    Rute terpilih;
    while (1) {
        char buffer[10] = "";
        int idx = 0;
        char ch;

        gotoxy(3, 25);
        printf("Pilih No Urut : ");
        gotoxy(20, 25);
        printf("          ");  // Bersihkan area input
        gotoxy(20, 25);

        // Loop input angka
        while (1) {
            ch = getch();

            // ESC → Batal
            if (ch == 27) {
                gotoxy(3, 26);
                printf("Dibatalkan!               ");
                getch();
                return;
            }

            // ENTER
            if (ch == 13) {
                // Validasi: cek apakah kosong
                if (idx == 0) {
                    gotoxy(3, 26);
                    printf("Angka tidak boleh kosong!");
                    Sleep(1500);
                    gotoxy(3, 26);
                    printf("                          ");
                    break;  // Keluar inner loop, ulangi input
                }

                buffer[idx] = '\0';
                pilihan = atoi(buffer);
                break;  // Keluar inner loop dengan nilai valid
            }

            // BACKSPACE
            if (ch == 8 && idx > 0) {
                idx--;
                buffer[idx] = '\0';
                gotoxy(20, 25);
                printf("          ");  // Hapus tampilan
                gotoxy(20, 25);
                printf("%s", buffer);  // Tampil ulang
            }

            // ANGKA 0-9
            if (ch >= '0' && ch <= '9') {
                if (idx < 9) {
                    buffer[idx++] = ch;
                    buffer[idx] = '\0';
                    printf("%c", ch);
                }
            }
        }

        // Jika input kosong, continue (ulangi dari awal)
        if (idx == 0) continue;

        // Validasi: nomor harus dalam range
        if (pilihan < 1 || pilihan > count) {
            gotoxy(3, 26);
            printf("Nomor Urut %d Tidak Ditemukan", pilihan);
            Sleep(1500);
            gotoxy(3, 26);
            printf("                                ");
            continue;  // Ulangi input
        }

        // ===== AMBIL DATA TERPILIH =====
        terpilih = list[pilihan - 1];

        // ===== CEK STATUS: JIKA SUDAH NONAKTIF =====
        if (strcmp(terpilih.status, "Nonaktif") == 0) {
            gotoxy(3, 26);
            printf("Rute ini sudah nonaktif!");
            Sleep(1500);
            gotoxy(3, 26);
            printf("                          ");
            continue;  // Ulangi input
        }

        // Jika lolos semua validasi, keluar dari loop
        break;
    }

    // ===== DETAIL RUTE DALAM BOX =====
    char hargaStr[25];
    formatHarga((long)terpilih.harga, hargaStr);

    bentukframe(37, 27, 47, 13);
    gotoxy(52, 27); printf("====DATA %d===", pilihan);
    gotoxy(38, 28); printf("ID            : %s", terpilih.id);
    gotoxy(38, 29); printf("Kota Asal     : %s", terpilih.kotaAsal);
    gotoxy(38, 30); printf("Kota Tujuan   : %s", terpilih.kotaTujuan);
    gotoxy(38, 31); printf("Harga         : %s", hargaStr);
    gotoxy(38, 32); printf("Jam Berangkat : %s", terpilih.jamBerangkat);
    gotoxy(38, 33); printf("Jam Tiba      : %s", terpilih.jamTiba);
    gotoxy(38,34);  printf("Durasi        : %s", terpilih.durasi);
    gotoxy(38, 35); printf("Status        : %s", terpilih.status);

    // ===== KONFIRMASI (Y/N DENGAN BACKSPACE & ESC) =====
    gotoxy(38, 36);
    printf("Yakin ingin menonaktifkan rute ini? (y/n): ");
    gotoxy(81, 36);

    konfirmasi = '\0';

    while (1) {
        char ch = getch();

        // ESC → Batal
        if (ch == 27) {
            gotoxy(38, 37);
            printf("Pembatalan proses!               ");
            getch();
            return;
        }

        // BACKSPACE → Hapus y/n yang sudah diketik
        if (ch == 8 && konfirmasi != '\0') {
            konfirmasi = '\0';
            gotoxy(81, 36);
            printf(" ");
            gotoxy(81, 36);
            continue;
        }

        // Konversi ke lowercase
        ch = tolower(ch);

        // Hanya terima 'y' atau 'n', dan hanya jika belum ada input
        if ((ch == 'y' || ch == 'n') && konfirmasi == '\0') {
            konfirmasi = ch;
            gotoxy(81, 36);
            printf("%c", toupper(ch));  // Tampil uppercase
        }

        // ENTER setelah input valid (y/n sudah diisi)
        if (ch == 13 && konfirmasi != '\0') {
            break;
        }
    }

    // Jika user pilih 'n' (tidak jadi)
    if (konfirmasi != 'y') {
        gotoxy(38, 37);
        printf("Pembatalan proses!               ");
        getch();
        return;
    }

    // ===== PROSES UBAH STATUS MENJADI NONAKTIF =====
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].id, terpilih.id) == 0) {
            strcpy(list[i].status, "Nonaktif");
            found = 1;
            break;
        }
    }

    if (found) {
        // Tulis ulang SEMUA data ke file
        fp = fopen("rute.dat", "wb");
        if (!fp) {
            gotoxy(38, 37);
            printf("Gagal membuka file!              ");
            getch();
            return;
        }

        for (int i = 0; i < count; i++) {
            fwrite(&list[i], sizeof(Rute), 1, fp);
        }
        fclose(fp);

        gotoxy(38, 37);
        printf("Rute '%s' berhasil dinonaktifkan!", terpilih.id);
    } else {
        gotoxy(38, 37);
        printf("Terjadi kesalahan saat memproses!");
    }

    getch();
}

#endif // PROJEK_DELETERUTE_H