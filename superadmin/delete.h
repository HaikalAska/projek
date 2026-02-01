#ifndef PROJEK_DELETE_H
#define PROJEK_DELETE_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "create.h"

void delete(){
    FILE *fp;
    staff data;
    staff staffList[100];
    int count = 0;
    int pilihan;
    char konfirmasi;
    int found = 0;
    char strNo[10];
    int targetNo = 0;
    int currentNo = 1;
    int idx;

    fp = fopen("staff.dat","rb");
    if (fp == NULL) {
        gotoxy(3,13); printf("File tidak ditemukan!");
        getchar();
        return;
    }

    while (fread(&data, sizeof(staff), 1, fp) == 1) {
        staffList[count] = data;
        count++;
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

    if (count == 0) {
        gotoxy(3, 13); printf("Tidak ada data staff!");
        getchar();
        getchar();
        return;
    }

    while (1) {
        gotoxy(3, 25);
        printf("Pilih No Urut: ");

        idx = 0;
        while (1) {
            char ch = _getch();

            if (ch == 27) return;

            else if (ch == 13) {
                if (idx == 0) {
                    gotoxy(3, 26);
                    printf("Input tidak boleh kosong!");
                    Sleep(800);
                    clearArea(3, 26, 30, 1);
                    clearArea(17, 25, 10, 1);
                    gotoxy(17, 25);
                    continue;
                }

                targetNo = 0;
                for (int i = 0; i < idx; i++) {
                    targetNo = targetNo * 10 + (strNo[i] - '0');
                }
                break;
            }

            else if (ch == 8) {
                if (idx > 0) {
                    idx--;
                    printf("\b \b");
                }
            }

            else if (ch >= '0' && ch <= '9') {
                if (idx < 9) {
                    strNo[idx++] = ch;
                    printf("%c", ch);
                }
            }
        }

        pilihan = targetNo;

        if (pilihan < 1 || pilihan > count) {
            gotoxy(35, 30);
            printf("Nomor Urut %d Tidak Ditemukan!", pilihan);
            Sleep(1000);
            clearArea(35, 30, 40, 1);
            clearArea(17, 25, 10, 1);
            continue;
        }

        staff terpilih = staffList[pilihan - 1];

        if (strcmp(terpilih.status, "Nonaktif") == 0) {
            gotoxy(35, 30);
            printf("Akun sudah nonaktif!");
            Sleep(1000);
            clearArea(35, 30, 40, 1);
            clearArea(17, 25, 10, 1);
            continue;
        }

        bentukframe(37, 27, 47, 11);
        gotoxy(52, 27);  printf("====DATA %d===", pilihan);
        gotoxy(38, 28);  printf("Username    : %s", terpilih.username);
        gotoxy(38, 29);  printf("Nama        : %s", terpilih.nama);
        char maskedPw[50];
        int pwLen = strlen(terpilih.password);
        memset(maskedPw, '*', pwLen);
        maskedPw[pwLen] = '\0';
        gotoxy(38, 30); printf("Password    : %s", maskedPw);
        gotoxy(38, 31); printf("Tgl Lahir   : %s", terpilih.tgl);
        gotoxy(38, 32); printf("No Telpon   : %s", terpilih.notlpn);
        gotoxy(38, 33); printf("Gender      : %s", terpilih.gender);
        gotoxy(38, 34); printf("Status      : %s", terpilih.status);

        gotoxy(38, 35); printf("Yakin ingin menonaktifkan data ini? (y/n): ");

        while (1) {
            char ch = _getch();

            if (ch == 27) return;

            if (ch == 'y' || ch == 'Y') {
                konfirmasi = 'y';
                printf("Y");
                break;
            }else if (ch == 'n' || ch == 'N') {
                konfirmasi = 'n';
                printf("N");
                break;
            }
        }

        if (tolower(konfirmasi) != 'y') {
            gotoxy(38, 36); printf("Pembatalan proses!");
            getchar();
            getchar();
            return;
        }

        for (int i = 0; i < count; i++) {
            if (strcmp(staffList[i].id, terpilih.id) == 0) {
                strcpy(staffList[i].status, "Nonaktif");
                found = 1;
                break;
            }
        }

        if (found) {
            fp = fopen("staff.dat", "wb");
            if (fp == NULL) {
                gotoxy(38, 36); printf("Gagal membuka file!");
                getchar();
                getchar();
                return;
            }

            for (int i = 0; i < count; i++) {
                fwrite(&staffList[i], sizeof(staff), 1, fp);
            }
            fclose(fp);

            gotoxy(38, 36); printf("Staff '%s' berhasil dinonaktifkan!", terpilih.username);
        } else {
            gotoxy(38, 36); printf("Terjadi kesalahan saat memproses!");
        }

        getchar();
        getchar();
        return;
    }
}

#endif