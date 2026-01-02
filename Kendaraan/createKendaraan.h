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
    char tahun[10];
    char status [20];
} Kendaraan;

// ================= INPUT KAPASITAS =================
static void inputKapasitas2Digit(char *kapasitas, int row, int col) {
    int i = 0;
    char ch;
    char temp[3] = "";   // buffer dibersihkan dari awal

    gotoxy(col, row);

    while (1) {
        ch = getch();

        // ===== ENTER =====
        if (ch == 13) {
            temp[i] = '\0';

            if (i == 0) {
                gotoxy(col + 0, row);
                printf("[Tidak boleh kosong]");
                Sleep(800);

                gotoxy(col + 0, row);
                printf("%-25s", " ");

                gotoxy(col, row);
                i = 0;
                continue;
            }

            int nilai = atoi(temp);
            if (nilai < 1 || nilai > 60) {
                gotoxy(col + 5, row);
                printf("[Kapasitas 1 - 60]");
                Sleep(800);

                gotoxy(col + 5, row);
                printf("%-25s", " ");

                gotoxy(col, row);
                printf("  ");
                gotoxy(col, row);

                i = 0;
                temp[0] = '\0';
                continue;
            }

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
                temp[i] = '\0';
                printf("\b \b");
            }
        }

        // ===== ANGKA =====
        else if (ch >= '0' && ch <= '9') {
            if (i < 2) {
                temp[i++] = ch;
                temp[i] = '\0';
                printf("%c", ch);
            }
        }
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

// ================= INPUT FASILITAS =================
static void inputFasilitas(char *fasilitas, int row, int col) {
    int i = 0;
    char ch;
    char temp[100];

    while (1) {
        ch = getch();

        if (ch == 13) {
            temp[i] = '\0';

            if (i == 0) {
                gotoxy(col + 0, row);
                printf("[Fasilitas tidak boleh kosong!]");
                Sleep(800);

                gotoxy(col + 0, row);
                printf("%-35s", " ");

                gotoxy(col, row);
                i = 0;
                continue;
            }

            strcpy(fasilitas, temp);
            return;
        }
        else if (ch == 27) {
            fasilitas[0] = '\0';
            return;
        }
        else if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        }
        else if ((ch >= 'a' && ch <= 'z') ||
                 (ch >= 'A' && ch <= 'Z') ||
                 ch == ' ' || ch == ',') {
            if (i < 99) {
                temp[i++] = ch;
                printf("%c", ch);
            }
                 }
    }
}

// ================= INPUT KATEGORI =================
static void inputKategoriKendaraan(char *kategori, int row, int col) {
    char ch;
    char temp[30] = "";

    while (1) {
        ch = getch();

        // ===== ENTER =====
        if (ch == 13) {
            if (strlen(temp) == 0) {
                gotoxy(col + 0, row);
                printf("[Wajib pilih kategori]");
                Sleep(800);
                gotoxy(col + 0, row);
                printf("%-25s", " ");
                continue;
            }

            strcpy(kategori, temp);
            return;
        }

        // ===== ESC =====
        if (ch == 27) {
            kategori[0] = '\0';
            return;
        }

        // ===== BACKSPACE → hapus pilihan =====
        if (ch == 8) {
            temp[0] = '\0';

            gotoxy(col, row);
            printf("%-30s", " ");
            gotoxy(col, row);
            continue;
        }

        // ===== PILIHAN KATEGORI =====
        if (ch == 'e' || ch == 'E') {
            strcpy(temp, "Ekonomi");
        }
        else if (ch == 'b' || ch == 'B') {
            strcpy(temp, "Bisnis");
        }
        else if (ch == 'x' || ch == 'X') {
            strcpy(temp, "Executive");
        }
        else {
            continue; // tombol lain diabaikan
        }

        // tampilkan pilihan
        gotoxy(col, row);
        printf("%-30s", temp);
    }
}

