#ifndef PROJEK_BATALTIKET_H
#define PROJEK_BATALTIKET_H

#include "../FrameTabel.h"
#include <time.h>
//#include "readtiket.h"
#include "../Pemesanan/Pesantiket.h"

// ================= STRUCT (SAMA PERSIS DENGAN CREATETIKET.H) =================


// ================= STRUCT UNTUK MENYIMPAN DATA PEMBATALAN =================
typedef struct {
    char id_pembatalan[10];
    char id_tiket[20];
    char id_penumpang[20];
    char nama_penumpang[50];
    char tanggal_pembatalan[15];
    long refund;
    long metode_pengembalian;
    long hargaTbatal;
    char tanggal_booking [15];
} DataPembatalan;

static void inputIDTiketBatal(char *id, int x, int y);
static void generateIDPembatalan(char *id_pembatalan);
static void getTanggalSekarang(char *tanggal);
static void generateIDPembatalan(char *id_pembatalan);
static void getTanggalSekarang(char *tanggal);
static void inputIDTiketBatal(char *id, int x, int y);


// ================= BATAL TIKET =================
void BatalTiket() {
    char n;

    do {
        system("chcp 65001 > nul");
        fillBackground(0x90);
        bentukframe(2, 1, 30, 45);
        bentukframe(34, 1, 121, 10);
        bentukframe(3, 4, 27, 3);
        tampilanlogin("GAMBARASCI.txt", 60, 3);
        gotoxy(8,5); printf("Kelompok 5");
        bentukframe(3, 29, 27, 10);
        gotoxy(5,30); printf("=== MENU NAVIGASI ===");
        gotoxy(4,32); printf("NAVIGASI [↑ ↓]");
        gotoxy(4,34); printf("[ENTER] Pilih");
        gotoxy(4,36); printf("[ESC] Keluar");
        readTiketPenumpang();


        FILE *fp_tiket = fopen("tiket.dat", "rb");
        if (!fp_tiket) {
            bentukframe(35, 27, 108, 5);
            gotoxy(75, 27); printf("=== BATALKAN TIKET ===");
            gotoxy(37, 29);
            printf("Belum ada data tiket!");
            gotoxy(37, 30);
            printf("Silakan pesan tiket terlebih dahulu.");
            getch();
            return;
        }
        fclose(fp_tiket);

        // ================= TUNGGU ENTER =================
        char key;
        while (1) {
            key = getch();

            // ESC - Keluar
            if (key == 27) {
                return;
            }

            // ENTER
            if (key == 13) {
                break;
            }
        }


        bentukframe(35, 27, 108, 18);
        gotoxy(75, 27); printf("=== BATALKAN TIKET ===");

        tiket data;
        char id_cari[20];
        char id_pembatalan[10];
        char tanggal_pembatalan[15];

        generateIDPembatalan(id_pembatalan);
        getTanggalSekarang(tanggal_pembatalan);
        gotoxy(37, 28); printf("ID Pembatalan  : %s", id_pembatalan);
        gotoxy(37, 29); printf("Tanggal Batal  : %s", tanggal_pembatalan);
        gotoxy(37, 30); printf("ID Tiket       : ");
        inputIDTiketBatal(id_cari, 54, 30);


        if (strlen(id_cari) == 0) {
            return;
        }

        // ================= CARI TIKET =================
        fp_tiket = fopen("tiket.dat", "rb");

        int found = 0;
        while (fread(&data, sizeof(tiket), 1, fp_tiket)) {
            if (strcmp(data.id_tiket, id_cari) == 0) {
                found = 1;
                break;
            }
        }
        fclose(fp_tiket);

        if (!found) {
            gotoxy(37, 31);
            printf("Tiket dengan ID '%s' tidak ditemukan!", id_cari);
            getch();
            clearArea(35, 27, 80, 18);
            continue;
        }


        // ================= TAMPILKAN DATA TIKET =================
        gotoxy(37, 31); printf("ID Penumpang   : %s", data.id_penumpang);
        gotoxy(37, 32); printf("Nama Penumpang : %s", data.nama_penumpang);
        gotoxy(37, 33); printf("No. Telepon    : %s", data.notlpn);
        gotoxy(37, 34); printf("Email          : %s", data.Email);
        gotoxy(37, 35); printf("Rute           : %s → %s", data.rute_awal, data.tujuan);
        gotoxy(37, 36); printf("Armada         : %s", data.nama_armada);
        gotoxy(37, 37); printf("Berangkat      : %s | %s", data.tanggal_berangkat, data.jam_berangkat);
        gotoxy(37, 38); printf("Harga          : ");
        tampilanhargatiket(data.harga);
        gotoxy(37, 39); printf("Metode Bayar   : %s", data.metode_bayar);



        // ================= PILIH METODE PENGEMBALIAN =================
        bentukframe(87, 34, 36, 10);
        gotoxy(93, 35); printf("METODE PENGEMBALIAN DANA");

        gotoxy(90, 37); printf("Refund 70%%     : ");
        tampilanhargatiket(data.harga * 0.7);

        long metode_pengembalian; // 1 = Tunai, 2 = Non Tunai
        char pilihan_refund;

        gotoxy(90, 39); printf("Pilih metode pengembalian:");
        gotoxy(90, 40); printf("(T) Tunai");
        gotoxy(90, 41); printf("(N) Non Tunai");
        gotoxy(90, 42); printf("Pilihan Anda   : ");

        // Loop untuk validasi input metode pengembalian
        while (1) {
            pilihan_refund = getch();

            // ESC - Keluar
            if (pilihan_refund == 27) {
                clearArea(35, 27, 80, 18);
                return;
            }

            // T atau t untuk Tunai
            if (pilihan_refund == 'T' || pilihan_refund == 't') {
                metode_pengembalian = 1; // 1 = Tunai
                gotoxy(109, 42); printf("T");
                break;
            }

            // N atau n untuk Non Tunai
            if (pilihan_refund == 'N' || pilihan_refund == 'n') {
                metode_pengembalian = 2; // 2 = Non Tunai
                gotoxy(109, 42); printf("N");
                break;
            }
        }

        // ================= KONFIRMASI PEMBATALAN =================
        clearArea(90, 37, 30, 6);
        gotoxy(90, 37); printf("Metode Refund  : %s",
            (metode_pengembalian == 1) ? "Tunai" : "Non Tunai");
        gotoxy(90, 38); printf("Refund 70%%     : ");
        tampilanhargatiket(data.harga * 0.7);

        gotoxy(90, 40); printf("Batalkan tiket ini?");
        gotoxy(90, 41); printf("(Y) Ya  (N) Tidak : ");

        char confirm;
        while (1) {
            confirm = getch();

            // ESC
            if (confirm == 27) {
                clearArea(35, 27, 80, 18);
                return;
            }

            // YA - PROSES PEMBATALAN
            if (confirm == 'Y' || confirm == 'y') {

                FILE *fp_read = fopen("tiket.dat", "rb");
                FILE *fp_temp = fopen("temp.dat", "wb");
                FILE *fp_log   = fopen("pembatalan.dat", "ab");

                if (!fp_read || !fp_temp || !fp_log) {
                    if (fp_read) fclose(fp_read);
                    if (fp_temp) fclose(fp_temp);
                    if (fp_log) fclose(fp_log);
                    return;
                }

                tiket temp_data;

                while (fread(&temp_data, sizeof(tiket), 1, fp_read)) {
                    if (strcmp(temp_data.id_tiket, id_cari) != 0) {
                        fwrite(&temp_data, sizeof(tiket), 1, fp_temp);
                    }
                }

                fclose(fp_read);
                fclose(fp_temp);

                // ===== SIMPAN DATA PEMBATALAN =====
                DataPembatalan data_batal;

                strcpy(data_batal.id_pembatalan, id_pembatalan);
                strcpy(data_batal.id_tiket, data.id_tiket);
                strcpy(data_batal.id_penumpang, data.id_penumpang);
                strcpy(data_batal.nama_penumpang, data.nama_penumpang);
                strcpy(data_batal.tanggal_pembatalan, tanggal_pembatalan);
                strcpy(data_batal.tanggal_booking, data.tanggal_berangkat); // Ambil dari tiket

                data_batal.hargaTbatal = data.harga * 0.7; // Refund 70%
                data_batal.refund = data.harga * 0.7;
                data_batal.metode_pengembalian = metode_pengembalian; // 1=Tunai, 2=Non Tunai

                fwrite(&data_batal, sizeof(DataPembatalan), 1, fp_log);

                fclose(fp_log);

                remove("tiket.dat");
                rename("temp.dat", "tiket.dat");

                gotoxy(37, 43);
                printf("Tiket berhasil dibatalkan! ID: %s", id_pembatalan);
                getch();
                break;
            }

            else if (confirm == 'N' || confirm == 'n') {
                gotoxy(45, 22);
                printf("Pembatalan dibatalkan.");
                getch();
                break;
            }

        }

    } while (n == 'y' || n == 'Y');
}



