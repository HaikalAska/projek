#ifndef PROJEK_DELETE_PENUMPANG_H
#define PROJEK_DELETE_PENUMPANG_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../FrameTabel.h"
#include "createpenumpang.h"

void deletePenumpang() {
    FILE *fp, *temp;
    penumpang data;
    penumpang list[1000];
    int count = 0;
    int pilihan;
    char konfirmasi;
    int found = 0;

    // ===== BUKA FILE =====
    fp = fopen("penumpang.dat", "rb");
    if (!fp) {
        gotoxy(37, 25);
        printf("File penumpang.dat tidak ditemukan!");
        getch();
        return;
    }

    // ===== BACA SEMUA DATA =====
    while (fread(&data, sizeof(penumpang), 1, fp)) {
        list[count++] = data;
    }
    fclose(fp);

    if (count == 0) {
        gotoxy(37, 25);
        printf("Tidak ada data penumpang!");
        getch();
        return;
    }

    // ===== PILIH NOMOR =====
    gotoxy(3, 25);
    printf("Pilih No Urut: ");
    scanf("%d", &pilihan);

    if (pilihan < 1 || pilihan > count) {
        gotoxy(37, 27);
        printf("Pilihan tidak valid!");
        getch();
        getch();
        return;
    }

    penumpang terpilih = list[pilihan - 1];

    // ===== BOX DETAIL =====
    bentukframe(37, 28, 70, 10);
    gotoxy(65, 28); printf("=== DATA PENUMPANG ===");
    gotoxy(38, 29); printf("ID Penumpang : %s", terpilih.id);
    gotoxy(38, 30); printf("Nama         : %s", terpilih.nama);
    gotoxy(38, 31); printf("No HP        : %s", terpilih.no_hp);
    gotoxy(38, 32); printf("rute         : %s", terpilih.rute);
    gotoxy(38, 33); printf("Email        : %s", terpilih.email);

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
    fp = fopen("penumpang.dat", "rb");
    temp = fopen("temp_penumpang.dat", "wb");

    while (fread(&data, sizeof(penumpang), 1, fp)) {
        if (strcmp(data.id, terpilih.id) != 0) {
            fwrite(&data, sizeof(penumpang), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("penumpang.dat");
        rename("temp_penumpang.dat", "penumpang.dat");
        gotoxy(38, 35);
        printf("Data '%s' berhasil dihapus!", terpilih.nama);
    } else {
        remove("temp_penumpang.dat");
        gotoxy(38, 35);
        printf("Gagal menghapus data!");
    }

    getch();
    getch();
}

#endif
