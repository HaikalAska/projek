//
// Created by Lenovo on 05/12/2025.
//

#ifndef PROJEK_CREATEKENDARAAN_H
#define PROJEK_CREATEKENDARAAN_H

#include "../FrameTabel.h"
#include <string.h>
#include <time.h>

typedef struct {
    char id_kendaraan[10];
    char kategori[30];
    char kapasitas[10];
    char fasilitas[100];
    char nama_armada[50];
    char tahun[5];
} Kendaraan;

// ================= INPUT KAPASITAS =================
static void inpukapasitas(char *angka, int maxLen) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();

        if (ch == 13) {
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

static int getKendaraanCount() {
    FILE *fp = fopen("kendaraan.dat", "rb");
    if (!fp) return 0;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);

    return size / sizeof(Kendaraan);
}

void inputKapasitas2Digit(char *kapasitas) {
    int i = 0;
    char ch;
    char temp[3] = "";

    const int INPUT_X = 52;
    const int INPUT_Y = 30;
    const int ERR_X   = 80;
    const int ERR_Y   = 30;

    while (1) {
        ch = getch();

        // ===== ENTER =====
        if (ch == 13) {
            temp[i] = '\0';

            // kosong
            if (i == 0) {
                gotoxy(ERR_X, ERR_Y);
                printf("%-25s", "[Tidak boleh kosong]");
                Sleep(800);
                gotoxy(ERR_X, ERR_Y);
                printf("%-25s", " ");
                gotoxy(INPUT_X, INPUT_Y);
                continue;
            }

            int nilai = atoi(temp);

            // validasi 1 - 60
            if (nilai < 1 || nilai > 60) {
                gotoxy(ERR_X, ERR_Y);
                printf("%-25s", "[Kapasitas hanya 1 - 60]");
                Sleep(800);

                // hapus error
                gotoxy(ERR_X, ERR_Y);
                printf("%-25s", " ");

                // hapus input angka
                gotoxy(INPUT_X, INPUT_Y);
                printf("  ");
                gotoxy(INPUT_X, INPUT_Y);

                i = 0;
                memset(temp, 0, sizeof(temp));
                continue;
            }

            // valid → simpan
            strcpy(kapasitas, temp);
            return;
        }

        // ===== ESC =====
        else if (ch == 27) {
            kapasitas[0] = '\0';
            return;
        }

        // ===== BACKSPACE =====
        else if (ch == 8) {
            if (i > 0) {
                i--;
                gotoxy(INPUT_X + i, INPUT_Y);
                printf(" ");
                gotoxy(INPUT_X + i, INPUT_Y);
            }
        }

        //ANGKA SAJA (MAKS 2 DIGIT) =====
        else if (ch >= '0' && ch <= '9') {
            if (i < 2) {
                temp[i] = ch;
                gotoxy(INPUT_X + i, INPUT_Y);
                printf("%c", ch);
                i++;
            }
        }
    }
}

// ================= INPUT FASILITAS =================
static void inputFasilitas(char *fasilitas, int maxLen) {
    int i = 0;
    char ch;

    const int INPUT_X = 52;
    const int INPUT_Y = 31;
    const int ERR_X   = 85;
    const int ERR_Y   = 31;

    while (1) {
        ch = getch();

        if (ch == 13) { // ENTER
            fasilitas[i] = '\0';

            if (i == 0) {
                // tampilkan error
                gotoxy(ERR_X, ERR_Y);
                printf("%-30s", "[Tidak boleh kosong]");
                Sleep(800);

                // hapus error
                gotoxy(ERR_X, ERR_Y);
                printf("%-30s", " ");

                // balik ke input
                gotoxy(INPUT_X, INPUT_Y);
                continue;
            }
            return;
        }
        else if (ch == 27) { // ESC
            fasilitas[0] = '\0';
            return;
        }
        else if (ch == 8) { // BACKSPACE
            if (i > 0) {
                i--;
                gotoxy(INPUT_X + i, INPUT_Y);
                printf(" ");
                gotoxy(INPUT_X + i, INPUT_Y);
            }
        }
        else if ((ch >= 'a' && ch <= 'z') ||
                 (ch >= 'A' && ch <= 'Z') ||
                 ch == ' ' || ch == ',') {

            if (i < maxLen - 1) {
                fasilitas[i++] = ch;
                gotoxy(INPUT_X + i - 1, INPUT_Y);
                printf("%c", ch);
            }
                 }
    }
}