//========================================================
//Hitung pendapatan
void pendapatan(int x, int y) {

    FILE *fpTiket;
    tiket t;

    long totalPenjualan = 0;
    long totalRefund = 0;
    long totalPendapatan;

    // ================== HITUNG PENJUALAN DAN REFUND ==================
    fpTiket = fopen("tiket.dat", "rb");
    if (fpTiket != NULL) {
        while (fread(&t, sizeof(tiket), 1, fpTiket)) {
            // Cek status tiket
            if (strcmp(t.status, "Batal") == 0) {
                // Jika tiket dibatalkan, hitung refund 30%
                totalRefund += (t.hargaTbatal * 0.3);
            } else {
                // Jika tiket tidak dibatalkan, hitung sebagai penjualan
                totalPenjualan += t.harga;
            }
        }
        fclose(fpTiket);
    }

    // ================== TOTAL PENDAPATAN ==================
    // Pendapatan = Penjualan - Refund (karena refund adalah pengeluaran)
    totalPendapatan = totalPenjualan - totalRefund;

    // ================== OUTPUT ==================
    gotoxy(x, y);
    tampilanhargatiket(totalPendapatan);
}

void pengembalian(int x, int y) {
    FILE *fp = fopen("pembatalan.dat", "rb");

    if (!fp) {
        gotoxy(x, y);
        printf("0");
        return;
    }

    DataPembatalan batal;
    int total = 0;

    while (fread(&batal, sizeof(batal), 1, fp)) {
        total++;
    }

    fclose(fp);

    gotoxy(x, y);
    printf("%d", total);
}

