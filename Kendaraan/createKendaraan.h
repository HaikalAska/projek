//
// Created by Lenovo on 05/12/2025.
//

#ifndef PROJEK_CREATEKENDARAAN_H
#define PROJEK_CREATEKENDARAAN_H

#include "../FrameTabel.h"
#include <string.h>

// ================= STRUCT KENDARAAN =================
typedef struct {
    char id_kendaraan[10];
    char kategori[30];
    char kapasitas[10];
    char fasilitas[100];
    char nama_armada[50];
} Kendaraan;

// ================= INPUT ANGKA (UNTUK KAPASITAS) =================
static void inputAngka(char *angka, int maxLen) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();

        if (ch == 13) { // ENTER
            angka[i] = '\0';

            if (i == 0) {
                printf(" [Tidak boleh kosong]");
                Sleep(700);

                printf("\r                     \r");
                i = 0;
                continue;
            }
            break;
        }
        else if (ch == 27) { // ESC
            angka[0] = '\0';
            break;
        }
        else if (ch == 8) { // BACKSPACE
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if (ch >= '0' && ch <= '9') {
            if (i < maxLen - 1) {
                angka[i++] = ch;
                printf("%c", ch);
            }
        }
        // selain angka → diabaikan
    }
}

// ================= HITUNG DATA =================
static int getKendaraanCount() {
    FILE *fp = fopen("kendaraan.dat", "rb");
    if (!fp) return 0;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);

    return size / sizeof(Kendaraan);
}

// ================= VALIDASI KAPASITAS 2 DIGIT =================
void inputKapasitas2Digit(char *kapasitas) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();

        // ENTER
        if (ch == 13) {
            kapasitas[i] = '\0';

            if (i == 0) {
                printf(" [Tidak boleh kosong]");
                Sleep(800);
                printf("\r                     \r");
                i = 0;
                continue;
            }
            break;
        }
        // ESC
        else if (ch == 27) {
            kapasitas[0] = '\0';
            break;
        }
        // BACKSPACE
        else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        // HANYA ANGKA & MAKS 2 DIGIT
        else if (ch >= '0' && ch <= '6') {
            if (i < 2) {
                kapasitas[i++] = ch;
                printf("%c", ch);
            }
        }
    }
}

// ================= INPUT FASILITAS =================
static void inputFasilitas(char *fasilitas, int maxLen) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();

        // ENTER
        if (ch == 13) {
            fasilitas[i] = '\0';

            if (i == 0) {
                printf(" [Tidak boleh kosong]");
                Sleep(800);
                printf("\r                              \r");
                i = 0;
                continue;
            }
            break;
        }
        // ESC
        else if (ch == 27) {
            fasilitas[0] = '\0';
            break;
        }
        // BACKSPACE
        else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        // HURUF
        else if ((ch >= 'a' && ch <= 'z') ||
                 (ch >= 'A' && ch <= 'Z')) {
            if (i < maxLen - 1) {
                fasilitas[i++] = ch;
                printf("%c", ch);
            }
        }
        // SPASI
        else if (ch == ' ') {
            if (i < maxLen - 1 && i > 0 && fasilitas[i - 1] != ' ') {
                fasilitas[i++] = ch;
                printf(" ");
            }
        }
        // KOMA (,)
        else if (ch == ',') {
            if (i < maxLen - 1 && i > 0 && fasilitas[i - 1] != ',') {
                fasilitas[i++] = ch;
                printf(",");
            }
        }
        // karakter lain → diabaikan
    }
}

// ================= INPUT KATEGORI KENDARAAN =================
static void inputKategoriKendaraan(char *kategori) {
    char ch;
    char temp[50] = "";   // simpan pilihan sementara

    while (1) {
        ch = getch();

        // ESC → batal
        if (ch == 27) {
            kategori[0] = '\0';
            return;
        }

        // ENTER → konfirmasi pilihan
        if (ch == 13) {
            if (strlen(temp) == 0) {
                // belum pilih apa-apa
                printf(" [Pilih kategori dulu]");
                Sleep(800);

                // Hapus peringatan
                printf("\r");
                for (int k = 0; k < 50; k++) {
                    printf(" ");
                }
                printf("\r");
                continue;
            }

            strcpy(kategori, temp); // simpan final
            return;
        }

        // PILIHAN KATEGORI
        switch (ch) {
            case 'e':
            case 'E':
                strcpy(temp, "Ekonomi");
                break;

            case 'b':
            case 'B':
                strcpy(temp, "Bisnis");
                break;

            case 'x':
            case 'X':
                strcpy(temp, "Executive");
                break;

            case 'p':
            case 'P':
                strcpy(temp, "Pariwisata");
                break;

            case 'm':
            case 'M':
                strcpy(temp, "Mania");
                break;

            default:
                continue; // tombol lain (termasuk Tab) diabaikan
        }

        // TAMPILKAN PILIHAN (bisa berubah-ubah)
        // Hapus text lama dulu
        // printf("\r");
        for (int k = 0; k < 50; k++) {
            // printf(" ");
        }
        // printf("\r");

        // Tampilkan pilihan baru
        gotoxy(52,29); printf("%-30s", temp);
    }
}

