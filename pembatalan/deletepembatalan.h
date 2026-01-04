//
// Created by Asus on 16/12/2025.
//
#ifndef PROJEK_DELETEPEMBATALAN_H
#define PROJEK_DELETEPEMBATALAN_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../FrameTabel.h"
#include "createpembatalan.h"

void deletepembatalan() {
    FILE *fp, *temp;
    pembatalan data;
    pembatalan list[1000];
    int count = 0;
    int pilihan;
    char konfirmasi;
    int found = 0;

    // ===== BUKA FILE =====
    fp = fopen("pembatalan.dat", "rb");
    if (!fp) {
        gotoxy(37, 25);
        printf("File pembatalan.dat tidak ditemukan!");
        getch();
        return;
    }

    // ===== BACA SEMUA DATA =====
    while (fread(&data, sizeof(pembatalan), 1, fp)) {
        list[count++] = data;
    }
    fclose(fp);

    if (count == 0) {
        gotoxy(37, 25);
        printf("Tidak ada data pembatalan!");
        getch();
        return;
    }

    // ===== INPUT NOMOR URUT =====
    gotoxy(3, 25);
    printf("Pilih No Urut: ");
    scanf("%d", &pilihan);
    fflush(stdin);

    if (pilihan < 1 || pilihan > count) {
        gotoxy(37, 27);
        printf("Pilihan tidak valid!");
        getch();
        return;
    }

    pembatalan terpilih = list[pilihan - 1];

    // ===== BOX DETAIL =====
    bentukframe(37, 28, 70, 8);
    gotoxy(62, 28); printf("=== DATA PEMBATALAN ===");
    gotoxy(38, 29); printf("ID Pembatalan : %s", terpilih.id_pembatalan);
    gotoxy(38, 30); printf("ID Pemesanan  : %s", terpilih.id_pemesanan);
    gotoxy(38, 31); printf("Pengembalian  : Rp %.2f", terpilih.pengembalian);

    // ===== KONFIRMASI =====
    gotoxy(38, 32);
    printf("Yakin ingin menghapus data ini? (y/n): ");
    scanf(" %c", &konfirmasi);

    if (tolower(konfirmasi) != 'y') {
        gotoxy(38, 33);
        printf("Penghapusan dibatalkan!");
        getch();
        return;
    }

    // ===== PROSES HAPUS =====
    fp = fopen("pembatalan.dat", "rb");
    temp = fopen("temp_pembatalan.dat", "wb");

    while (fread(&data, sizeof(pembatalan), 1, fp)) {
        if (strcmp(data.id_pembatalan, terpilih.id_pembatalan) != 0) {
            fwrite(&data, sizeof(pembatalan), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("pembatalan.dat");
        rename("temp_pembatalan.dat", "pembatalan.dat");
        gotoxy(38, 33);
        printf("Data pembatalan berhasil dihapus!");
    } else {
        remove("temp_pembatalan.dat");
        gotoxy(38, 33);
        printf("Gagal menghapus data!");
    }

    getch();
}

#endif // PROJEK_DELETEPEMBATALAN_H