void hitungtotalbatal() {
    FILE *fp;
    DataPembatalan batal;
    long total = 0;

    fp = fopen("batal.dat", "rb");
    if (fp == NULL) {
        gotoxy(37, 30);
        printf("Data batal belum tersedia!");
        return;
    }

    while (fread(&batal, sizeof(batal), 1, fp)) {
        total += batal.hargaTbatal;
    }

    fclose(fp);

    gotoxy(37, 32);
    printf("Total Pendapatan Tiket : ");
    tampilanhargatiket(total);
}





// ================= GENERATE ID PEMBATALAN OTOMATIS =================
static void generateIDPembatalan(char *id_pembatalan) {
    FILE *file = fopen("pembatalan.dat", "rb");
    int max_id = 0;
    DataPembatalan temp;

    // Baca file untuk mencari ID tertinggi
    if (file != NULL) {
        while (fread(&temp, sizeof(DataPembatalan), 1, file)) {
            // Ekstrak angka dari ID (misal: BTL001 -> 1)
            int num;
            if (sscanf(temp.id_pembatalan, "BTL%d", &num) == 1) {
                if (num > max_id) {
                    max_id = num;
                }
            }
        }
        fclose(file);
    }

    // Generate ID baru dengan format BTL001, BTL002, dst
    sprintf(id_pembatalan, "BTL%03d", max_id + 1);
}


// ================= GET TANGGAL SEKARANG =================
static void getTanggalSekarang(char *tanggal) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(tanggal, 15, "%d-%m-%Y", tm_info);
}

// ================= INPUT ID TIKET (TKT + 3 ANGKA) =================
static void inputIDTiketBatal(char *id, int x, int y) {
    int i = 0;
    char ch;
    char buffer[4]; // 3 angka + null

    gotoxy(x, y);
    printf("TKT"); // Tampilkan prefix TKT otomatis

    int inputX = x + 3; // Posisi setelah "TKT"
    gotoxy(inputX, y);

    while (1) {
        ch = getch();

        // ENTER - hanya jika sudah 3 angka
        if (ch == 13) {
            if (i == 3) {
                buffer[i] = '\0';
                sprintf(id, "TKT%s", buffer); // Gabungkan TKT + 3 angka
                return;
            }
        }
        // ESC - batal
        else if (ch == 27) {
            id[0] = '\0';
            return;
        }
        // BACKSPACE
        else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        // HANYA ANGKA, MAKSIMAL 3 DIGIT
        else if (ch >= '0' && ch <= '9') {
            if (i < 3) {
                buffer[i++] = ch;
                printf("%c", ch);
            }
        }
        // Selain angka diabaikan
    }
}
#endif