// ================= CREATE KENDARAAN =================
void createKendaraan() {
    char n;

    do {
        bentukframe(35, 27, 108, 16);
        gotoxy(78, 27); printf("=== TAMBAH KENDARAAN ===");

        FILE *fp = fopen("kendaraan.dat", "ab");
        if (!fp) return;

        Kendaraan data;

        // ===== ID OTOMATIS =====
        int count = getKendaraanCount() + 1;
        sprintf(data.id_kendaraan, "KND%03d", count);
        gotoxy(37, 28);
        printf("ID Kendaraan : %s", data.id_kendaraan);

        // ===== KATEGORI =====
        gotoxy(37, 29); printf("Kategori     : ");
        setPointer(30, 53);
        inputKategoriKendaraan(data.kategori);
        if (strlen(data.kategori) == 0) {
            fclose(fp);
            return;
        }

        // ===== KAPASITAS =====
        gotoxy(37, 30); printf("Kapasitas    : ");
        setPointer(31, 53);
        inputKapasitas2Digit(data.kapasitas);
        if (strlen(data.kapasitas) == 0) {
            fclose(fp);
            return;
        }

        // ===== FASILITAS =====
        gotoxy(37, 31); printf("Fasilitas    : ");
        setPointer(32, 53);
        inputFasilitas(data.fasilitas, sizeof(data.fasilitas));
        if (strlen(data.fasilitas) == 0) {
            fclose(fp);
            return;
        }

        // ===== NAMA ARMADA =====
        gotoxy(37, 32); printf("Nama Armada  : ");
        setPointer(33, 53);
        INPUTNama(data.nama_armada);
        if (strlen(data.nama_armada) == 0) {
            fclose(fp);
            return;
        }

        // ===== SIMPAN =====
        fwrite(&data, sizeof(Kendaraan), 1, fp);
        fclose(fp);

        gotoxy(37, 34);
        printf("Data kendaraan berhasil dibuat!");

        gotoxy(37, 35);
        printf("Tambah lagi? (y/n): ");

        while (1) {
            n = _getch();
            if (n == 27) { // ESC
                clearArea(35, 28, 70, 12);
                return;
            }
            if (n == 'y' || n == 'Y' || n == 'n' || n == 'N') {
                clearArea(35, 28, 70, 12);
                if (n == 'n' || n == 'N') return;
                break;
            }
        }

    } while (n == 'y' || n == 'Y');
}

// ================= DATA DUMMY KENDARAAN =================
void buatDummyKendaraan() {
    FILE *fp;
    Kendaraan data;
    int max_data = 50;

    // ===== CONTOH DATA =====
    char *kategori[] = {
        "Bus Ekonomi",
        "Bus Bisnis",
        "Bus Executive",
        "Mini Bus",
        "Bus Pariwisata"
    };

    char *kapasitas[] = {
        "25", "30", "35", "40", "45", "50"
    };

    char *fasilitas[] = {
        "AC",
        "AC, Reclining Seat",
        "AC, Reclining Seat, Toilet",
        "AC, TV, USB Charger",
        "AC, Toilet, WiFi",
    };

    char *nama_armada[] = {
        "PO Sinar Jaya",
        "PO Rosalia Indah",
        "PO Harapan Jaya",
        "PO Pahala Kencana",
        "PO Gunung Harta",
        "PO Sumber Alam",
        "PO Lorena",
        "PO Agra Mas"
    };

    int nKategori  = sizeof(kategori) / sizeof(kategori[0]);
    int nKapasitas = sizeof(kapasitas) / sizeof(kapasitas[0]);
    int nFasilitas = sizeof(fasilitas) / sizeof(fasilitas[0]);
    int nArmada    = sizeof(nama_armada) / sizeof(nama_armada[0]);

    // ===== BUAT / RESET FILE =====
    fp = fopen("kendaraan.dat", "wb");
    if (fp == NULL) {
        printf("ERROR: Gagal membuat file kendaraan.dat\n");
        getch();
        return;
    }

    printf("     MEMBUAT DATA DUMMY KENDARAAN\n");

    for (int i = 0; i < max_data; i++) {

        // ID OTOMATIS
        sprintf(data.id_kendaraan, "KND%03d", i + 1);

        // ISI DATA (DI-ROTASI BIAR BERVARIASI)
        strcpy(data.kategori,  kategori[i % nKategori]);
        strcpy(data.kapasitas, kapasitas[i % nKapasitas]);
        strcpy(data.fasilitas, fasilitas[i % nFasilitas]);

        // Nama armada + nomor biar unik
        sprintf(data.nama_armada, "%s %d",
                nama_armada[i % nArmada],
                (i / nArmada) + 1);

        fwrite(&data, sizeof(Kendaraan), 1, fp);
    }

    fclose(fp);

    printf("\n[✓] Berhasil membuat %d data dummy kendaraan\n", max_data);
    printf("Tekan tombol apapun untuk kembali...");
    getch();
}

#endif // PROJEK_CREATEKENDARAAN_H