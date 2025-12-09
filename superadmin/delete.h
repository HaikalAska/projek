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

    clearscreen();
    system("chcp 65001 > nul");
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);
    gotoxy(8,5); printf("Kelompok 5");

    gotoxy(50, 14); printf("Pilih No Urut: %d", pilihan);

    // Buat box
    printBorder(49, 15, 45, 8);
    gotoxy(50, 16);  printf("===================DATA====================");
    gotoxy(50, 17);  printf("Nama        : %s", terpilih.username);
    gotoxy(50, 18); printf("Password    : %s", terpilih.password);
    gotoxy(50, 19); printf("Tgl Lahir   : %s", terpilih.tgl);
    gotoxy(50, 20); printf("No Telpon   : %s", terpilih.notlpn);
    gotoxy(50, 21); printf("Gender      : %s", terpilih.gender);

    // Konfirmasi penghapusan
    gotoxy(50, 23); printf("Yakin ingin menghapus data ini? (y/n): ");
    scanf(" %c", &konfirmasi);

    if (tolower(konfirmasi) != 'y') {
        gotoxy(50, 24); printf("Penghapusan dibatalkan!");
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
        gotoxy(50, 24); printf("Data '%s' berhasil dihapus!", terpilih.username);
    } else {
        remove("sampah.dat");
        gotoxy(50, 24); printf("Terjadi kesalahan saat menghapus!");
    }

    getchar();
    getchar();
}

#endif