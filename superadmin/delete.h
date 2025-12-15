#ifndef PROJEK_DELETE_H
#define PROJEK_DELETE_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "create.h"

void delete(){
    FILE *fp, *sampah;
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
    bentukframe(37, 27, 45, 11);
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

    // Konfirmasi penghapusan
    gotoxy(38, 35); printf("Yakin ingin menghapus data ini? (y/n): ");
    scanf(" %c", &konfirmasi);

    if (tolower(konfirmasi) != 'y') {
        gotoxy(38, 36); printf("Penghapusan dibatalkan!");
        getchar();
        getchar();
        return;
    }

    // Proses penghapusan
    fp = fopen("staff.dat","rb");
    sampah = fopen("sampah.dat","wb");

    while (fread(&data, sizeof(staff), 1, fp) == 1) {
        if (strcmp(data.id, terpilih.id) != 0) {
            fwrite(&data, sizeof(staff), 1, sampah);
        } else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(sampah);

    if (found) {
        remove("staff.dat");
        rename("sampah.dat", "staff.dat");
        gotoxy(38, 36); printf("Data '%s' berhasil dihapus!", terpilih.username);
    } else {
        remove("sampah.dat");
        gotoxy(62, 40); printf("Terjadi kesalahan saat menghapus!");
    }

    getchar();
    getchar();
}

#endif