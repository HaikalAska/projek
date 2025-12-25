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

    // Input pilihan nomor
    gotoxy(3, 25);
    printf("Pilih No Urut: ");
    scanf("%d", &pilihan);

    // Validasi pilihan
    if (pilihan < 1 || pilihan > count) {
        gotoxy(3, 14); printf("Pilihan tidak valid!");
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
    scanf(" %c", &konfirmasi);

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