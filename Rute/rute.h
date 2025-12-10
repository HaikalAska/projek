//
// Created by yoyop on 08/12/2025.
//

#ifndef PROJEK_RUTE_H
#define PROJEK_RUTE_H
#include "../FrameTabel.h"
#include <stdio.h>
#include "../PesanTiket.h"
#include "../Menu.h"
#include <string.h>
#include <conio.h>

// Struktur data untuk rute bus
typedef struct {
    char kode_rute[10];
    char posisi_awal[50];
    char tujuan_akhir[50];
    int harga;
    int jarak; // dalam km
    char waktu_tempuh[20]; // contoh: "4 jam"
} RuteBus;

void tampilkanSemuaRute();
void tambahRuteBaru();
void editRute();
void hapusRute();
void cariRute();

// Array untuk menyimpan rute-rute
RuteBus daftarRute[100];
int jumlahRute = 0;

// Fungsi untuk membuat tampilan rute
void buatrute(){
    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);
    gotoxy(8,5); printf("Kelompok 5");
}

// Fungsi untuk menampilkan menu admin rute
void menuAdminRute() {
    int pilihan;
    int pilih;
    do {
        clearscreen();
        fillBackground(0x90);
        printBorder(1, 1, 153, 43);
        FrameYangTengah(31, 1, 43);
        FrameYangHider(1,9,153);

        // Header
        gotoxy(3, 11); printf("==========================");
        gotoxy(3, 12); printf("    MANAJEMEN RUTE BUS    ");
        gotoxy(3, 13); printf("==========================");

        // Menu pilihan
        gotoxy(3, 15); printf("   Lihat Semua Rute");
        gotoxy(3, 17); printf("   Tambah Rute Baru");
        gotoxy(3, 19); printf("   Edit Rute");
        gotoxy(3, 21); printf("   Hapus Rute");
        gotoxy(3, 23); printf("   Cari Rute");
        gotoxy(3, 25); printf("   Kembali ke Menu Utama");
        pilih = menuNavigasi(6,15,3);

        // gotoxy(55, 22); printf("Pilihan Anda: ");
        // scanf("%d", &pilihan);
        // fflush(stdin);

        switch(pilihan) {
            case 1:
                tampilkanSemuaRute();
                break;
            case 2:
                tambahRuteBaru();
                break;
            case 3:
                editRute();
                break;
            case 4:
                hapusRute();
                break;
            case 5:
                cariRute();
                break;
            case 0:
                return;
            default:
                gotoxy(55, 25); printf("Pilihan tidak valid!");
                getch();
        }
    } while (pilihan != 0);
}

// Fungsi untuk menampilkan semua rute
void tampilkanSemuaRute() {
    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);
    gotoxy(8,5); printf("Kelompok 5");

    gotoxy(60, 3); printf("==========================");
    gotoxy(60, 4); printf("       DAFTAR RUTE BUS    ");
    gotoxy(60, 5); printf("==========================");

    if (jumlahRute == 0) {
        gotoxy(55, 10); printf("Belum ada data rute!");
        gotoxy(55, 12); printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }

    // Header tabel
    gotoxy(10, 8); printf("========================================================================================================");
    gotoxy(10, 9); printf("| No | Kode Rute | Posisi Awal      | Tujuan Akhir     | Harga     | Jarak  | Waktu Tempuh |");
    gotoxy(10, 10); printf("========================================================================================================");

    // Menampilkan data
    for (int i = 0; i < jumlahRute; i++) {
        gotoxy(10, 11 + i);
        printf("| %-2d | %-9s | %-16s | %-16s | Rp %-6d | %-5d km | %-12s |",
               i + 1,
               daftarRute[i].kode_rute,
               daftarRute[i].posisi_awal,
               daftarRute[i].tujuan_akhir,
               daftarRute[i].harga,
               daftarRute[i].jarak,
               daftarRute[i].waktu_tempuh);
    }

    gotoxy(10, 11 + jumlahRute);
    printf("========================================================================================================");

    gotoxy(10, 13 + jumlahRute);
    printf("Tekan Enter untuk kembali...");
    getch();
}