// ================= INPUT ARMADA =================
static void inputNamaArmada(char *nama, int row, int col) {
    int i = 0;
    char ch;
    char temp[50];

    while (1) {
        ch = getch();

        if (ch == 13) {
            temp[i] = '\0';

            if (i == 0) {
                gotoxy(col + 0, row);
                printf("[Nama armada wajib di isi!]");
                Sleep(800);

                gotoxy(col + 0, row);
                printf("%-35s", " ");

                gotoxy(col, row);
                i = 0;
                continue;
            }

            strcpy(nama, temp);
            break;
        }
        else if (ch == 27) {  // ESC
            nama[0] = '\0';
            break;
        }
        else if (ch == 8) {  // BACKSPACE (SAMA)
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if ((ch >= 'A' && ch <= 'Z') ||
                 (ch >= 'a' && ch <= 'z') ||
                 ch == ' ') {

            if (i < 49) {
                temp[i++] = ch;
                printf("%c", ch);
            }
                 }
    }
}

// ================= INPUT TAHUN =================
static void inputTahun(char *tahun, int row, int col) {
    int i = 0;
    char ch;
    char temp[5];

    while (1) {
        ch = getch();

        if (ch == 13) {  // ENTER
            temp[i] = '\0';

            // VALIDASI: HARUS 4 DIGIT
            if (i != 4) {
                // tampilkan error di KANAN input
                gotoxy(col + 0, row);
                printf("[Harus 4 digit]");
                Sleep(800);

                // hapus error DENGAN PANJANG SAMA
                gotoxy(col + 0, row);
                printf("%-15s", " ");

                // bersihkan input
                gotoxy(col, row);
                printf("    ");
                gotoxy(col, row);

                i = 0;
                continue;
            }

            // VALIDASI: MAKSIMAL 2025
            int tahunInput = atoi(temp);
            if (tahunInput > 2025) {
                gotoxy(col, row);
                printf("[Maksimal tahun 2025]");
                Sleep(800);

                gotoxy(col, row);
                printf("%-25s", " ");

                gotoxy(col, row);
                printf("    ");
                gotoxy(col, row);

                i = 0;
                continue;
            }

            strcpy(tahun, temp);
            return;
        }
        else if (ch == 27) {  // ESC
            tahun[0] = '\0';
            return;
        }
        else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if (ch >= '0' && ch <= '9') {
            if (i < 4) {
                temp[i++] = ch;
                printf("%c", ch);
            }
        }
    }
}

// ================= INPUT STATUS =================
static void inputStatusKendaraan(char *status, int row, int col) {
    char ch;
    char temp[20] = "";

    while (1) {
        ch = getch();

        // ===== ENTER =====
        if (ch == 13) {
            if (strlen(temp) == 0) {
                gotoxy(col + 0, row);
                printf("[Wajib pilih status]");
                Sleep(800);
                gotoxy(col + 0, row);
                printf("%-25s", " ");
                continue;
            }
            strcpy(status, temp);
            return;
        }

        // ===== ESC =====
        if (ch == 27) {
            status[0] = '\0';
            return;
        }

        // ===== BACKSPACE =====
        if (ch == 8) {
            temp[0] = '\0';
            gotoxy(col, row);
            printf("%-20s", " ");
            gotoxy(col, row);
            continue;
        }

        // ===== PILIHAN STATUS =====
        if (ch == 't' || ch == 'T') {
            strcpy(temp, "Tersedia");
        }
        else if (ch == 'm' || ch == 'M') {
            strcpy(temp, "Maintenance");
        }
        else if (ch == 'd' || ch == 'D') {
            strcpy(temp, "Dalam Perjalanan");
        }
        else if (ch == 'n' || ch == 'N') {
            strcpy(temp, "Tidak Aktif");
        }
        else {
            continue;
        }

        // tampilkan pilihan
        gotoxy(col, row);
        printf("%-20s", temp);
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
        gotoxy(37, 29);
        printf("Kategori     : ");

        gotoxy(37, 30);
        printf("(E=Ekonomi  B=Bisnis  X=Executive)");

        setPointer(29, 53);
        inputKategoriKendaraan(data.kategori, 29, 52);

        if (strlen(data.kategori) == 0) {
        fclose(fp);
        return;
        }

        // hapus keterangan setelah dipilih
        clearArea(37, 30, 60, 1);

        // ===== KAPASITAS =====
        gotoxy(37, 30); printf("Kapasitas    : ");
        setPointer(30, 53);
        inputKapasitas2Digit(data.kapasitas, 30, 52);
        if (strlen(data.kapasitas) == 0) {
            fclose(fp);
            return;
        }

        // ===== FASILITAS =====
        gotoxy(37, 31); printf("Fasilitas    : ");
        setPointer(32, 53);
        inputFasilitas(data.fasilitas, 31, 52);
        if (strlen(data.fasilitas) == 0) {
            fclose(fp);
            return;
        }

        // ===== NAMA ARMADA =====
        gotoxy(37, 32); printf("Nama Armada  : ");
        setPointer(33, 53);
        inputNamaArmada(data.nama_armada, 32, 52);
        if (strlen(data.nama_armada) == 0) {
            fclose(fp);
            return;
        }

        // ===== TAHUN =====
        gotoxy(37, 33); printf("Tahun        : ");
        setPointer(34, 53);
        inputTahun(data.tahun, 33, 52);
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

        // ===== STATUS =====
        gotoxy(37, 34);
        printf("Status       : ");

        gotoxy(37, 35);
        printf("(T=Tersedia  M=Maintenance  D=Perjalanan  N=Tidak aktif)");

        setPointer(34, 52);
        inputStatusKendaraan(data.status, 34, 52);

        if (strlen(data.status) == 0) {
            fclose(fp);
            return;
        }

        // hapus keterangan status setelah dipilih
        clearArea(37, 35, 80, 1);

        // ===== SIMPAN =====
        fwrite(&data, sizeof(Kendaraan), 1, fp);
        fclose(fp);

        gotoxy(37, 36);
        printf("Data kendaraan berhasil dibuat!");

        gotoxy(37, 37);
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
        "Executive"
    };

    char *kapasitas[] = {
        "25", "30", "35", "40", "45", "50"
    };

    char *fasilitas[] = {
        "AC",
        "AC, Reclining Seat",
        "AC, Reclining Seat, Toilet",
        "AC, TV, USB Charger",
        "AC, Toilet, WiFi"
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

    char *tahun[] = {
        "2018", "2019", "2020", "2021", "2022", "2023", "2024", "2025"
    };

    char *status[] = {
        "Tersedia",
        "Tersedia",
        "Tersedia",
        "Dalam Perjalanan",
        "Maintenance"
    };

    int nKategori  = sizeof(kategori) / sizeof(kategori[0]);
    int nKapasitas = sizeof(kapasitas) / sizeof(kapasitas[0]);
    int nFasilitas = sizeof(fasilitas) / sizeof(fasilitas[0]);
    int nArmada    = sizeof(nama_armada) / sizeof(nama_armada[0]);
    int nTahun     = sizeof(tahun) / sizeof(tahun[0]);
    int nStatus    = sizeof(status) / sizeof(status[0]);

    // ===== BUAT / RESET FILE =====
    fp = fopen("kendaraan.dat", "wb");
    if (fp == NULL) {
        printf("ERROR: Gagal membuat file kendaraan.dat\n");
        getch();
        return;
    }

    printf("     MEMBUAT DATA DUMMY KENDARAAN\n");

    for (int i = 0; i < max_data; i++) {
        // INISIALISASI MEMORI STRUCT DULU
        memset(&data, 0, sizeof(Kendaraan));

        // ID OTOMATIS
        sprintf(data.id_kendaraan, "KND%03d", i + 1);

        // ISI DATA (DI-ROTASI BIAR BERVARIASI)
        strcpy(data.kategori,  kategori[i % nKategori]);
        strcpy(data.kapasitas, kapasitas[i % nKapasitas]);
        strcpy(data.fasilitas, fasilitas[i % nFasilitas]);
        strcpy(data.tahun,     tahun[i % nTahun]);
        strcpy(data.status,    status[i % nStatus]);

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