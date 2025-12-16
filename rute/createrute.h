//
// Created by ASUS on 12/14/2025.
//

#ifndef PROJEK_CREATERUTE_H
#define PROJEK_CREATERUTE_H

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "../FrameTabel.h"

typedef struct {
    char id[20];
    char kotaAsal[50];
    char kotaTujuan[50];
    float harga;
    char jamBerangkat[10];
    char jamTiba[10];
} Rute;

// ================= HITUNG DATA =================
int getRuteCount() {
    FILE *fp = fopen("rute.dat", "rb");
    if (!fp) return 0;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);

    return size / sizeof(Rute);
}

// ================= INPUT JAM =================
void inputJam(char *out) {
    char jam[3] = "", menit[3] = "";
    int i = 0;
    char ch;

    // ===== INPUT JAM (HH) =====
    while (i < 2) {
        ch = _getch();

        if (ch == 27) { out[0] = '\0'; return; }

        // digit pertama jam: 0 - 2
        if (i == 0 && ch >= '0' && ch <= '2') {
            jam[i++] = ch;
            printf("%c", ch);
        }
        // digit kedua jam: 0 - 9
        else if (i == 1 && ch >= '0' && ch <= '9') {
            jam[i++] = ch;
            printf("%c", ch);
        }
    }

    jam[2] = '\0';
    printf(":");
    i = 0;

    // ===== INPUT MENIT (MM) =====
    while (i < 2) {
        ch = _getch();

        if (ch == 27) { out[0] = '\0'; return; }

        // digit pertama menit: 0 - 5
        if (i == 0 && ch >= '0' && ch <= '5') {
            menit[i++] = ch;
            printf("%c", ch);
        }
        // digit kedua menit: 1 - 9
        else if (i == 1 && ch >= '1' && ch <= '9') {
            menit[i++] = ch;
            printf("%c", ch);
        }
    }

    menit[2] = '\0';

    sprintf(out, "%s:%s", jam, menit);
}


// ================= INPUT HARGA =================
int inputHarga(int x, int y) {
    char buf[5] = "";   // max 4 digit + '\0'
    int i = 0;

    gotoxy(x, y);
    printf("Rp");

    while (1) {
        char ch = _getch();

        // ESC batal
        if (ch == 27) return 0;

        // ENTER
        if (ch == 13 && i > 0) {
            int nilai = atoi(buf);

            // pindah kursor ke akhir input
            printf("Rp");

            if (i <= 3) {
                // contoh: 120 -> Rp120.000,00
                gotoxy(54,31); printf("%d.000,00", nilai);
                return nilai * 1000;
            } else {
                // contoh: 1200 -> Rp1.200.000,00
                gotoxy(54,31); printf("%d.%03d.000,00", nilai / 1000, nilai % 1000);
                return nilai * 1000;
            }
        }

        // BACKSPACE
        if (ch == 8 && i > 0) {
            i--;
            buf[i] = '\0';
            printf("\b \b");
        }

        // ANGKA (maks 4 digit)
        if (ch >= '0' && ch <= '9' && i < 4) {
            buf[i++] = ch;
            printf("%c", ch);
        }
    }
}


int rutenavigasi(int x, int y, int jumlah, int spasi) {
    int pilih = 0;
    int ch;

    while (1) {
        for (int i = 0; i < jumlah; i++) {
            gotoxy(x, y + i * spasi);
            if (i == pilih)
                printf(">>");
            else
                printf("  ");
        }

        ch = _getch();
        if (ch == 13) return pilih;

        if (ch == 224) {
            ch = _getch();
            if (ch == 72) {
                pilih--;
                if (pilih < 0) pilih = jumlah - 1;
            }
            else if (ch == 80) {
                pilih++;
                if (pilih >= jumlah) pilih = 0;
            }
        }
    }
}


