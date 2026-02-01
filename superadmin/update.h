#ifndef PROJEK_UPDATE_H
#define PROJEK_UPDATE_H
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "create.h"
#include "read.h"
#include "../FrameTabel.h"

int cekPasswordLama(int targetNo);
int inputPasswordBaru(char *passwordBaru, int row, int col);

void update() {
    int startY_input = 29;
    int startX_input = 50;
    FILE *fp, *sampah;
    staff data;
    staff staffList[100];
    int count = 0;
    char strNo[10];
    int targetNo = 0;
    int found = 0;
    int idx;

    // --- Input Nomor Urut ---
    gotoxy(3, 25); printf("Pilih No Urut: ");

    idx = 0;
    while (1) {
        char ch = _getch();
        if (ch == 27) return;
        else if (ch == 13) {
            if (idx == 0) {
                gotoxy(3, 26);
                printf("Input tidak boleh kosong!");
                Sleep(1000);
                clearArea(97, 26 + 8, 35, 1);
                gotoxy(17, 25);
                continue;
            }

            targetNo = 0;
            for (int i = 0; i < idx; i++) {
                targetNo = targetNo * 10 + (strNo[i] - '0');
            }
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

    // Load semua data dulu
    fp = fopen("staff.dat", "rb");
    if (!fp) {
        gotoxy(startX_input, startY_input + 2); printf("Gagal membuka file database!");
        _getch();
        return;
    }

    while (fread(&data, sizeof(staff), 1, fp) == 1) {
        staffList[count++] = data;
    }
    fclose(fp);

    // Sorting berdasarkan ID (terbesar ke terkecil)
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(staffList[i].id, staffList[j].id) < 0) {
                staff temp = staffList[i];
                staffList[i] = staffList[j];
                staffList[j] = temp;
            }
        }
    }

    // Cek apakah targetNo valid
    if (targetNo < 1 || targetNo > count) {
        gotoxy(startX_input, startY_input + 2); printf("Nomor urut tidak ditemukan!");
        _getch();
        return;
    }

    // Ambil data yang akan di-update
    data = staffList[targetNo - 1];
    found = 1;

    // --- Tampilan Navigasi & Border ---
    bentukframe(3, 29, 27, 10);
    gotoxy(5,30); printf("===  MENU NAVIGASI  ===");
    gotoxy(4, 32);printf("NAVIGASI [\xE2\x86\x91 \xE2\x86\x93]");
    gotoxy(4, 34);printf("[ENTER] Pilih");
    gotoxy(4, 36);printf("[Esc] Keluar");
    gotoxy(50, 41);printf("KOSONGKAN JIKA TIDAK INGIN MEMILIH");

    // Tampilkan Data Lama (Kiri)
    bentukframe(48, 29, 45, 12);
    gotoxy(65, 30); printf("Data Lama");
    gotoxy(startX_input, startY_input + 3); printf("Username  : %s", data.username);
    gotoxy(startX_input, startY_input + 4); printf("Nama      : %s", data.nama);

    // Masking Password Lama
    char maskedPw[50];
    int pwLen = strlen(data.password);
    for(int i = 0; i < pwLen; i++) maskedPw[i] = '*';
    maskedPw[pwLen] = '\0';
    gotoxy(startX_input, startY_input + 5); printf("Password  : %s", maskedPw);

    gotoxy(startX_input, startY_input + 6); printf("Tgl Lahir : %s", data.tgl);
    gotoxy(startX_input, startY_input + 7); printf("No Telpon : %s", data.notlpn);
    gotoxy(startX_input, startY_input + 8); printf("Gender    : %s", data.gender);
    gotoxy(startX_input, startY_input + 9); printf("Status    : %s", data.status);
    gotoxy(startX_input, startY_input + 10); printf("Role      : %s", data.Role);

    // Tampilkan Form Input Baru (Kanan)
    bentukframe(95, 29, 55, 13);
    gotoxy(112, 30); printf("Data Baru");

    // Tampilan Form
    gotoxy(97,32); printf("Nama      : ");
    gotoxy(97,33); printf("Username  : ");
    gotoxy(97,34); printf("Password  : ");
    gotoxy(97,35); printf("Tgl Lahir : ");
    gotoxy(97,36); printf("No Telpon : ");
    gotoxy(97,37); printf("Gender    : ");
    gotoxy(97,38); printf("Status    : ");
    gotoxy(97,39); printf("Role      : ");
    gotoxy(97,40); printf("[ SIMPAN PERUBAHAN ]");

    int selectedField = 0;
    int editing = 1;
    int totalFields = 8;

    while (editing) {
        // Gambar Kursor Navigasi
        for (int i = 0; i <= totalFields; i++) {
            gotoxy(95, 32 + i);
            if (i == selectedField) {
                printf(">>");
            } else {
                printf("│ ");
            }
        }

        int ch = _getch();

        // Handle Arrow Keys
        if (ch == 0 || ch == 224) {
            int arrow = _getch();
            if (arrow == 72) {
                selectedField--;
                if (selectedField < 0) selectedField = totalFields;
            }
            else if (arrow == 80) {
                selectedField++;
                if (selectedField > totalFields) selectedField = 0;
            }
        }
        // Handle ENTER
        else if (ch == 13) {
            if (selectedField == totalFields) {
                editing = 0;
                break;
            }

            int inputX = 109;
            clearArea(inputX, 32 + selectedField, 25, 1);

            switch(selectedField) {
                case 0:
                    setPointer(33, inputX);
                    if (NamaUpdate(data.nama) == 0) {
                        break;
                    }
                    break;

                case 1:
                    setPointer(34, 109);
                    if (UpdateUsername(data.username, 33, 108) == 0) {
                        break;
                    }
                    break;

                case 2:
                    int cekPass = cekPasswordLama(targetNo);
                    if (cekPass == 1) {
                        clearArea(97, 34, 40, 1);
                        gotoxy(97, 34);
                        printf("Password Baru : ");
                        if (inputPasswordBaru(data.password, 34, 113) == 0) {
                            break;
                        }
                    } else if (cekPass == -1) {
                        break;
                    }
                    break;

                case 3:
                    if (UpdateTanggal(data.tgl, inputX, 35) == 0) {
                        break;
                    }
                    break;

                case 4:
                    if (UpdateNoTelp(data.notlpn, inputX, 36) == 0) {
                        break;
                    }
                    break;

                case 5:
                    if (inputGender(data.gender, 104, 37) == 0) {
                        break;
                    }
                    break;

                case 6:
                    if (inputStatus(data.status, 104, 38) == 0) {
                        break;
                    }
                    break;

                case 7:
                    if (inputRole(data.Role, 104, 39) == 0) {
                        break;
                    }
                    break;
            }
        }
        // Handle ESC
        else if (ch == 27) {
            return;
        }
    }

    // Update data di array
    staffList[targetNo - 1] = data;

    // Tulis ulang semua data ke file
    sampah = fopen("sampah.dat", "wb");
    if (!sampah) {
        gotoxy(startX_input, startY_input + 2); printf("Gagal membuka file!");
        _getch();
        return;
    }

    for (int i = 0; i < count; i++) {
        fwrite(&staffList[i], sizeof(staff), 1, sampah);
    }
    fclose(sampah);

    remove("staff.dat");
    rename("sampah.dat", "staff.dat");
    gotoxy(startX_input, startY_input + 18); printf("Data Berhasil Di Update!");

    _getch();
}

