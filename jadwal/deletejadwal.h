//
// Created by ASUS on 12/16/2025.
//

#ifndef PROJEK_DELETEJADWAL_H
#define PROJEK_DELETEJADWAL_H

#ifndef PROJEK_DELETE_JADWAL_H
#define PROJEK_DELETE_JADWAL_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#include "../FrameTabel.h"
#include "createJadwal.h"

void deleteJadwal() {

    FILE *fp, *temp;
    jadwal list[200];
    jadwal data;
    int count = 0;
    int pilihan;
    char konfirmasi;
    int found = 0;

    // Buka file jadwal
    fp = fopen("jadwal.dat", "rb");
    if (fp == NULL) {
        gotoxy(3, 13);
        printf("File jadwal.dat tidak ditemukan!");
        getch();
        return;
    }

    // Baca semua data
    while (fread(&data, sizeof(jadwal), 1, fp) == 1) {
        list[count++] = data;
    }
    fclose(fp);

    if (count == 0) {
        gotoxy(3, 13);
        printf("Tidak ada data jadwal!");
        getch();
        return;
    }

    // Input nomor urut
    gotoxy(3, 25);
    printf("Pilih No Urut Jadwal : ");
    scanf("%d", &pilihan);

    if (pilihan < 1 || pilihan > count) {
        gotoxy(3, 26);
        printf("Pilihan tidak valid!");
        getch();
        return;
    }

    jadwal pilih = list[pilihan - 1];

    // ===== BOX DETAIL JADWAL =====
    bentukframe(35, 27, 60, 14);
    gotoxy(55, 27); printf("=== DETAIL JADWAL ===");

    gotoxy(37, 28); printf("ID Jadwal    : %s", pilih.id);
    gotoxy(37, 29); printf("Tanggal      : %s", pilih.tanggal);
    gotoxy(37, 30); printf("Kota Awal    : %s", pilih.kotaAsal);
    gotoxy(37, 31); printf("Kota Akhir   : %s", pilih.kotaTujuan);
    gotoxy(37, 32); printf("Jam          : %s", pilih.jamBerangkat);
    gotoxy(37, 33); printf("Kategori     : %s", pilih.kategori);
    gotoxy(37, 34); printf("Armada       : %s", pilih.armada);

    char hargaStr[25];
    formatHarga(pilih.harga, hargaStr);
    gotoxy(37, 35); printf("Harga        : %s", hargaStr);

    // Konfirmasi
    gotoxy(37, 36);
    printf("Yakin ingin menghapus jadwal ini? (y/n): ");
    scanf(" %c", &konfirmasi);

    if (tolower(konfirmasi) != 'y') {
        gotoxy(37, 37);
        printf("Penghapusan dibatalkan!");
        getch();
        return;
    }

    // Proses hapus
    fp = fopen("jadwal.dat", "rb");
    temp = fopen("temp.dat", "wb");

    while (fread(&data, sizeof(jadwal), 1, fp) == 1) {
        if (strcmp(data.id, pilih.id) != 0) {
            fwrite(&data, sizeof(jadwal), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("jadwal.dat");
        rename("temp.dat", "jadwal.dat");
        gotoxy(37, 38);
        printf("Jadwal berhasil dihapus!");
    } else {
        remove("temp.dat");
        gotoxy(37, 38);
        printf("Gagal menghapus jadwal!");
    }

    getch();
}

#endif


#endif //PROJEK_DELETEJADWAL_H