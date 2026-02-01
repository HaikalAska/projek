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
    char statusRute[10];
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
int inputJam(char *out) {  // ← Ubah return type dari void ke int
    char jam[3] = "", menit[3] = "";
    int i = 0;
    char ch;

    // ===== INPUT JAM (HH) =====
    while (i < 2) {
        ch = _getch();

        if (ch == 27) {
            out[0] = '\0';
            return -1;  // ← Return -1 sebagai penanda ESC
        }

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

        if (ch == 27) {
            out[0] = '\0';
            return -1;  // ← Return -1 sebagai penanda ESC
        }

        // digit pertama menit: 0 - 5
        if (i == 0 && ch >= '0' && ch <= '5') {
            menit[i++] = ch;
            printf("%c", ch);
        }
        // digit kedua menit: 0 - 9
        else if (i == 1 && ch >= '0' && ch <= '9') {
            menit[i++] = ch;
            printf("%c", ch);
        }
    }

    menit[2] = '\0';

    sprintf(out, "%s:%s", jam, menit);
    return 0;  // ← Return 0 jika sukses
}


// ================= INPUT HARGA =================
int inputHarga(int x, int y) {
    char buf[9] = "";   // max 8 digit + '\0'
    int i = 0;

    gotoxy(x, y);
    printf("Rp");

    while (1) {
        char ch = _getch();

        // ESC batal
        if (ch == 27) return -1;

        // ENTER
        if (ch == 13 && i > 0) {
            int nilai = atoi(buf);

            // Validasi: angka tidak boleh 0
            if (nilai == 0) {
                gotoxy(x, y + 1);
                printf("Angka tidak boleh 0!");
                Sleep(1500);

                // Hapus pesan error
                gotoxy(x, y + 1);
                printf("                      ");

                // Reset input
                i = 0;
                memset(buf, 0, sizeof(buf));
                gotoxy(x, y);
                printf("Rp              ");
                gotoxy(x, y);
                printf("Rp");
                continue;
            }

            // Format final dengan titik pemisah ribuan
            gotoxy(x, y);
            printf("Rp");

            if (nilai < 1000) {
                printf("%d", nilai);
            } else if (nilai < 1000000) {
                printf("%d.%03d", nilai / 1000, nilai % 1000);
            } else {
                printf("%d.%03d.%03d", nilai / 1000000, (nilai / 1000) % 1000, nilai % 1000);
            }

            return nilai;
        }

        // BACKSPACE
        if (ch == 8 && i > 0) {
            i--;
            buf[i] = '\0';

            // Hapus tampilan dan tampilkan ulang
            gotoxy(x, y);
            printf("Rp              ");
            gotoxy(x, y);
            printf("Rp");

            // Tampilkan ulang dengan format
            if (i > 0) {
                int nilai = atoi(buf);
                if (nilai < 1000) {
                    printf("%d", nilai);
                } else if (nilai < 1000000) {
                    printf("%d.%03d", nilai / 1000, nilai % 1000);
                } else {
                    printf("%d.%03d.%03d", nilai / 1000000, (nilai / 1000) % 1000, nilai % 1000);
                }
            }
        }

        // ANGKA (maks 8 digit)
        if (ch >= '0' && ch <= '9' && i < 8) {
            buf[i++] = ch;
            buf[i] = '\0';

            int nilai = atoi(buf);

            // Hapus dan tampilkan ulang dengan format
            gotoxy(x, y);
            printf("Rp              ");
            gotoxy(x, y);
            printf("Rp");

            // Format dengan titik
            if (nilai < 1000) {
                printf("%d", nilai);
            } else if (nilai < 1000000) {
                printf("%d.%03d", nilai / 1000, nilai % 1000);
            } else {
                printf("%d.%03d.%03d", nilai / 1000000, (nilai / 1000) % 1000, nilai % 1000);
            }
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


void pilihKota(char *output, char *kotaTerpilihSebelumnya) {
    int x = 82, y = 29;
    int pilih;

pilihProvinsi:
    // Bersihkan area sebelumnya (samakan dengan frame)
    clearArea(85, 29, 45, 12);

    // Buat frame
    bentukframe(85, 29, 45, 12);

    // Judul
    gotoxy(98, 30);
    printf("=== PILIH PROVINSI ===");

    // Daftar provinsi
    gotoxy(95, 32); printf("Banten");
    gotoxy(95, 33); printf("DKI Jakarta");
    gotoxy(95, 34); printf("Jawa Barat");
    gotoxy(95, 35); printf("Jawa Tengah");
    gotoxy(95, 36); printf("Yogyakarta");
    gotoxy(95, 37); printf("Jawa Timur");

    // Navigasi
    pilih = rutenavigasi(93, 32, 6, 1);


    // ================= BANTEN =================
    if (pilih == 0) {
        clearArea(85, 29, 45, 12);
        bentukframe(85,29, 45, 12);

        gotoxy(101, 30); printf("=== BANTEN ===");

        int indexSerang = 0, indexTangerang = 1;
        int jumlahOpsi = 0;
        int mapping[2]; // untuk mapping pilihan ke kota asli

        // Tampilkan Serang jika belum dipilih
        if (strcmp(kotaTerpilihSebelumnya, "Serang") != 0) {
            gotoxy(95, 32 + jumlahOpsi);
            printf("Serang");
            mapping[jumlahOpsi] = 0;
            jumlahOpsi++;
        }

        // Tampilkan Tangerang jika belum dipilih
        if (strcmp(kotaTerpilihSebelumnya, "Tangerang") != 0) {
            gotoxy(95, 32 + jumlahOpsi);
            printf("Tangerang");
            mapping[jumlahOpsi] = 1;
            jumlahOpsi++;
        }

        // Jika semua kota sudah dipilih
        if (jumlahOpsi == 0) {
            gotoxy(95, 32);
            printf("Semua kota sudah dipilih!");
            gotoxy(95, 34);
            printf("Tekan ESC untuk kembali");
            _getch();
            goto pilihProvinsi;
        }

        pilih = rutenavigasi(93, 32, jumlahOpsi, 1);

        if (pilih >= 0 && pilih < jumlahOpsi) {
            if (mapping[pilih] == 0) strcpy(output, "Serang");
            else if (mapping[pilih] == 1) strcpy(output, "Tangerang");
        } else {
            goto pilihProvinsi;
        }

        clearArea(85, 29, 45, 12);
        return;
    }


    // ================= DKI =================
    else if (pilih == 1) {
        // Cek apakah Jakarta sudah dipilih sebelumnya
        if (strcmp(kotaTerpilihSebelumnya, "Jakarta") == 0) {
            clearArea(85, 29, 45, 12);
            bentukframe(85, 29, 45, 12);
            gotoxy(95, 32);
            printf("Jakarta sudah dipilih!");
            gotoxy(95, 34);
            printf("Tekan ESC untuk kembali");
            _getch();
            goto pilihProvinsi;
        }

        strcpy(output, "Jakarta");
        clearArea(85, 29, 45, 12);
        return;
    }


    // ================= JAWA BARAT =================
    else if (pilih == 2) {
        clearArea(85, 29, 45, 12);
        bentukframe(85, 29, 45, 12);

        gotoxy(99, 30); printf("=== JAWA BARAT ===");

        int jumlahOpsi = 0;
        int mapping[5];
        char *namaKota[5] = {"Bandung", "Bekasi", "Bogor", "Cirebon", "Tasikmalaya"};

        // Tampilkan hanya kota yang belum dipilih
        for (int i = 0; i < 5; i++) {
            if (strcmp(kotaTerpilihSebelumnya, namaKota[i]) != 0) {
                gotoxy(95, 32 + jumlahOpsi);
                printf("%s", namaKota[i]);
                mapping[jumlahOpsi] = i;
                jumlahOpsi++;
            }
        }

        // Jika semua kota sudah dipilih
        if (jumlahOpsi == 0) {
            gotoxy(95, 32);
            printf("Semua kota sudah dipilih!");
            gotoxy(95, 34);
            printf("Tekan ESC untuk kembali");
            _getch();
            goto pilihProvinsi;
        }

        pilih = rutenavigasi(93, 32, jumlahOpsi, 1);

        if (pilih >= 0 && pilih < jumlahOpsi) {
            strcpy(output, namaKota[mapping[pilih]]);
        } else {
            goto pilihProvinsi;
        }

        clearArea(85, 29, 45, 12);
        return;
    }


    // ================= JAWA TENGAH =================
    else if (pilih == 3) {
        clearArea(85, 29, 45, 12);
        bentukframe(85, 29, 45, 12);

        gotoxy(99, 30); printf("=== JAWA TENGAH ===");

        int jumlahOpsi = 0;
        int mapping[4];
        char *namaKota[4] = {"Semarang", "Magelang", "Pekalongan", "Tegal"};

        for (int i = 0; i < 4; i++) {
            if (strcmp(kotaTerpilihSebelumnya, namaKota[i]) != 0) {
                gotoxy(95, 32 + jumlahOpsi);
                printf("%s", namaKota[i]);
                mapping[jumlahOpsi] = i;
                jumlahOpsi++;
            }
        }

        if (jumlahOpsi == 0) {
            gotoxy(95, 32);
            printf("Semua kota sudah dipilih!");
            gotoxy(95, 34);
            printf("Tekan ESC untuk kembali");
            _getch();
            goto pilihProvinsi;
        }

        pilih = rutenavigasi(93, 32, jumlahOpsi, 1);

        if (pilih >= 0 && pilih < jumlahOpsi) {
            strcpy(output, namaKota[mapping[pilih]]);
        } else {
            goto pilihProvinsi;
        }

        clearArea(85, 29, 45, 12);
        return;
    }


    // ================= YOGYAKARTA =================
    else if (pilih == 4) {
        if (strcmp(kotaTerpilihSebelumnya, "Yogyakarta") == 0) {
            clearArea(85, 29, 45, 12);
            bentukframe(85, 29, 45, 12);
            gotoxy(95, 32);
            printf("Yogyakarta sudah dipilih!");
            gotoxy(95, 34);
            printf("Tekan ESC untuk kembali");
            _getch();
            goto pilihProvinsi;
        }

        strcpy(output, "Yogyakarta");
        clearArea(85, 29, 45, 12);
        return;
    }

    // ================= JAWA TIMUR =================
    else if (pilih == 5) {
        clearArea(85, 29, 45, 12);
        bentukframe(85, 29, 45, 12);

        gotoxy(99, 30); printf("=== JAWA TIMUR ===");

        int jumlahOpsi = 0;
        int mapping[6];
        char *namaKota[6] = {"Surabaya", "Malang", "Kediri", "Mojokerto", "Madiun", "Probolinggo"};

        for (int i = 0; i < 6; i++) {
            if (strcmp(kotaTerpilihSebelumnya, namaKota[i]) != 0) {
                gotoxy(95, 32 + jumlahOpsi);
                printf("%s", namaKota[i]);
                mapping[jumlahOpsi] = i;
                jumlahOpsi++;
            }
        }

        if (jumlahOpsi == 0) {
            gotoxy(95, 32);
            printf("Semua kota sudah dipilih!");
            gotoxy(95, 34);
            printf("Tekan ESC untuk kembali");
            _getch();
            goto pilihProvinsi;
        }

        pilih = rutenavigasi(93, 32, jumlahOpsi, 1);

        if (pilih >= 0 && pilih < jumlahOpsi) {
            strcpy(output, namaKota[mapping[pilih]]);
        } else {
            goto pilihProvinsi;
        }

        clearArea(85, 29, 45, 12);
        return;
    }
}



// ================= CREATE RUTE =================
void buatrute() {
    char n;
    char kotaPertama[50];
    char kotaKedua[50];

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
        pilihKota(kotaPertama, "");
        strcpy(r.kotaAsal, kotaPertama);
        gotoxy(52, 29); printf("%s", r.kotaAsal);

        gotoxy(37, 30); printf("Kota Tujuan  : ");
        pilihKota(kotaKedua, kotaPertama);
        strcpy(r.kotaTujuan, kotaKedua);
        gotoxy(52, 30); printf("%s", r.kotaTujuan);

        gotoxy(37, 31); printf("Harga        : ");
        r.harga = inputHarga(52, 31);
        if (r.harga == 0) { fclose(fp); return; }

        gotoxy(37, 32); printf("Jam Berangkat: ");
        if (inputJam(r.jamBerangkat) == -1) {  // ← Cek return value
            fclose(fp);
            return;
        }

        gotoxy(37, 33); printf("Jam Tiba     : ");
        if (inputJam(r.jamTiba) == -1) {  // ← Cek return value
            fclose(fp);
            return;
        }

        strcpy(r.statusRute, "Aktif");
        gotoxy(37, 34);
        printf("Status       : %s ", r.statusRute);

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

    // ================= DATA KOTA SESUAI pilihKota() =================
    char *asal[] = {
        "Jakarta","Jakarta","Jakarta","Bandung","Bandung",
        "Semarang","Semarang","Surabaya","Surabaya","Malang",
        "Yogyakarta","Cirebon","Tegal","Madiun","Kediri"
    };

    char *tujuan[] = {
        "Bandung","Cirebon","Semarang","Jakarta","Semarang",
        "Surabaya","Yogyakarta","Malang","Kediri","Yogyakarta",
        "Surabaya","Jakarta","Semarang","Surabaya","Malang"
    };

    int harga[] = {
        150000, // Jakarta - Bandung
        180000, // Jakarta - Cirebon
        280000, // Jakarta - Semarang
        150000, // Bandung - Jakarta
        250000, // Bandung - Semarang
        230000, // Semarang - Surabaya
        200000, // Semarang - Yogyakarta
        100000, // Surabaya - Malang
        140000, // Surabaya - Kediri
        350000, // Malang - Yogyakarta
        300000, // Yogyakarta - Surabaya
        180000, // Cirebon - Jakarta
        220000, // Tegal - Semarang
        180000, // Madiun - Surabaya
        120000  // Kediri - Malang
    };

    int totalRute = 15;

    for (int i = 0; i < 50; i++) {
        sprintf(r.id, "RT%03d", i + 1);

        int idx = i % totalRute;

        strcpy(r.kotaAsal, asal[idx]);
        strcpy(r.kotaTujuan, tujuan[idx]);

        // Variasi harga kecil biar natural
        r.harga = harga[idx] + (i % 4) * 5000;

        // Jam berangkat 05.00 – 19.00
        int jam = 5 + (i % 15);
        int menit = (i * 10) % 60;

        sprintf(r.jamBerangkat, "%02d:%02d", jam, menit);
        sprintf(r.jamTiba, "%02d:%02d", (jam + 4) % 24, menit);

        fwrite(&r, sizeof(Rute), 1, fp);
    }

    fclose(fp);

    gotoxy(40, 40);
    printf("✓ 50 data dummy rute REALISTIS berhasil dibuat");
    getch();
}


#endif // PROJEK_CREATERUTE_H
