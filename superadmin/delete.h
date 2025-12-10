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
    gotoxy(3, 13);
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


    gotoxy(62, 29); printf("Pilih No Urut: %d", pilihan);

    // Buat box
    printBorder(60, 30, 35, 10);
    gotoxy(62, 31);  printf("==============DATA==============");
    gotoxy(62, 32);  printf("Nama        : %s", terpilih.username);
    gotoxy(62, 33); printf("Password    : %s", terpilih.password);
    gotoxy(62, 34); printf("Tgl Lahir   : %s", terpilih.tgl);
    gotoxy(62, 35); printf("No Telpon   : %s", terpilih.notlpn);
    gotoxy(62, 36); printf("Gender      : %s", terpilih.gender);

    // Konfirmasi penghapusan
    gotoxy(60, 40); printf("Yakin ingin menghapus data ini? (y/n): ");
    scanf(" %c", &konfirmasi);

    if (tolower(konfirmasi) != 'y') {
        gotoxy(62, 40); printf("Penghapusan dibatalkan!");
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
        gotoxy(62, 41); printf("Data '%s' berhasil dihapus!", terpilih.username);
    } else {
        remove("sampah.dat");
        gotoxy(62, 40); printf("Terjadi kesalahan saat menghapus!");
    }

    getchar();
    getchar();
}

#endif