#ifndef PROJEK_BATALTIKET_H
#define PROJEK_BATALTIKET_H

#include "../FrameTabel.h"
#include <time.h>
//#include "readtiket.h"
#include "../Pemesanan/Pesantiket.h"

// ================= STRUCT (SAMA PERSIS DENGAN CREATETIKET.H) =================
typedef struct {
    char id_tiket[20];
    char id_penumpang[20];
    char nama_penumpang[50];
    char rute_awal[30];
    char tujuan[30];
    char nama_armada[30];
    char tanggal_berangkat[15];
    char jam_berangkat[10];
    float harga;
    long hargaTbatal;
    char tanggal_booking[15];
    char metode_bayar[10];
    char status[20];
    char notlpn[15];
    char Email[50];
} batal;

// ================= STRUCT UNTUK MENYIMPAN DATA PEMBATALAN =================
typedef struct {
    char id_pembatalan[10];
    char id_tiket[20];
    char nama_penumpang[50];
    char tanggal_pembatalan[15];
    long refund;
    long metode_pengembalian;
} DataPembatalan;

static void inputIDTiketBatal(char *id, int x, int y);
static void generateIDPembatalan(char *id_pembatalan);
static void getTanggalSekarang(char *tanggal);


void readTiketPenumpang() {

    FILE *fp;
    tiket data[1000];
    int total = 0;

    int startX = 37;
    int startY = 12;

    // ===== LEBAR KOLOM =====
    int wNo = 3, wID = 10, wNama = 20, wTelp = 15;
    int wRute = 25, wTgl = 12, wStatus = 10;

    fp = fopen("tiket.dat", "rb");
    if (!fp) {
        gotoxy(startX, startY);
        printf("Belum ada data tiket.");
        getch();
        return;
    }

    while (fread(&data[total], sizeof(tiket), 1, fp) == 1) {
        if (total < 1000) total++;
    }
    fclose(fp);

    int total_pages = (total + MAX_ROWS_PER_PAGE - 1) / MAX_ROWS_PER_PAGE;
    int current_page = 1;
    char key;

    int totalWidth =
        1 + (wNo+2)+(wID+2)+(wNama+2)+(wTelp+2)+
        (wRute+2)+(wTgl+2)+(wStatus+2);

    char garis[300];
    memset(garis, '-', totalWidth);
    garis[totalWidth] = '\0';

    do {
        int start = (current_page - 1) * MAX_ROWS_PER_PAGE;
        int end = start + MAX_ROWS_PER_PAGE;
        if (end > total) end = total;

        clearArea(startX, startY + 1, totalWidth, 18);

        gotoxy(80, 13);
        printf("=== DAFTAR TIKET PENUMPANG ===");

        int row = startY + 2;

        // ===== TABEL =====
        gotoxy(startX, row++); printf("%s", garis);

        gotoxy(startX, row++);
        printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
               wNo+1,"No",
               wID+1,"ID Tiket",
               wNama+1,"Nama",
               wTelp+1,"Telepon",
               wRute+1,"Rute",
               wTgl+1,"Tanggal",
               wStatus+1,"Status");

        gotoxy(startX, row++); printf("%s", garis);

        for (int i = start; i < end; i++) {
            char rute[40];
            sprintf(rute, "%s-%s",
                    data[i].rute_awal,
                    data[i].tujuan);

            gotoxy(startX, row++);
            printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
                   wNo+1, i+1,
                   wID+1, data[i].id_tiket,
                   wNama+1, data[i].nama_penumpang,
                   wTelp+1, data[i].notlpn,
                   wRute+1, rute,
                   wTgl+1, data[i].tanggal_berangkat,
                   wStatus+1, data[i].status);
        }

        gotoxy(startX, row++); printf("%s", garis);

        // ===== NAVIGASI (SESUIAI PERMINTAANMU) =====
        bentukframe(3, 11, 27, 12);
        gotoxy(6, 13); printf("[SPASI] Lanjut");
        gotoxy(6, 15); printf("[BACKSPACE] Kembali");
        gotoxy(6, 17); printf("[ENTER] Keluar");
        gotoxy(6, 19); printf("Halaman: %d/%d", current_page, total_pages);
        gotoxy(6, 21); printf("Total  : %d data", total);

        key = getch();

        if (key == ' ' && current_page < total_pages)
            current_page++;
        else if (key == 8 && current_page > 1)
            current_page--;

    } while (key != 13);
}

//========================================================================

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