void pilihKota(char *output) {
    int x = 80, y = 29;
    int pilih;

pilihProvinsi:
    clearArea(77, y, 25, 12);

    gotoxy(x, y);  printf("PILIH PROVINSI");
    gotoxy(x, 31); printf("Banten");
    gotoxy(x, 32); printf("DKI Jakarta");
    gotoxy(x, 33); printf("Jawa Barat");
    gotoxy(x, 34); printf("Jawa Tengah");
    gotoxy(x, 35); printf("Yogyakarta");
    gotoxy(x, 36); printf("Jawa Timur");

    pilih = rutenavigasi(77, 31, 6, 1);

    // ================= BANTEN =================
    if (pilih == 0) {
        clearArea(77, y, 25, 12);

        gotoxy(x, y);  printf("BANTEN");
        gotoxy(x, 31); printf("Serang");
        gotoxy(x, 32); printf("Tangerang");

        pilih = rutenavigasi(77, 31, 2, 1);

        if      (pilih == 0) strcpy(output, "Serang");
        else if (pilih == 1) strcpy(output, "Tangerang");
        else goto pilihProvinsi;

        clearArea(77, y, 25, 12);
        return;
    }

    // ================= DKI =================
    else if (pilih == 1) {
        strcpy(output, "Jakarta");
        clearArea(77, y, 25, 12);
        return;
    }

    // ================= JAWA BARAT =================
    else if (pilih == 2) {
        clearArea(77, y, 25, 12);

        gotoxy(x, y);  printf("JAWA BARAT");
        gotoxy(x, 31); printf("Bandung");
        gotoxy(x, 32); printf("Bekasi");
        gotoxy(x, 33); printf("Bogor");
        gotoxy(x, 34); printf("Cirebon");
        gotoxy(x, 35); printf("Tasikmalaya");

        pilih = rutenavigasi(77, 31, 5, 1);

        if      (pilih == 0) strcpy(output, "Bandung");
        else if (pilih == 1) strcpy(output, "Bekasi");
        else if (pilih == 2) strcpy(output, "Bogor");
        else if (pilih == 3) strcpy(output, "Cirebon");
        else if (pilih == 4) strcpy(output, "Tasikmalaya");
        else goto pilihProvinsi;

        clearArea(77, y, 25, 12);
        return;
    }

    // ================= JAWA TENGAH =================
    else if (pilih == 3) {
        clearArea(77, y, 25, 12);

        gotoxy(x, y);  printf("JAWA TENGAH");
        gotoxy(x, 31); printf("Semarang");
        gotoxy(x, 32); printf("Magelang");
        gotoxy(x, 33); printf("Pekalongan");
        gotoxy(x, 34); printf("Tegal");

        pilih = rutenavigasi(77, 31, 4, 1);

        if      (pilih == 0) strcpy(output, "Semarang");
        else if (pilih == 1) strcpy(output, "Magelang");
        else if (pilih == 2) strcpy(output, "Pekalongan");
        else if (pilih == 3) strcpy(output, "Tegal");
        else goto pilihProvinsi;

        clearArea(77, y, 25, 12);
        return;
    }

    // ================= YOGYAKARTA =================
    else if (pilih == 4) {
        strcpy(output, "Yogyakarta");
        clearArea(77, y, 25, 12);
        return;
    }

    // ================= JAWA TIMUR =================
    else if (pilih == 5) {
        clearArea(77, y, 25, 12);

        gotoxy(x, y);  printf("JAWA TIMUR");
        gotoxy(x, 31); printf("Surabaya");
        gotoxy(x, 32); printf("Malang");
        gotoxy(x, 33); printf("Kediri");
        gotoxy(x, 34); printf("Mojokerto");
        gotoxy(x, 35); printf("Madiun");
        gotoxy(x, 36); printf("Probolinggo");

        pilih = rutenavigasi(77, 31, 6, 1);

        if      (pilih == 0) strcpy(output, "Surabaya");
        else if (pilih == 1) strcpy(output, "Malang");
        else if (pilih == 2) strcpy(output, "Kediri");
        else if (pilih == 3) strcpy(output, "Mojokerto");
        else if (pilih == 4) strcpy(output, "Madiun");
        else if (pilih == 5) strcpy(output, "Probolinggo");
        else goto pilihProvinsi;

        clearArea(77, y, 25, 12);
        return;
    }
}



// ================= CREATE RUTE =================
void buatrute() {
    char n;

    do {
        bentukframe(35, 27, 108, 16);
        gotoxy(80, 27); printf("=== BUAT RUTE ===");

        FILE *fp = fopen("rute.dat", "ab");
        if (!fp) return;

        Rute r;

        int count = getRuteCount() + 1;
        sprintf(r.id, "RT%03d", count);
        gotoxy(37, 28); printf("ID Rute      : %s", r.id);

        gotoxy(37, 29); printf("Kota Asal    : ");
        pilihKota(r.kotaAsal);
        gotoxy(52, 29); printf("%s", r.kotaAsal);

        gotoxy(37, 30); printf("Kota Tujuan  : ");
        pilihKota(r.kotaTujuan);
        gotoxy(52, 30); printf("%s", r.kotaTujuan);

        gotoxy(37, 31); printf("Harga        : ");
        r.harga = inputHarga(52, 31);
        if (r.harga == 0) { fclose(fp); return; }

        gotoxy(37, 32); printf("Jam Berangkat: ");
        inputJam(r.jamBerangkat);
        if (strlen(r.jamBerangkat) == 0) { fclose(fp); return; }

        gotoxy(37, 33); printf("Jam Tiba     : ");
        inputJam(r.jamTiba);
        if (strlen(r.jamTiba) == 0) { fclose(fp); return; }

        fwrite(&r, sizeof(Rute), 1, fp);
        fclose(fp);

        gotoxy(37, 35); printf("Data rute berhasil ditambahkan!");
        gotoxy(37, 36); printf("Tambah lagi? (y/n): ");

        while (1) {
            n = _getch();
            if (n == 27) return;
            if (n == 'y' || n == 'Y' || n == 'n' || n == 'N') {
                if (n == 'n' || n == 'N') return;
                break;
            }
        }

    } while (n == 'y' || n == 'Y');
}

// ================= DUMMY 50 DATA RUTE =================
void buatDummyRute() {
    FILE *fp = fopen("rute.dat", "wb");
    if (!fp) return;

    Rute r;

    char *kota[] = {
        "Jakarta","Bekasi","Depok","Bogor","Bandung",
        "Cirebon","Semarang","Solo","Yogyakarta","Surabaya",
        "Malang","Kediri","Madiun","Purwokerto","Tegal"
    };

    int totalKota = 15;

    for (int i = 0; i < 50; i++) {
        sprintf(r.id, "RT%03d", i + 1);

        strcpy(r.kotaAsal, kota[i % totalKota]);
        strcpy(r.kotaTujuan, kota[(i + 4) % totalKota]);

        r.harga = 50000 + (i * 3000);

        int jam = 6 + (i % 12);
        int menit = (i * 5) % 60;

        sprintf(r.jamBerangkat, "%02d:%02d", jam, menit);
        sprintf(r.jamTiba, "%02d:%02d", (jam + 3) % 24, menit);

        fwrite(&r, sizeof(Rute), 1, fp);
    }

    fclose(fp);

    gotoxy(40, 40);
    printf("✓ 50 data dummy rute berhasil dibuat");
    getch();
}

#endif // PROJEK_CREATERUTE_H
