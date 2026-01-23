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

    if (count == 0) {
        gotoxy(3, 13); printf("Tidak ada data staff!");
        getchar();
        getchar();
        return;
    }

    // --- Input Nomor Urut ---
    gotoxy(3, 25);
    printf("Pilih No Urut: ");

    idx = 0;
    while (1) {
        char ch = _getch();

        // ESC
        if (ch == 27) return;

        // ENTER
        else if (ch == 13) {
            if (idx == 0) {
                gotoxy(3, 26);
                printf("Input tidak boleh kosong!");
                gotoxy(17, 25);
                continue;
            }

            targetNo = 0;
            for (int i = 0; i < idx; i++) {
                targetNo = targetNo * 10 + (strNo[i] - '0');
            }
            break;
        }

        // BACKSPACE
        else if (ch == 8) {
            if (idx > 0) {
                idx--;
                printf("\b \b");
            }
        }

        // ANGKA SAJA
        else if (ch >= '0' && ch <= '9') {
            if (idx < 9) {
                strNo[idx++] = ch;
                printf("%c", ch);
            }
        }

        else {
            // do nothing
        }
    }

    pilihan =  targetNo;

    if (pilihan < 1 || pilihan > count) {
        gotoxy(35, 30);
        printf("Nomor Urut %d Tidak DItemukan", pilihan);
        getchar();
        getchar();
        return;
    }

    // Tampilkan detail data dalam box
    staff terpilih = staffList[pilihan - 1];

    // Buat box
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

    // Konfirmasi nonaktifkan
    gotoxy(38, 35); printf("Yakin ingin menonaktifkan data ini? (y/n): ");

    while (1) {
        char ch = _getch();

        if ( ch == 27) return;;

        if (ch == 'y' || ch == 'Y') {
            konfirmasi = 'y';
            printf("Y");
            break;
        }else if (ch == 'n' || ch == 'N') {
            konfirmasi = 'n';
            printf("N");
            break;
            getchar();
            getchar() ;
        }
    }

    if (tolower(konfirmasi) != 'y') {
        gotoxy(38, 36); printf("Pembatalan proses!");
        getchar();
        getchar();
        return;
    }

    // Proses mengubah status menjadi Nonaktif
    for (int i = 0; i < count; i++) {
        if (strcmp(staffList[i].id, terpilih.id) == 0) {
            strcpy(staffList[i].status, "Nonaktif");
            found = 1;
            break;
        }
    }

    if (found) {
        // Tulis ulang semua data ke file
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
}

#endif