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
    char plat_nomor[20];
} Kendaraan;

int getTahunSekarang();

static int getKendaraanCount() {
    FILE *fp = fopen("kendaraan.dat", "rb");
    if (!fp) return 0;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);

    return size / sizeof(Kendaraan);
}

void generatePlatNomor(char *plat) {
    const char huruf[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // random huruf depan (2 huruf)
    char h1 = huruf[rand() % 26];
    char h2 = huruf[rand() % 26];

    // random angka 4 digit (1000 - 9999)
    int angka = rand() % 9000 + 1000;

    // random huruf belakang (3 huruf)
    char h3 = huruf[rand() % 26];
    char h4 = huruf[rand() % 26];
    char h5 = huruf[rand() % 26];

    sprintf(plat, "%c%c %04d %c%c%c",
            h1, h2, angka, h3, h4, h5);
}



// ================= FUNGSI TAMPILKAN DETAIL KATEGORI (DALAM KOTAK) =================
static void tampilkanDetailKategori(int pilihan) {
    // Bersihkan area detail
    clearArea(105, 31, 32, 9);

    if (pilihan == 0) {  // Ekonomi
        gotoxy(105, 31); printf("Kategori  : Ekonomi");
        gotoxy(105, 32); printf("Kapasitas : 60 orang");
        gotoxy(105, 33); printf("Fasilitas :");
        gotoxy(105, 34); printf("- AC");
    }
    else if (pilihan == 1) {  // Bisnis
        gotoxy(105, 31); printf("Kategori  : Bisnis");
        gotoxy(105, 32); printf("Kapasitas : 40 orang");
        gotoxy(105, 33); printf("Fasilitas :");
        gotoxy(105, 34); printf("- AC");
        gotoxy(105, 35); printf("- Stopcontact");
        gotoxy(105, 36); printf("- Toilet");
    }
    else if (pilihan == 2) {  // Executive
        gotoxy(105, 31); printf("Kategori  : Executive");
        gotoxy(105, 32); printf("Kapasitas : 40 orang");
        gotoxy(105, 33); printf("Fasilitas :");
        gotoxy(105, 34); printf("- AC");
        gotoxy(105, 35); printf("- Camilan");
        gotoxy(105, 36); printf("- TV");
        gotoxy(105, 37); printf("- Toilet");
    }
}

// ================= FUNGSI NAVIGASI KATEGORI =================
static int rutenavigasiKategoriDalamKotak(int x, int y, int jumlah_pilihan, int spasi) {
    int pilihan = 0;
    int ch;

    // Tampilkan detail awal
    tampilkanDetailKategori(pilihan);

    while (1) {
        // Tampilkan panah untuk semua pilihan
        for (int i = 0; i < jumlah_pilihan; i++) {
            gotoxy(x, y + (i * spasi));
            if (i == pilihan) {
                printf(">>");
            } else {
                printf("  ");
            }
        }

        ch = _getch();

        // Arrow keys
        if (ch == 0 || ch == 224) {
            ch = _getch();

            if (ch == 72) {  // Arrow UP
                pilihan--;
                if (pilihan < 0) {
                    pilihan = jumlah_pilihan - 1;
                }
                tampilkanDetailKategori(pilihan);
            }
            else if (ch == 80) {  // Arrow DOWN
                pilihan++;
                if (pilihan >= jumlah_pilihan) {
                    pilihan = 0;
                }
                tampilkanDetailKategori(pilihan);
            }
        }
        // ENTER
        else if (ch == 13) {
            return pilihan;
        }
        // ESC
        else if (ch == 27) {
            return -1;
        }
    }
}

// ================= INPUT KATEGORI DENGAN KOTAK KECIL =================
static void inputKategoriKendaraanDenganPreview(char *kategori, char *kapasitas, char *fasilitas, int row, int col) {
    int pilih;

    // ===== KOTAK KIRI - MENU KATEGORI (18 karakter lebar) =====
    bentukframe(84, 30, 18, 11);
    gotoxy(85, 30);
    printf("[ PILIH KATEGORI ]");

    gotoxy(87, 32); printf("Ekonomi");
    gotoxy(87, 34); printf("Bisnis");
    gotoxy(87, 36); printf("Executive");

    gotoxy(85, 38);
    printf("[\xE2\x86\x91 \xE2\x86\x93] Navigasi", 24, 25);  // ↑↓
    gotoxy(85, 39);
    printf("[Enter] Pilih");

    // ===== KOTAK KANAN - DETAIL KATEGORI (35 karakter lebar) =====
    bentukframe(103, 30, 35, 11);
    gotoxy(115, 30);
    printf("[ DETAIL ]");

    // Navigasi dengan preview (3 pilihan dengan jarak 2 baris)
    pilih = rutenavigasiKategoriDalamKotak(85, 32, 3, 2);

    // Bersihkan kedua kotak setelah selesai
    clearArea(83, 29, 57, 13);

    // Set data berdasarkan pilihan
    if (pilih == 0) {  // Ekonomi
        strcpy(kategori, "Ekonomi");
        strcpy(kapasitas, "60");
        strcpy(fasilitas, "AC");
    }
    else if (pilih == 1) {  // Bisnis
        strcpy(kategori, "Bisnis");
        strcpy(kapasitas, "40");
        strcpy(fasilitas, "AC, Stopcontact, Toilet");
    }
    else if (pilih == 2) {  // Executive
        strcpy(kategori, "Executive");
        strcpy(kapasitas, "40");
        strcpy(fasilitas, "AC, Camilan, TV, Toilet");
    }
    else {  // ESC ditekan
        kategori[0] = '\0';
        kapasitas[0] = '\0';
        fasilitas[0] = '\0';
        return;
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
        else if (ch == 8) {  // BACKSPACE
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

    int tahunSekarang = getTahunSekarang();
    int tahunMinimal  = tahunSekarang - 10;

    while (1) {
        ch = getch();

        if (ch == 13) {  // ENTER
            temp[i] = '\0';

            // ===== VALIDASI KOSONG =====
            if (i == 0) {
                gotoxy(col, row);
                printf("Tahun harus diisi");
                Sleep(800);

                gotoxy(col, row);
                printf("%-25s", " ");
                gotoxy(col, row);
                continue;
            }

            // ===== VALIDASI 4 DIGIT =====
            if (i != 4) {
                gotoxy(col, row);
                printf("[Harus 4 digit]");
                Sleep(800);

                gotoxy(col, row);
                printf("%-25s", " ");
                gotoxy(col, row);

                i = 0;
                continue;
            }

            int tahunInput = atoi(temp);

            // ===== VALIDASI RANGE TAHUN =====
            if (tahunInput < tahunMinimal || tahunInput > tahunSekarang) {
                gotoxy(col, row);
                printf("[Tahun %d - %d]", tahunMinimal, tahunSekarang);
                Sleep(1000);

                gotoxy(col, row);
                printf("%-30s", " ");
                gotoxy(col, row);

                i = 0;
                continue;
            }

            // ===== VALID =====
            strcpy(tahun, temp);
            return;
        }
        else if (ch == 27) {  // ESC
            tahun[0] = '\0';
            return;
        }
        else if (ch == 8) {   // BACKSPACE
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
                gotoxy(col, row);
                printf("Input A / N");
                Sleep(800);
                gotoxy(col, row);
                printf("%-20s", " ");
                gotoxy(col, row);
                continue;
            }

            strcpy(status, temp);
            return;
        }

        // ===== ESC =====
        if (ch == 27) {
            status[0] = '\0';   // penanda batal
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

        // ===== PILIH STATUS =====
        if (ch == 'a' || ch == 'A') {
            strcpy(temp, "Aktif");
        }
        else if (ch == 'n' || ch == 'N') {
            strcpy(temp, "Nonaktif");
        }
        else {
            continue;
        }

        // tampilkan status
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
        gotoxy(78, 27);
        printf("=== TAMBAH KENDARAAN ===");

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
        printf("Kategori     : [Tekan Enter untuk pilih]");

        inputKategoriKendaraanDenganPreview(
            data.kategori,
            data.kapasitas,
            data.fasilitas,
            29, 52
        );

        if (strlen(data.kategori) == 0) {
            fclose(fp);
            clearArea(35, 28, 108, 15);
            return;
        }

        // ===== REDRAW FRAME =====
        bentukframe(35, 27, 108, 16);
        gotoxy(78, 27);
        printf("=== TAMBAH KENDARAAN ===");

        gotoxy(37, 28);
        printf("ID Kendaraan : %s", data.id_kendaraan);

        gotoxy(37, 29);
        printf("Kategori     : %-30s", data.kategori);

        gotoxy(37, 30);
        printf("Kapasitas    : %s orang", data.kapasitas);

        gotoxy(37, 31);
        printf("Fasilitas    : %s", data.fasilitas);

        // ===== NAMA ARMADA =====
        gotoxy(37, 32);
        printf("Nama Armada  : ");
        setPointer(33, 53);
        inputNamaArmada(data.nama_armada, 32, 52);

        if (strlen(data.nama_armada) == 0) {
            fclose(fp);
            clearArea(35, 28, 108, 15);
            return;
        }
        srand(time(NULL));
        gotoxy(37, 33);
        printf("Nomor Kendaraan : ");

        generatePlatNomor(data.plat_nomor);

        gotoxy(55, 33);
        printf("%s", data.plat_nomor);


        // ===== INPUT TAHUN =====
        gotoxy(37, 34);
        printf("Tahun        : ");
        setPointer(35, 53);
        inputTahun(data.tahun, 34, 52);

        if (strlen(data.tahun) == 0) {
            fclose(fp);
            clearArea(35, 28, 108, 15);
            return;
        }

        // ===== HITUNG UMUR BUS =====
        int tahunSekarang = getTahunSekarang();
        int tahunBus = atoi(data.tahun);
        int umur = tahunSekarang - tahunBus;

        gotoxy(58, 34);
        if (umur > 10) {
            printf("[Tidak Layak | Umur %d th]", umur);
        } else {
            printf("[Layak | Umur %d th]", umur);
        }

        // ===== STATUS OTOMATIS =====
        gotoxy(37, 35);
        printf("Status       : ");

        if (umur > 10) {
            strcpy(data.status, "Tidak Aktif");
            gotoxy(52, 35);
            printf("Tidak Aktif");
        } else {
            strcpy(data.status, "Aktif");
            gotoxy(52, 35);
            printf("Aktif");
        }

        // ===== SIMPAN DATA =====
        fwrite(&data, sizeof(Kendaraan), 1, fp);
        fclose(fp);

        gotoxy(37, 37);
        printf("Data kendaraan berhasil dibuat!");

        gotoxy(37, 38);
        printf("Tambah lagi? (y/n): ");

        while (1) {
            n = _getch();

            if (n == 27) { // ESC
                clearArea(35, 28, 108, 15);
                return;
            }

            if (n == 'y' || n == 'Y' || n == 'n' || n == 'N') {
                clearArea(35, 28, 108, 15);
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

    srand(time(NULL)); // ⬅️ penting untuk random

    // ===== CONTOH DATA =====
    char *kategori[] = {
        "Ekonomi",
        "Bisnis",
        "Eksekutif"
    };

    char *nama_armada[] = {
        "PO Sinar Jaya",
        "PO Rosalia Indah",
        "PO Harapan Jaya",
        "PO Pahala Kencana",
        "PO Gunung Harta",
        "PO Sumber Alam",
        "PO Lorena",
        "PO Agramas"
    };

    char *tahun[] = {
        "2018", "2019", "2020", "2021", "2022", "2023", "2024", "2025"
    };

    char *status[] = {
        "Aktif",
        // "Nonaktif"
    };

    int nKategori = sizeof(kategori) / sizeof(kategori[0]);
    int nArmada   = sizeof(nama_armada) / sizeof(nama_armada[0]);
    int nTahun    = sizeof(tahun) / sizeof(tahun[0]);
    int nStatus   = sizeof(status) / sizeof(status[0]);

    // ===== BUAT / RESET FILE =====
    fp = fopen("kendaraan.dat", "wb");
    if (!fp) {
        printf("ERROR: Gagal membuat file kendaraan.dat\n");
        getch();
        return;
    }

    printf("     MEMBUAT DATA DUMMY KENDARAAN\n");

    for (int i = 0; i < max_data; i++) {
        memset(&data, 0, sizeof(Kendaraan));

        // ID
        sprintf(data.id_kendaraan, "KND%03d", i + 1);

        // KATEGORI
        strcpy(data.kategori, kategori[i % nKategori]);

        // KAPASITAS & FASILITAS
        if (strcmp(data.kategori, "Ekonomi") == 0) {
            strcpy(data.kapasitas, "60");
            strcpy(data.fasilitas, "AC");
        }
        else if (strcmp(data.kategori, "Bisnis") == 0) {
            strcpy(data.kapasitas, "40");
            strcpy(data.fasilitas, "AC, Stopcontact, Toilet");
        }
        else {
            strcpy(data.kapasitas, "40");
            strcpy(data.fasilitas, "AC, Camilan, TV, Toilet");
        }

        // NAMA ARMADA
        strcpy(data.nama_armada, nama_armada[i % nArmada]);

        // TAHUN
        strcpy(data.tahun, tahun[i % nTahun]);

        // STATUS (Aktif / Nonaktif)
        strcpy(data.status, status[i % nStatus]);

        // PLAT NOMOR OTOMATIS
        generatePlatNomor(data.plat_nomor);

        fwrite(&data, sizeof(Kendaraan), 1, fp);
    }

    fclose(fp);

    printf("\n[✓] Berhasil membuat %d data dummy kendaraan\n", max_data);
    printf("Tekan tombol apapun untuk kembali...");
    getch();
}


#endif // PROJEK_CREATEKENDARAAN_H