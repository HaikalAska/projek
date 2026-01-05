//
// Created by yoyop on 14/12/2025.
//

#ifndef PROJEK_DELETEKENDARAAN_H
#define PROJEK_DELETEKENDARAAN_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#include "../FrameTabel.h"
#include "createKendaraan.h"

void deleteKendaraan() {
    FILE *fp, *temp;
    Kendaraan data;
    Kendaraan kendaraanList[100];
    int count = 0;
    int pilihan;
    char konfirmasi;
    int found = 0;

    // ===== BACA DATA =====
    fp = fopen("kendaraan.dat", "rb");
    if (fp == NULL) {
        gotoxy(3, 13);
        printf("File kendaraan.dat tidak ditemukan!");
        getch();
        return;
    }

    while (fread(&data, sizeof(Kendaraan), 1, fp) == 1) {
        kendaraanList[count++] = data;
    }
    fclose(fp);

    if (count == 0) {
        gotoxy(3, 13);
        printf("Tidak ada data kendaraan! ");
        getch();
        return;
    }

    // ===== INPUT PILIHAN =====
    gotoxy(3, 25);
    printf("Pilih No Urut Kendaraan: ");
    scanf("%d", &pilihan);

    if (pilihan < 1 || pilihan > count) {
        gotoxy(3, 26);
        printf("Pilihan tidak valid!");
        getch();
        getch();
        return;
    }

    Kendaraan terpilih = kendaraanList[pilihan - 1];

    // ===== BOX DETAIL =====
    bentukframe(37, 27, 55, 10);
    gotoxy(55, 27); printf("=== DATA KENDARAAN ===");

    gotoxy(38, 28); printf("ID Kendaraan : %s", terpilih.id_kendaraan);
    gotoxy(38, 29); printf("Kategori     : %s", terpilih.kategori);
    gotoxy(38, 30); printf("Kapasitas    : %s", terpilih.kapasitas);
    gotoxy(38, 31); printf("Fasilitas    : %s", terpilih.fasilitas);
    gotoxy(38, 32); printf("Nama Armada  : %s", terpilih.nama_armada);

    // ===== KONFIRMASI =====
    gotoxy(38, 34);
    printf("Yakin ingin menghapus data ini? (y/n): ");
    scanf(" %c", &konfirmasi);

    if (tolower(konfirmasi) != 'y') {
        gotoxy(38, 35);
        printf("Penghapusan dibatalkan!");
        getch();
        getch();
        return;
    }

    // ===== PROSES HAPUS =====
    fp = fopen("kendaraan.dat", "rb");
    temp = fopen("temp.dat", "wb");

    while (fread(&data, sizeof(Kendaraan), 1, fp) == 1) {
        if (strcmp(data.id_kendaraan, terpilih.id_kendaraan) != 0) {
            fwrite(&data, sizeof(Kendaraan), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("kendaraan.dat");
        rename("temp.dat", "kendaraan.dat");
        gotoxy(38, 35);
        printf("Data kendaraan berhasil dihapus!");
    } else {
        remove("temp.dat");
        gotoxy(38, 35);
        printf("Terjadi kesalahan saat menghapus!");
    }

    getch();
    getch();
}

#endif

