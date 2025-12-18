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
void inputPasswordBaru(char *passwordBaru, int row, int col);

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
    gotoxy(3, 25); printf("Pilih No Urut: ");

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
int totalFields = 8; // 0-6 field input, 7 tombol simpan

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
        if (arrow == 72) { // UP
            selectedField--;
            if (selectedField < 0) selectedField = totalFields;
        }
        else if (arrow == 80) { // DOWN
            selectedField++;
            if (selectedField > totalFields) selectedField = 0;
        }
    }
    // Handle ENTER
    else if (ch == 13) {
        // Jika pilih tombol SIMPAN
        if (selectedField == totalFields) {
            editing = 0;
            break;
        }

        int inputX = 109; // Koordinat X untuk input

        // Clear previous input area
        clearArea(inputX, 32 + selectedField, 25, 1);

        switch(selectedField) {
            case 0: // Username
                setPointer(33, inputX);
                INPUTNama(data.nama);
                if (strlen(data.nama) == 0) {
                    fclose(fp);
                    fclose(sampah);
                    remove("sampah.dat");
                    return;
                }
                break;


            case 1: // Nama
                setPointer(34, 109);
                inputUsername(data.username, 33, 108);
                if (strlen(data.username) == 0) {
                    fclose(fp);
                    fclose(sampah);
                    remove("sampah.dat");
                    return;
                }
                break;


            case 2: // Password
                gotoxy(97, 34);
                printf("Password Lama : ");
                if (cekPasswordLama(targetNo) == 1) {
                    clearArea(97, 34, 40, 1);
                    gotoxy(97, 34);
                    printf("Password Baru : ");
                    inputPasswordBaru(data.password, 34, 113);

                    // User cancel
                    if (strlen(data.password) == 0) {
                        fclose(fp);
                        fclose(sampah);
                        remove("sampah.dat");
                        return;
                    }
                } else {
                    // Password salah atau user cancel
                    fclose(fp);
                    fclose(sampah);
                    remove("sampah.dat");
                    return;
                }
                break;

            case 3: // Tgl Lahir
                setPointer(35, inputX);
                inputTanggal(data.tgl);
                if (strlen(data.tgl) == 0) {
                    fclose(fp);
                    fclose(sampah);
                    remove("sampah.dat");
                    return;
                }
                break;

            case 4: // No Telpon
                inputNoTelp(data.notlpn, inputX, 36);
                if (strlen(data.notlpn) == 0) {
                    fclose(fp);
                    fclose(sampah);
                    remove("sampah.dat");
                    return;
                }
                break;

            case 5: // Gender
                inputGender(data.gender, 104, 37);
                if (strlen(data.gender) == 0) {
                    fclose(fp);
                    fclose(sampah);
                    remove("sampah.dat");
                    return;
                }
                break;

            case 6: // Status
                inputStatus(data.status, 104, 38);
                if (strlen(data.status) == 0) {
                    fclose(fp);
                    fclose(sampah);
                    remove("sampah.dat");
                    return;
                }
                break;
                case 7: // Status
                inputRole(data.Role, 104, 39);
                if (strlen(data.Role) == 0) {
                    fclose(fp);
                    fclose(sampah);
                    remove("sampah.dat");
                    return;
                }
                break;
        }
    }
    // Handle ESC
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



//===========================================================//
//============BAGIAN VALIDASI PASSWORD====================//
int cekPasswordLama(int targetNo) {
    FILE *fp;
    staff data;
    char inputPwLama[200] = "";
    char passwordBenar[200] = "";

    fp = fopen("staff.dat", "rb");
    if (fp == NULL) return 0;


    fseek(fp, (targetNo - 1) * sizeof(staff), SEEK_SET);

    if (fread(&data, sizeof(staff), 1, fp) != 1) {
        fclose(fp);
        return 0;
    }

    strcpy(passwordBenar, data.password);
    fclose(fp);

    while (1) {
        clearArea(113, 34, 25, 3);
        clearArea(97, 41, 25, 3);

        gotoxy(97, 34);
        printf("Password Lama : ");
        PWesc(inputPwLama, 34, 113);

        if (strlen(inputPwLama) == 0)
            return 0;

        if (strcmp(inputPwLama, passwordBenar) == 0)
            return 1;

        gotoxy(97, 41);
        printf("✗ Password salah!");
        Sleep(1000);
    }
}


void inputPasswordBaru(char *passwordBaru, int row, int col) {
    clearArea(col, row, 30, 1);
    PWesc(passwordBaru, row, col);
}

#endif //PROJEK_UPDATE_H