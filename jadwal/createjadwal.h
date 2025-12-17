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
#include <stdio.h>


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
    gotoxy(37, 30); printf("Pilih rute (1-%d) : ", total);
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
            tanggal[pos++] = ch;
            printf("%c", ch);
        }

        // ===== DIGIT 2 =====
        else if (pos == 1) {
            if ((tanggal[0] == '3' && ch >= '0' && ch <= '2') ||
                (tanggal[0] != '3' && ch >= '0' && ch <= '9')) {
                tanggal[pos++] = ch;
                printf("%c", ch);
                }
        }

        // ===== AUTO "/" =====
        else if (pos == 2) {
            tanggal[pos++] = '/';
            printf("/");
        }

        // ===== DIGIT 3 (bulan puluhan) =====
        else if (pos == 3 && (ch == '0' || ch == '1')) {
            tanggal[pos++] = ch;
            printf("%c", ch);
        }

        // ===== DIGIT 4 (bulan satuan) =====
        else if (pos == 4) {
            if ((tanggal[3] == '1' && ch >= '0' && ch <= '2') ||
                (tanggal[3] == '0' && ch >= '1' && ch <= '9')) {
                tanggal[pos++] = ch;
                printf("%c", ch);
                }
        }

        // ===== AUTO "/2025" =====
        else if (pos == 5) {
            sprintf(&tanggal[5], "/2025");
            printf("/2025");
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
        gotoxy(37, 28); printf("ID Jadwal    : %s", j.id);

        gotoxy(37, 29); printf("Tanggal      : ");
        gotoxy(52, 29);
        inputTanggals(j.tanggal, 52, 29);


        Rute r;

        gotoxy(37, 30); printf("Pilih rute        : ");
        // gotoxy(52, 30); printf("");
        _getch();

        if (!pilihRuteDanTampil(&r)) return;

        // tampilkan detail rute
        char hargaStr[25];
        formatHarga((int)r.harga, hargaStr);

        gotoxy(37, 31); printf("Kota Awal     : %-20s", r.kotaAsal);
        gotoxy(37, 32); printf("Kota Akhir    : %-20s", r.kotaTujuan);
        gotoxy(37, 33); printf("Jam Berangkat : %-10s", r.jamBerangkat);
        gotoxy(37, 34); printf("Harga         : %-15s", hargaStr);

        // simpan ke jadwal
        strcpy(j.kotaAsal, r.kotaAsal);
        strcpy(j.kotaTujuan, r.kotaTujuan);
        strcpy(j.jamBerangkat, r.jamBerangkat);
        j.harga = r.harga;


        gotoxy(37, 35); printf("Kategori      : ");
        // gotoxy(37, 50); printf("[B]usiness [E]konomi [x]ecutive");
        gotoxy(53, 35);
        inputKategori(j.kategori, 53, 35);

        gotoxy(37, 36); printf("Nama Armada   : ");
        gotoxy(53, 36); scanf(" %[^\n]", j.armada);

        fwrite(&j, sizeof(jadwal), 1, fp);
        fclose(fp);

        gotoxy(37, 37); printf("Data jadwal berhasil ditambahkan!");
        gotoxy(37, 38); printf("Tambah lagi? (y/n): ");

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

void buatdummyjadwal() {
    FILE *fp;
    jadwal data;
    int max_data = 40;

    char *kota_awal[] = {
        "Jakarta", "Bandung", "Surabaya", "Semarang",
        "Yogyakarta", "Malang", "Solo"
    };

    char *kota_akhir[] = {
        "Bandung", "Jakarta", "Surabaya", "Yogyakarta",
        "Malang", "Solo", "Semarang"
    };

    // ARMADA DIGANTI
    char *armada[] = {
        "Sinar Jaya",
        "Arimbi",
        "Rosalia Indah",
        "Agra Mas",
        "Budiman",
        "Blue Star"
    };

    // KATEGORI BARU
    char *kategori[] = {
        "Business",
        "Executive",
        "Ekonomi"
    };

    char *tanggal[] = {
        "12/01/2025", "13/01/2025", "14/01/2025",
        "15/01/2025", "16/01/2025"
    };

    char *jam[] = {
        "06:00", "08:30", "10:00",
        "13:00", "16:30", "19:00", "21:30"
    };

    int harga[] = {
        75000, 90000, 120000, 150000, 180000
    };

    int jml_awal    = sizeof(kota_awal) / sizeof(kota_awal[0]);
    int jml_akhir   = sizeof(kota_akhir) / sizeof(kota_akhir[0]);
    int jml_armada  = sizeof(armada) / sizeof(armada[0]);
    int jml_kategori= sizeof(kategori) / sizeof(kategori[0]);
    int jml_tgl     = sizeof(tanggal) / sizeof(tanggal[0]);
    int jml_jam     = sizeof(jam) / sizeof(jam[0]);
    int jml_harga   = sizeof(harga) / sizeof(harga[0]);

    fp = fopen("jadwal.dat", "wb");
    if (fp == NULL) {
        printf("ERROR: Gagal membuat file jadwal.dat\n");
        getch();
        return;
    }

    printf("     MEMBUAT DATA DUMMY JADWAL\n\n");

    for (int i = 0; i < max_data; i++) {

        sprintf(data.id, "JDW%03d", i + 1);

        strcpy(data.kotaAsal, kota_awal[i % jml_awal]);
        strcpy(data.kotaTujuan, kota_akhir[i % jml_akhir]);

        // Pastikan kota awal != kota akhir
        if (strcmp(data.kotaAsal, data.kotaTujuan) == 0) {
            strcpy(data.kotaTujuan, kota_akhir[(i + 1) % jml_akhir]);
        }

        strcpy(data.armada, armada[i % jml_armada]);
        strcpy(data.kategori, kategori[i % jml_kategori]); // ← BARU
        strcpy(data.tanggal, tanggal[i % jml_tgl]);
        strcpy(data.jamBerangkat, jam[i % jml_jam]);

        data.harga = harga[i % jml_harga] + (i * 2000);

        fwrite(&data, sizeof(jadwal), 1, fp);
    }

    fclose(fp);

    printf("[✓] Berhasil membuat %d data dummy jadwal\n", max_data);
    printf("Tekan tombol apapun untuk kembali...");
    getch();
}




#endif //PROJEK_CREATEJADWAL_H