//
// Created by ASUS on 12/16/2025.
//

#ifndef PROJEK_CREATEJADWAL_H
#define PROJEK_CREATEJADWAL_H

typedef struct {
    char id[10];
    char kotaAsal[30];
    char kotaTujuan[30];
    char armada[30];
    char tanggal[15];
    char jamBerangkat[10];
    float harga;
    char kategori[20];
} jadwal;


#include <conio.h>
#include "../Kendaraan/createKendaraan.h"

int loadKendaraan(Kendaraan k[]) {
    FILE *fp = fopen("kendaraan.dat", "rb");
    int total = 0;

    if (!fp) return 0;

    while (fread(&k[total], sizeof(Kendaraan), 1, fp) == 1) {
        total++;
        if (total >= 1000) break;
    }

    fclose(fp);
    return total;
}

int pilihArmadaDanKategori(char *armadaOut, char *kategoriOut) {
    Kendaraan all_kendaraan[1000];
    int totals, pilih;
    int y = 30;

    totals = loadKendaraan(all_kendaraan);
    if (totals == 0) return 0;

    gotoxy(37, 34);
    printf("Pilih kendaraan  : ");
    scanf("%d", &pilih);

    if (pilih < 1 || pilih > totals) return 0;

    // tampilkan hasil pilihan
    gotoxy(37, 34);
    printf("Armada        : %s", all_kendaraan[pilih - 1].nama_armada);
    gotoxy(37, 35);
    printf("Kategori      : %s", all_kendaraan[pilih - 1].kategori);

    strcpy(armadaOut, all_kendaraan[pilih - 1].nama_armada);
    strcpy(kategoriOut, all_kendaraan[pilih - 1].kategori);

    return 1;
}


void inputKategori(char kategori[], int x, int y) {
    char ch;
    int filled = 0;

    while (1) {
        ch = _getch();

        // ===== ENTER (konfirmasi) =====
        if (ch == 13) {
            if (filled) break; // hanya boleh enter kalau sudah ada pilihan
            continue;
        }

        // ===== BACKSPACE =====
        if (ch == 8) {
            if (filled) {
                gotoxy(x, y);
                printf("          "); // hapus teks
                gotoxy(x, y);
                filled = 0;
            }
            continue;
        }

        // ===== INPUT VALID =====
        if (!filled) {
            if (ch == 'b' || ch == 'B') {
                strcpy(kategori, "Business");
                gotoxy(x, y); printf("Business");
                filled = 1;
            }
            else if (ch == 'e' || ch == 'E') {
                strcpy(kategori, "Ekonomi");
                gotoxy(x, y); printf("Ekonomi");
                filled = 1;
            }
            else if (ch == 'x' || ch == 'X') {
                strcpy(kategori, "Executive");
                gotoxy(x, y); printf("Executive");
                filled = 1;
            }
        }
        // input lain DIABAIKAN TOTAL
    }
}


int loadRute(Rute r[]) {
    FILE *fp = fopen("rute.dat", "rb");
    int total = 0;

    if (!fp) return 0;

    while (fread(&r[total], sizeof(Rute), 1, fp) == 1) {
        total++;
        if (total >= 1000) break;
    }

    fclose(fp);
    return total;
}


int pilihRuteDanTampil(Rute *hasil) {
    Rute all_rute[1000];
    int total, pilih;

    total = loadRute(all_rute);
    if (total == 0) return 0;

    // tampilkan tabel rute
    // bacaRute();

    // bentukframe(35, 48, 108, 6);
    gotoxy(37, 30); printf("Pilih rute    : ", total);
    scanf("%d", &pilih);

    if (pilih < 1 || pilih > total) return 0;

    *hasil = all_rute[pilih - 1];
    return 1;
}