// ================= BATAL TIKET =================
void BatalTiket() {
    char n;

    do {
        // ================= TAMPILAN AWAL =================
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

        // ================= CEK FILE TIKET =================
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

            // ENTER - Lanjut ke form pembatalan
            if (key == 13) {
                break;
            }
        }

        // ================= TAMPILKAN FORM PEMBATALAN =================
        bentukframe(35, 27, 108, 18);
        gotoxy(75, 27); printf("=== BATALKAN TIKET ===");

        tiket data;
        char id_cari[20];
        char id_pembatalan[10];
        char tanggal_pembatalan[15];

        // ================= GENERATE ID PEMBATALAN OTOMATIS =================
        generateIDPembatalan(id_pembatalan);

        // ================= GET TANGGAL PEMBATALAN OTOMATIS =================
        getTanggalSekarang(tanggal_pembatalan);

        gotoxy(37, 28);
        printf("ID Pembatalan  : %s", id_pembatalan);

        gotoxy(37, 29);
        printf("Tanggal Batal  : %s", tanggal_pembatalan);

        // ================= INPUT ID TIKET =================
        gotoxy(37, 30);
        printf("ID Tiket       : ");

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

        // ================= CEK STATUS =================
        if (strcmp(data.status, "Batal") == 0) {
            gotoxy(37, 31);
            printf("Tiket ini sudah dibatalkan!");
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
        gotoxy(37, 40); printf("Status         : %s", data.status);

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
        gotoxy(90, 37); printf("Metode Refund  : %s", (metode_pengembalian == 1) ? "Tunai" : "Non Tunai");
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
                // Update status di file
                FILE *fp_read = fopen("tiket.dat", "rb");
                FILE *fp_temp = fopen("temp.dat", "wb");

                if (!fp_read || !fp_temp) {
                    gotoxy(90, 42);
                    printf("Error: Tidak dapat membatalkan tiket!");
                    getch();
                    if (fp_read) fclose(fp_read);
                    if (fp_temp) fclose(fp_temp);
                    return;
                }

                tiket temp_data;
                while (fread(&temp_data, sizeof(tiket), 1, fp_read)) {
                    if (strcmp(temp_data.id_tiket, id_cari) == 0) {
                        strcpy(temp_data.status, "Batal");
                    }
                    fwrite(&temp_data, sizeof(tiket), 1, fp_temp);
                }

                fclose(fp_read);
                fclose(fp_temp);

                remove("tiket.dat");
                rename("temp.dat", "tiket.dat");

                // ================= SIMPAN DATA PEMBATALAN =================
                FILE *fp_batal = fopen("batal.dat", "ab");
                if (fp_batal) {
                    DataPembatalan data_batal;
                    strcpy(data_batal.id_pembatalan, id_pembatalan);
                    strcpy(data_batal.id_tiket, id_cari);
                    strcpy(data_batal.nama_penumpang, data.nama_penumpang);
                    strcpy(data_batal.tanggal_pembatalan, tanggal_pembatalan);
                    data_batal.metode_pengembalian = metode_pengembalian; // 1 = Tunai, 2 = Non Tunai
                    data_batal.refund = data.harga * 0.7;

                    fwrite(&data_batal, sizeof(DataPembatalan), 1, fp_batal);
                    fclose(fp_batal);
                }

                // Tampilan proses pembatalan
                clearArea(90, 36, 30, 6);
                gotoxy(95, 39);
                printf("Membatalkan tiket");

                for (int i = 0; i < 3; i++) {
                    printf(".");
                    fflush(stdout);
                    Sleep(500);
                }

                //clearArea(87, 34, 36, 11);
                gotoxy(90, 37);
                printf("Pembatalan berhasil!");
                Sleep(1000);

                gotoxy(90, 29); printf("Status         : Batal");
                gotoxy(90, 30); printf("ID Pembatalan  : %s", id_pembatalan);
                gotoxy(90, 31); printf("Metode Refund  : %s", (metode_pengembalian == 1) ? "Tunai" : "Non Tunai");
                gotoxy(90, 32); printf("Tiket berhasil dibatalkan!");
                gotoxy(90, 33); printf("Batalkan lagi? (y/n): ");

                while (1) {
                    n = getch();
                    if (n == 27) {
                        clearArea(35, 27, 80, 18);
                        return;
                    }
                    if (n == 'y' || n == 'Y' || n == 'n' || n == 'N') {
                        clearArea(35, 27, 80, 18);
                        if (n == 'n' || n == 'N') return;
                        break;
                    }
                }
                break;
            }
            // TIDAK
            else if (confirm == 'N' || confirm == 'n') {
                clearArea(35, 27, 80, 18);
                return;
            }
        }

    } while (n == 'y' || n == 'Y');
}

//========================================================
//Hitung pendapatan
void pendapatan(int x, int y) {

    FILE *fpTiket, *fpRefund;
    tiket t;
    batal p;

    long totalPenjualan = 0;
    long totalRefund = 0;
    long totalPendapatan;

    // ================== HITUNG PENJUALAN ==================
    fpTiket = fopen("tiket.dat", "rb");
    if (fpTiket != NULL) {
        while (fread(&t, sizeof(tiket), 1, fpTiket)) {
             totalPenjualan += t.harga;
        }
        fclose(fpTiket);
    }

    // ================== HITUNG REFUND ==================
    fpRefund = fopen("batal.dat", "rb");
    if (fpRefund != NULL) {
        while (fread(&p, sizeof(batal), 1, fpRefund)) {
            totalRefund += p.hargaTbatal;
        }
        fclose(fpRefund);
    }

    // ================== TOTAL PENDAPATAN ==================
    totalPendapatan = totalPenjualan - totalRefund;

    // ================== OUTPUT ==================
    gotoxy(x, y);
    tampilanhargatiket(totalPendapatan);
}

void pengembalian(int x, int y) {
    FILE *fp = fopen("batal.dat", "rb");

    if (!fp) {
        gotoxy(x, y);
        printf("0");
        return;
    }

    batal data;
    int total = 0;

    while (fread(&data, sizeof(batal), 1, fp)) {
        total++;
    }

    fclose(fp);

    gotoxy(x, y);
    printf("%d", total);
}

void hitungtotalbatal() {
    FILE *fp;
    batal data;
    long total = 0;

    fp = fopen("batal.dat", "rb");
    if (fp == NULL) {
        gotoxy(37, 30);
        printf("Data batal belum tersedia!");
        return;
    }

    while (fread(&data, sizeof(batal), 1, fp)) {
        total += data.hargaTbatal;
    }

    fclose(fp);

    gotoxy(37, 32);
    printf("Total Pendapatan Tiket : ");
    tampilanhargatiket(total);
}

#endif