// Fungsi untuk menambah rute baru
void tambahRuteBaru() {
    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);
    gotoxy(8,5); printf("Kelompok 5");

    gotoxy(3, 3); printf("==========================");
    gotoxy(3, 4); printf("      TAMBAH RUTE BARU    ");
    gotoxy(3, 5); printf("==========================");

    gotoxy(3, 8); printf("Masukkan data rute baru:");

    gotoxy(50, 10); printf("Kode Rute      : ");
    gotoxy(50, 12); printf("Posisi Awal    : ");
    gotoxy(50, 14); printf("Tujuan Akhir   : ");
    gotoxy(50, 16); printf("Harga (Rp)     : ");
    gotoxy(50, 18); printf("Jarak (km)     : ");
    gotoxy(50, 20); printf("Waktu Tempuh   : ");

    // Ambil input dari user
    gotoxy(68, 10); scanf("%s", daftarRute[jumlahRute].kode_rute);
    fflush(stdin);
    gotoxy(68, 12); scanf("%[^\n]", daftarRute[jumlahRute].posisi_awal);
    fflush(stdin);
    gotoxy(68, 14); scanf("%[^\n]", daftarRute[jumlahRute].tujuan_akhir);
    fflush(stdin);
    gotoxy(68, 16); scanf("%d", &daftarRute[jumlahRute].harga);
    fflush(stdin);
    gotoxy(68, 18); scanf("%d", &daftarRute[jumlahRute].jarak);
    fflush(stdin);
    gotoxy(68, 20); scanf("%[^\n]", daftarRute[jumlahRute].waktu_tempuh);
    fflush(stdin);

    jumlahRute++;

    gotoxy(50, 25); printf("Rute berhasil ditambahkan!");
    gotoxy(50, 26); printf("Tekan Enter untuk kembali...");
    getch();
}

// Fungsi utama untuk edit rute (yang diminta)
void editRute() {
    char kodeCari[10];
    int found = 0;
    int index = -1;

    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);

    gotoxy(60, 3); printf("==========================");
    gotoxy(60, 4); printf("         EDIT RUTE        ");
    gotoxy(60, 5); printf("==========================");

    // Tampilkan dulu semua rute yang ada
    gotoxy(50, 8); printf("Daftar Rute yang Tersedia:");

    if (jumlahRute == 0) {
        gotoxy(50, 10); printf("Belum ada data rute untuk diedit!");
        gotoxy(50, 12); printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }

    // Tampilkan list singkat
    for (int i = 0; i < jumlahRute; i++) {
        gotoxy(45, 10 + i);
        printf("%d. %s: %s -> %s (Rp %d)",
               i + 1,
               daftarRute[i].kode_rute,
               daftarRute[i].posisi_awal,
               daftarRute[i].tujuan_akhir,
               daftarRute[i].harga);
    }

    // Minta input kode rute yang akan diedit
    gotoxy(45, 12 + jumlahRute);
    printf("Masukkan kode rute yang akan diedit: ");
    scanf("%s", kodeCari);
    fflush(stdin);

    // Cari rute berdasarkan kode
    for (int i = 0; i < jumlahRute; i++) {
        if (strcmp(daftarRute[i].kode_rute, kodeCari) == 0) {
            found = 1;
            index = i;
            break;
        }
    }

    if (!found) {
        gotoxy(45, 14 + jumlahRute);
        printf("Rute dengan kode %s tidak ditemukan!", kodeCari);
        gotoxy(45, 15 + jumlahRute);
        printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }

    // Tampilkan data rute yang akan diedit
    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);

    gotoxy(60, 3); printf("==========================");
    gotoxy(60, 4); printf("         EDIT RUTE        ");
    gotoxy(60, 5); printf("==========================");

    gotoxy(50, 8); printf("Rute yang akan diedit:");
    gotoxy(50, 9); printf("========================");

    gotoxy(45, 11); printf("Kode Rute      : %s", daftarRute[index].kode_rute);
    gotoxy(45, 12); printf("Posisi Awal    : %s", daftarRute[index].posisi_awal);
    gotoxy(45, 13); printf("Tujuan Akhir   : %s", daftarRute[index].tujuan_akhir);
    gotoxy(45, 14); printf("Harga          : Rp %d", daftarRute[index].harga);
    gotoxy(45, 15); printf("Jarak          : %d km", daftarRute[index].jarak);
    gotoxy(45, 16); printf("Waktu Tempuh   : %s", daftarRute[index].waktu_tempuh);

    // Menu edit
    gotoxy(50, 19); printf("Apa yang ingin diedit?");
    gotoxy(45, 21); printf("1. Edit Posisi Awal");
    gotoxy(45, 22); printf("2. Edit Tujuan Akhir");
    gotoxy(45, 23); printf("3. Edit Harga");
    gotoxy(45, 24); printf("4. Edit Jarak");
    gotoxy(45, 25); printf("5. Edit Waktu Tempuh");
    gotoxy(45, 26); printf("6. Edit Semua Data");
    gotoxy(45, 27); printf("0. Batal");

    int pilihanEdit;
    gotoxy(45, 29); printf("Pilihan: ");
    scanf("%d", &pilihanEdit);
    fflush(stdin);

    switch(pilihanEdit) {
        case 1:
            gotoxy(45, 31); printf("Posisi Awal Baru: ");
            scanf("%[^\n]", daftarRute[index].posisi_awal);
            fflush(stdin);
            break;
        case 2:
            gotoxy(45, 31); printf("Tujuan Akhir Baru: ");
            scanf("%[^\n]", daftarRute[index].tujuan_akhir);
            fflush(stdin);
            break;
        case 3:
            gotoxy(45, 31); printf("Harga Baru (Rp): ");
            scanf("%d", &daftarRute[index].harga);
            fflush(stdin);
            break;
        case 4:
            gotoxy(45, 31); printf("Jarak Baru (km): ");
            scanf("%d", &daftarRute[index].jarak);
            fflush(stdin);
            break;
        case 5:
            gotoxy(45, 31); printf("Waktu Tempuh Baru: ");
            scanf("%[^\n]", daftarRute[index].waktu_tempuh);
            fflush(stdin);
            break;
        case 6:
            gotoxy(45, 31); printf("Posisi Awal Baru    : ");
            scanf("%[^\n]", daftarRute[index].posisi_awal);
            fflush(stdin);
            gotoxy(45, 32); printf("Tujuan Akhir Baru   : ");
            scanf("%[^\n]", daftarRute[index].tujuan_akhir);
            fflush(stdin);
            gotoxy(45, 33); printf("Harga Baru (Rp)     : ");
            scanf("%d", &daftarRute[index].harga);
            fflush(stdin);
            gotoxy(45, 34); printf("Jarak Baru (km)     : ");
            scanf("%d", &daftarRute[index].jarak);
            fflush(stdin);
            gotoxy(45, 35); printf("Waktu Tempuh Baru   : ");
            scanf("%[^\n]", daftarRute[index].waktu_tempuh);
            fflush(stdin);
            break;
        case 0:
            gotoxy(45, 31); printf("Edit dibatalkan!");
            break;
        default:
            gotoxy(45, 31); printf("Pilihan tidak valid!");
    }

    if (pilihanEdit >= 1 && pilihanEdit <= 6) {
        gotoxy(45, 37); printf("Data rute berhasil diperbarui!");
    }

    gotoxy(45, 39); printf("Tekan Enter untuk kembali...");
    getch();
}