// ================= INPUT KATEGORI =================
static void inputKategoriKendaraan(char *kategori) {
    char ch;
    char temp[30] = "";

    const int INPUT_X = 52;
    const int Y       = 29;
    const int INFO_X  = 85;

    // tampilkan petunjuk SEKALI
    gotoxy(INFO_X, Y);
    printf("Isi (E/B/X)");

    while (1) {
        ch = getch();

        // ===== ESC =====
        if (ch == 27) {
            kategori[0] = '\0';
            return;
        }

        // ===== ENTER =====
        if (ch == 13) {
            if (strlen(temp) == 0) {
                // tampilkan error
                gotoxy(INFO_X, Y);
                printf("%-25s", "[Wajib pilih kategori]");
                Sleep(800);

                // hapus error
                gotoxy(INFO_X, Y);
                printf("%-25s", " ");

                // BALIKIN PETUNJUK
                gotoxy(INFO_X, Y);
                printf("Isi (E/B/X)");

                // balik ke input
                gotoxy(INPUT_X, Y);
                continue;
            }

            // valid
            strcpy(kategori, temp);
            return;
        }

        // ===== PILIHAN =====
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

            default:
                continue;
        }

        // hapus petunjuk (sekali user mulai input)
        gotoxy(INFO_X, Y);
        printf("%-25s", " ");

        // tampilkan pilihan
        gotoxy(INPUT_X, Y);
        printf("%-30s", temp);
    }
}

// ================= INPUT ARMADA =================
void inputNamaArmada(char *nama) {
    int i = 0;
    char ch;

    const int INPUT_X = 52;
    const int INPUT_Y = 32;
    const int ERR_X   = 85;
    const int ERR_Y   = 32;

    while (1) {
        ch = getch();

        // ENTER
        if (ch == 13) {
            nama[i] = '\0';

            if (i == 0) {
                gotoxy(ERR_X, ERR_Y);
                printf("%-30s", "[Nama armada wajib diisi]");
                Sleep(800);
                gotoxy(ERR_X, ERR_Y);
                printf("%-30s", " ");
                gotoxy(INPUT_X, INPUT_Y);
                continue;
            }
            return;
        }

        // ESC
        else if (ch == 27) {
            nama[0] = '\0';
            return;
        }

        // BACKSPACE
        else if (ch == 8 && i > 0) {
            i--;
            gotoxy(INPUT_X + i, INPUT_Y);
            printf(" ");
            gotoxy(INPUT_X + i, INPUT_Y);
        }

        // ===== HANYA HURUF & SPASI =====
        else if ((ch >= 'A' && ch <= 'Z') ||
                 (ch >= 'a' && ch <= 'z') ||
                 ch == ' ') {

            if (i < 49) {
                nama[i++] = ch;
                gotoxy(INPUT_X + i - 1, INPUT_Y);
                printf("%c", ch);
            }
                 }
        // angka & simbol otomatis ditolak
    }
}

// ================= INPUT TAHUN =================
void inputTahun(char *tahun) {
    int i = 0;
    char ch;

    const int X = 52;
    const int Y = 33;

    gotoxy(X, Y);

    while (1) {
        ch = getch();

        if (ch == 13) {
            if (i != 4) {
                gotoxy(80, Y);
                printf("[Harus 4 digit]");
                Sleep(800);
                gotoxy(80, Y);
                printf("               ");
                gotoxy(X + i, Y);
                continue;
            }
            tahun[i] = '\0';
            return;
        }

        else if (ch == 27) {
            tahun[0] = '\0';
            return;
        }

        else if (ch == 8 && i > 0) {
            i--;
            gotoxy(X + i, Y);
            printf(" ");
            gotoxy(X + i, Y);
        }

        else if (ch >= '0' && ch <= '9' && i < 4) {
            tahun[i++] = ch;
            gotoxy(X + i - 1, Y);
            printf("%c", ch);
        }
    }
}

int getTahunSekarang() {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    return tm_info->tm_year + 1900;
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
        inputNamaArmada(data.nama_armada);


        if (strlen(data.nama_armada) == 0) {
            fclose(fp);
            return;
        }

        // ===== TAHUN =====
        gotoxy(37, 33); printf("Tahun        : ");
        setPointer(34, 53);
        inputTahun(data.tahun);
        if (strlen(data.tahun) == 0) {
            fclose(fp);
            return;
        }

        // ===== CEK UMUR BUS =====
        int tahunBus = atoi(data.tahun);
        int tahunSekarang = getTahunSekarang();
        int umur = tahunSekarang - tahunBus;

        gotoxy(85, 33);
        if (umur > 10) {
            printf("[Tidak Layak | Umur %d th]", umur);
        } else {
            printf("[Layak | Umur %d th]", umur);
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
        "Ekonomi",
        "Bisnis",
        "Executive",

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