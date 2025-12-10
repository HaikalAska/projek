#ifndef PROJEK_UPDATE_H
#define PROJEK_UPDATE_H
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "create.h"
#include "read.h"
#include "../FrameTabel.h"

void update() {
    int startY_input = 29;
    int startX_input = 50;
    FILE *fp, *sampah;
    staff data;
    char strNo[10];
    int targetNo = 0;
    int currentNo = 1;
    int found = 0;
    int idx;

    // --- Input Nomor Urut ---
    gotoxy(3, startY_input); printf("Pilih No Urut: ");

    idx = 0;
    while (1) {
        char ch = _getch();
        if (ch == 27) return;
        else if (ch == 13) {
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

    if (targetNo <= 0) {
        gotoxy(startX_input, startY_input + 2); printf("Input nomor tidak valid!");
        _getch();
        return;
    }

    fp = fopen("staff.dat", "rb");
    sampah = fopen("sampah.dat", "wb");

    if (!fp || !sampah) {
        gotoxy(startX_input, startY_input + 2); printf("Gagal membuka file database!");
        _getch();
        return;
    }

    while (fread(&data, sizeof(staff), 1, fp) == 1) {

        if (currentNo == targetNo) {
            found = 1;

            // --- Tampilan Navigasi & Border ---
            gotoxy(33,11); printf("[ESC] Batal ");
            gotoxy(33,10); printf("[ENTER] Edit ");
            gotoxy(100, 14);printf("NAVIGASI \xE2\x86\x91 \xE2\x86\x93");

            // Tampilkan Data Lama (Kiri)
            printBorder(48, 30, 30, 10);
            gotoxy(startX_input, startY_input + 2); printf("=== Data Lama ===");
            gotoxy(startX_input, startY_input + 3); printf("Nama      : %s", data.username);

            // Masking Password Lama
            char maskedPw[50];
            int pwLen = strlen(data.password);
            for(int i = 0; i < pwLen; i++) maskedPw[i] = '*';
            maskedPw[pwLen] = '\0';
            gotoxy(startX_input, startY_input + 4); printf("Password  : %s", maskedPw);

            gotoxy(startX_input, startY_input + 5); printf("Tgl Lahir : %s", data.tgl);
            gotoxy(startX_input, startY_input + 6); printf("No Telpon : %s", data.notlpn);
            gotoxy(startX_input, startY_input + 7); printf("Gender    : %s", data.gender);

            // Tampilkan Form Input Baru (Kanan)
            printBorder(98, 30, 35, 10);
            gotoxy(100, 31); printf("=== MASUKKAN DATA BARU ===");

            gotoxy(103,32); printf("Nama      : "); // Tampilkan data saat ini dulu
            gotoxy(103,33); printf("Password  : ");
            gotoxy(103,34); printf("Tgl Lahir : ");
            gotoxy(103,35); printf("No Telpon : ");
            gotoxy(103,36); printf("Gender    : ");
            gotoxy(103,37); printf("[ SIMPAN PERUBAHAN ]");

            int selectedField = 0;
            int editing = 1;

            // ==========================================
            // LOGIKA NAVIGASI (LOOPING)
            // ==========================================
            while (editing) {
                // Gambar Kursor Navigasi
                for (int i = 0; i < 6; i++) {
                    gotoxy(100, 32 + i);
                    if (i == selectedField) printf(">>");
                    else printf("  ");
                }

                int ch = _getch();

                // Handle Arrow Keys (Atas/Bawah)
                if (ch == 0 || ch == 224) {
                    int arrow = _getch();
                    if (arrow == 72) { // UP
                        selectedField--;
                        if (selectedField < 0) selectedField = 5;
                    }
                    else if (arrow == 80) { // DOWN
                        selectedField++;
                        if (selectedField > 5) selectedField = 0;
                    }
                }
                // Handle ENTER (Pilih Field untuk Diedit)
                else if (ch == 13) {

                    // Jika pilih [SIMPAN PERUBAHAN]
                    if (selectedField == 5) {
                        editing = 0; // Keluar dari loop editing
                        break;
                    }

                    // Koordinat input (sesuaikan agar rapi)
                    int inputX = 114;

                    // --- SWITCH CASE UNTUK MEMANGGIL FUNGSI INPUT ---
                    switch(selectedField) {
                        case 0: // Nama
                            gotoxy(inputX, 32);
                            inputID(data.username);
                            break;

                        case 1: // Password
                            gotoxy(inputX, 33);
                            // Asumsi inputPassword butuh (buffer, x, y)
                            PWesc(data.password, inputX, 33);
                            break;

                        case 2: // Tgl Lahir
                            gotoxy(inputX, 34);
                            inputTanggal(data.tgl);
                            break;

                        case 3: // No Telpon
                            gotoxy(inputX, 35);
                            inputNoTelp(data.notlpn, inputX, 35);
                            break;

                        case 4: // Gender
                            // Panggil fungsi inputGender yang sudah dimodifikasi (buffer, x, y)
                            inputGender(data.gender, inputX, 36);
                            break;
                    }
                }
                // Handle ESC (Batal Update seluruhnya)
                else if (ch == 27) {
                    fclose(fp);
                    fclose(sampah);
                    remove("sampah.dat");
                    return;
                }
            }

            // Pastikan Role tetap Staff
            strcpy(data.Role, "Staff");

            // Simpan data yang sudah diedit ke file sampah
            fwrite(&data, sizeof(staff), 1, sampah);

        } else {
            // Salin data yang tidak diedit (bukan targetNo)
            fwrite(&data, sizeof(staff), 1, sampah);
        }

        currentNo++;
    }

    fclose(fp);
    fclose(sampah);

    if (found) {
        remove("staff.dat");
        rename("sampah.dat", "staff.dat");
        gotoxy(startX_input, startY_input + 18); printf("Data Berhasil Di Update!");
    }
    else {
        remove("sampah.dat");
        gotoxy(35, 30); printf("Nomor urut %d tidak ditemukan!", targetNo);
    }

    _getch();
}

#endif //PROJEK_UPDATE_H