void inputTanggals(char tanggal[], int x, int y) {
    char ch;
    int pos = 0;

    while (pos < 10) {
        ch = _getch();

        // ===== BACKSPACE =====
        if (ch == 8) {
            if (pos > 0) {
                pos--;
                gotoxy(x + pos, y);
                printf(" ");
                gotoxy(x + pos, y);
            }
            continue;
        }

        // ===== DIGIT 1 (0–3) =====
        if (pos == 0 && ch >= '0' && ch <= '3') {
            gotoxy(x + pos, y);
            tanggal[pos++] = ch;
            printf("%c", ch);
        }

        // ===== DIGIT 2 =====
        else if (pos == 1) {
            if ((tanggal[0] == '3' && ch <= '2') ||
                (tanggal[0] != '3' && ch <= '9')) {
                gotoxy(x + pos, y);
                tanggal[pos++] = ch;
                printf("%c", ch);
                }
        }

        // ===== AUTO "/" =====
        else if (pos == 2) {
            gotoxy(x + pos, y);
            tanggal[pos++] = '/';
            printf("/");
        }

        // ===== DIGIT 3 =====
        else if (pos == 3 && (ch == '0' || ch == '1')) {
            gotoxy(x + pos, y);
            tanggal[pos++] = ch;
            printf("%c", ch);
        }

        // ===== DIGIT 4 =====
        else if (pos == 4) {
            if ((tanggal[3] == '1' && ch <= '2') ||
                (tanggal[3] == '0' && ch >= '1' && ch <= '9')) {
                gotoxy(x + pos, y);
                tanggal[pos++] = ch;
                printf("%c", ch);
                }
        }

        // ===== AUTO "/2025" =====
        else if (pos == 5) {
            gotoxy(x + pos, y);
            printf("/2025");
            strcpy(&tanggal[5], "/2025");
            pos = 10;
        }
    }

    tanggal[10] = '\0';
}

int getJadwalCount() {
    FILE *fp = fopen("jadwal.dat", "rb");
    int count = 0;
    jadwal j;

    if (!fp) return 0;

    while (fread(&j, sizeof(jadwal), 1, fp)) {
        count++;
    }

    fclose(fp);
    return count;
}


void buatjadwal() {
    char n;

    do {
        bentukframe(35, 27, 108, 18);
        gotoxy(80, 27); printf("=== BUAT JADWAL ===");

        FILE *fp = fopen("jadwal.dat", "ab");
        if (fp == NULL) {
            return;
        }

        jadwal j;

        int count = getJadwalCount() + 1;
        sprintf(j.id, "JD%03d", count);
        gotoxy(37, 28); printf("ID Jadwal     : %s", j.id);

        gotoxy(37, 29); printf("Tanggal       : ");
        gotoxy(53, 29);
        inputTanggals(j.tanggal, 53, 29);


        Rute r;

        // gotoxy(37, 30); printf("Pilih rute        : ");
        // gotoxy(52, 30); printf("");
        _getch();

        if (!pilihRuteDanTampil(&r)) return;

        // tampilkan detail rute
        char hargaStr[25];
        formatHarga((int)r.harga, hargaStr);

        gotoxy(37, 30); printf("Kota Awal     : %-20s", r.kotaAsal);
        gotoxy(37, 31); printf("Kota Akhir    : %-20s", r.kotaTujuan);
        gotoxy(37, 32); printf("Jam Berangkat : %-10s", r.jamBerangkat);
        gotoxy(37, 33); printf("Harga         : %-15s", hargaStr);

        // simpan ke jadwal
        strcpy(j.kotaAsal, r.kotaAsal);
        strcpy(j.kotaTujuan, r.kotaTujuan);
        strcpy(j.jamBerangkat, r.jamBerangkat);
        j.harga = r.harga;

        gotoxy(37, 34); printf("Pilih Kendaraan  : ");
        Kendaraan k;
        if (!pilihArmadaDanKategori(j.armada, j.kategori)) return;


        // strcpy(j.armada, k.nama_armada);
        // strcpy(j.kategori, k.kategori);



        // gotoxy(37, 36); printf("Kategori      : ");
        // // gotoxy(37, 50); printf("[B]usiness [E]konomi [x]ecutive");
        // gotoxy(53, 36);
        // inputKategori(j.kategori, 53, 35);

        fwrite(&j, sizeof(jadwal), 1, fp);
        fclose(fp);

        gotoxy(37, 36); printf("Data jadwal berhasil ditambahkan!");
        gotoxy(37, 37); printf("Tambah lagi? (y/n): ");

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




#endif //PROJEK_CREATEJADWAL_H