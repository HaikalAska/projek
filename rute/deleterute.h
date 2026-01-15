//
// Created by ASUS on 12/14/2025.
//

#ifndef PROJEK_DELETERUTE_H
#define PROJEK_DELETERUTE_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "../FrameTabel.h"
#include "createrute.h"


//
// Created by ASUS on 12/14/2025.
//


// ==================================================
// FORMAT HARGA RUPIAH
// ==================================================
void formatHargass(int harga, char *out) {
    int juta = harga / 1000000;
    int ribu = (harga / 1000) % 1000;
    int sisa = harga % 1000;

    if (juta > 0) {
        sprintf(out, "Rp%d.%03d.%03d,00", juta, ribu, sisa);
    } else if (ribu > 0) {
        sprintf(out, "Rp%d.%03d,00", ribu, sisa);
    } else {
        sprintf(out, "Rp%d,00", sisa);
    }
}

// ==================================================
// DELETE RUTE
// ==================================================
void deleterute() {
    FILE *fp, *temp;
    Rute data;
    Rute list[1000];
    int count = 0;
    int pilihan;
    char konfirmasi;
    int found = 0;

    // ===== BUKA FILE =====
    fp = fopen("rute.dat", "rb");
    if (!fp) {
        gotoxy(3, 27); printf("File rute.dat tidak ditemukan!");
        getch();
        return;
    }

    // ===== BACA DATA =====
    while (fread(&data, sizeof(Rute), 1, fp) == 1) {
        list[count++] = data;
    }
    fclose(fp);

    if (count == 0) {
        gotoxy(3, 27); printf("Tidak ada data rute!");
        getch();
        return;
    }

    // ===== INPUT NOMOR =====
    gotoxy(3, 25);
    printf("Pilih No Urut Rute: ");
    gotoxy(23, 25);
    scanf("%d", &pilihan);

    if (pilihan < 1 || pilihan > count) {
        gotoxy(3, 27); printf("Nomor tidak valid!");
        getch(); getch();
        return;
    }

    Rute terpilih = list[pilihan - 1];

    // ===== DETAIL RUTE =====
    char hargaStr[25];
    formatHargass((int)terpilih.harga, hargaStr);

    bentukframe(37, 27, 108, 12);
    gotoxy(75, 27); printf("=== DETAIL RUTE ===");

    gotoxy(39, 28); printf("ID            : %s", terpilih.id);
    gotoxy(39, 29); printf("Kota Asal     : %s", terpilih.kotaAsal);
    gotoxy(39, 30); printf("Kota Tujuan   : %s", terpilih.kotaTujuan);
    gotoxy(39, 31); printf("Harga         : %s", hargaStr);
    gotoxy(39, 32); printf("Jam Berangkat : %s", terpilih.jamBerangkat);
    gotoxy(39, 33); printf("Jam Tiba      : %s", terpilih.jamTiba);

    // ===== KONFIRMASI =====
    gotoxy(39, 35);
    printf("Yakin ingin menghapus rute ini? (y/n): ");
    scanf(" %c", &konfirmasi);

    if (tolower(konfirmasi) != 'y') {
        gotoxy(39, 36); printf("Penghapusan dibatalkan!");
        getch(); getch();
        return;
    }

    // ===== PROSES HAPUS =====
    fp   = fopen("rute.dat", "rb");
    temp = fopen("temp.dat", "wb");

    while (fread(&data, sizeof(Rute), 1, fp) == 1) {
        if (strcmp(data.id, terpilih.id) != 0) {
            fwrite(&data, sizeof(Rute), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("rute.dat");
        rename("temp.dat", "rute.dat");
        gotoxy(39, 36); printf("Rute %s berhasil dihapus!", terpilih.id);
    } else {
        remove("temp.dat");
        gotoxy(39, 36); printf("Gagal menghapus data!");
    }

    getch();
    getch();
}

#endif // PROJEK_DELETERUTE_H