// Fungsi untuk menghapus rute
void hapusRute() {
    char kodeCari[10];
    int found = 0;

    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);

    gotoxy(60, 3); printf("==========================");
    gotoxy(60, 4); printf("        HAPUS RUTE        ");
    gotoxy(60, 5); printf("==========================");

    if (jumlahRute == 0) {
        gotoxy(50, 10); printf("Belum ada data rute!");
        gotoxy(50, 12); printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }

    gotoxy(50, 8); printf("Masukkan kode rute yang akan dihapus: ");
    scanf("%s", kodeCari);
    fflush(stdin);

    // Cari dan hapus rute
    for (int i = 0; i < jumlahRute; i++) {
        if (strcmp(daftarRute[i].kode_rute, kodeCari) == 0) {
            found = 1;
            // Geser semua data setelah index i
            for (int j = i; j < jumlahRute - 1; j++) {
                daftarRute[j] = daftarRute[j + 1];
            }
            jumlahRute--;
            break;
        }
    }

    if (found) {
        gotoxy(50, 12); printf("Rute dengan kode %s berhasil dihapus!", kodeCari);
    } else {
        gotoxy(50, 12); printf("Rute dengan kode %s tidak ditemukan!", kodeCari);
    }

    gotoxy(50, 14); printf("Tekan Enter untuk kembali...");
    getch();
}

// Fungsi untuk mencari rute
void cariRute() {
    char keyword[50];
    int found = 0;

    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);

    gotoxy(60, 3); printf("==========================");
    gotoxy(60, 4); printf("         CARI RUTE        ");
    gotoxy(60, 5); printf("==========================");

    gotoxy(50, 8); printf("Masukkan kata kunci (kode/posisi/tujuan): ");
    scanf("%[^\n]", keyword);
    fflush(stdin);

    // Header hasil pencarian
    gotoxy(10, 12); printf("========================================================================================================");
    gotoxy(10, 13); printf("| Kode Rute | Posisi Awal      | Tujuan Akhir     | Harga     | Jarak  | Waktu Tempuh |");
    gotoxy(10, 14); printf("========================================================================================================");

    int row = 15;
    for (int i = 0; i < jumlahRute; i++) {
        // Cari di semua field
        if (strstr(daftarRute[i].kode_rute, keyword) != NULL ||
            strstr(daftarRute[i].posisi_awal, keyword) != NULL ||
            strstr(daftarRute[i].tujuan_akhir, keyword) != NULL) {

            gotoxy(10, row);
            printf("| %-9s | %-16s | %-16s | Rp %-6d | %-5d km | %-12s |",
                   daftarRute[i].kode_rute,
                   daftarRute[i].posisi_awal,
                   daftarRute[i].tujuan_akhir,
                   daftarRute[i].harga,
                   daftarRute[i].jarak,
                   daftarRute[i].waktu_tempuh);
            row++;
            found = 1;
        }
    }

    if (!found) {
        gotoxy(50, 12); printf("Rute tidak ditemukan!");
    }

    gotoxy(10, row); printf("========================================================================================================");

    gotoxy(10, row + 2); printf("Tekan Enter untuk kembali...");
    getch();
}

#endif //PROJEK_RUTE_H