int cekPasswordLama(int targetNo) {
    FILE *fp;
    staff data;
    staff staffList[100];
    int count = 0;
    char inputPwLama[200] = "";
    char passwordBenar[200] = "";

    fp = fopen("staff.dat", "rb");
    if (fp == NULL) return -1;

    // Load dan sort data
    while (fread(&data, sizeof(staff), 1, fp) == 1) {
        staffList[count++] = data;
    }
    fclose(fp);

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(staffList[i].id, staffList[j].id) < 0) {
                staff temp = staffList[i];
                staffList[i] = staffList[j];
                staffList[j] = temp;
            }
        }
    }

    // Ambil password dari data yang sudah di-sort
    strcpy(passwordBenar, staffList[targetNo - 1].password);

    while (1) {
        gotoxy(97, 34);
        printf("Password Lama : ");
        int result = PWesc(inputPwLama, 34, 113);

        if (result == 0) {
            clearArea(113, 34, 25, 1);
            return -1;
        }

        if (strcmp(inputPwLama, passwordBenar) == 0) {
            clearArea(113, 34, 25, 1);
            return 1;
        }

        gotoxy(97, 42);
        printf("✗ Password salah!");
        Sleep(1000);
        clearArea(113, 34, 25, 1);
        clearArea(97, 42, 25, 1);
    }
}

int inputPasswordBaru(char *passwordBaru, int row, int col) {
    return PWesc(passwordBaru, row, col);
}

#endif //PROJEK_UPDATE_H