#ifndef PROJEK_BATALTIKET_H
#define PROJEK_BATALTIKET_H

#include "../FrameTabel.h"
#include <time.h>

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
    char tanggal_booking[15];
    char metode_bayar[10];
    char status[20];
    char notlpn[15];
    char Email[50];
} pembatalantiket;

static void inputIDTiketBatal(char *id, int x, int y);
static void bacaTiketPenumpang();

// ================= BACA DATA TIKET/PENUMPANG =================
void bacaTiketPenumpang() {

    FILE *fp;
    tiket all_tiket[1000];
    int total = 0;

    int startX = 37;
    int startY = 12;

    // ===== LEBAR KOLOM =====
    int wNo     = 3;
    int wID     = 10;
    int wNama   = 20;
    int wTelp   = 15;
    int wRute   = 25;
    int wTgl    = 12;
    int wStatus = 10;

    fp = fopen("tiket.dat", "rb");
    if (!fp) {
        gotoxy(startX, startY);
        printf("Belum ada data tiket.");
        return;
    }

    // ===== BACA SEMUA DATA =====
    while (fread(&all_tiket[total], sizeof(tiket), 1, fp) == 1) {
        if (total < 1000) total++;
    }
    fclose(fp);

    // ===== HITUNG PANJANG TABEL =====
    int totalWidth = 1 + (wNo+2) + (wID+2) + (wNama+2) + (wTelp+2) +
                     (wRute+2) + (wTgl+2) + (wStatus+2);

    char line[300];
    memset(line, '-', totalWidth);
    line[totalWidth] = '\0';

    clearArea(startX, startY, 130, 15);

    gotoxy(80, 13);
    printf("=== DAFTAR TIKET PENUMPANG ===");

    int row = startY + 2;

    // ===== GARIS ATAS =====
    gotoxy(startX, row++);
    printf("%s", line);

    // ===== HEADER =====
    gotoxy(startX, row++);
    printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
           wNo+1, "No",
           wID+1, "ID Tiket",
           wNama+1, "Nama Penumpang",
           wTelp+1, "No. Telepon",
           wRute+1, "Rute",
           wTgl+1, "Tgl Brgkt",
           wStatus+1, "Status");

    // ===== GARIS HEADER =====
    gotoxy(startX, row++);
    printf("%s", line);

    // ===== ISI DATA =====
    for (int i = 0; i < total && i < MAX_ROWS_PER_PAGE; i++) {

        char rute[30];
        sprintf(rute, "%s-%s",
                all_tiket[i].rute_awal,
                all_tiket[i].tujuan);

        gotoxy(startX, row++);
        printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
               wNo+1, i+1,
               wID+1, all_tiket[i].id_tiket,
               wNama+1, all_tiket[i].nama_penumpang,
               wTelp+1, all_tiket[i].notlpn,
               wRute+1, rute,
               wTgl+1, all_tiket[i].tanggal_berangkat,
               wStatus+1, all_tiket[i].status);
    }

    // ===== GARIS BAWAH =====
    gotoxy(startX, row++);
    printf("%s", line);
}


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
        bacaTiketPenumpang();

        bentukframe(35, 27, 108, 18);
        gotoxy(75, 27); printf("=== BATALKAN TIKET ===");

        FILE *fp_tiket = fopen("tiket.dat", "rb");
        if (!fp_tiket) {
            gotoxy(37, 29);
            printf("Belum ada data tiket!");
            gotoxy(37, 30);
            printf("Silakan pesan tiket terlebih dahulu.");
            getch();
            return;
        }
        fclose(fp_tiket);

        tiket data;
        char id_cari[20];

        // ================= INPUT ID TIKET =================
        gotoxy(37, 28);
        printf("ID Tiket       : ");

        inputIDTiketBatal(id_cari, 54, 28);
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
            gotoxy(37, 30);
            printf("Tiket dengan ID '%s' tidak ditemukan!", id_cari);
            getch();
            clearArea(35, 27, 80, 18);
            continue;
        }

        // ================= CEK STATUS =================
        if (strcmp(data.status, "Batal") == 0) {
            gotoxy(37, 30);
            printf("Tiket ini sudah dibatalkan!");
            getch();
            clearArea(35, 27, 80, 18);
            continue;
        }

        // ================= TAMPILKAN DATA TIKET =================
        gotoxy(37, 29); printf("ID Penumpang   : %s", data.id_penumpang);
        gotoxy(37, 30); printf("Nama Penumpang : %s", data.nama_penumpang);
        gotoxy(37, 31); printf("No. Telepon    : %s", data.notlpn);
        gotoxy(37, 32); printf("Email          : %s", data.Email);
        gotoxy(37, 33); printf("Rute           : %s → %s", data.rute_awal, data.tujuan);
        gotoxy(37, 34); printf("Armada         : %s", data.nama_armada);
        gotoxy(37, 35); printf("Berangkat      : %s | %s", data.tanggal_berangkat, data.jam_berangkat);
        gotoxy(37, 36); printf("Harga          : ");
        tampilanhargatiket(data.harga);
        gotoxy(37, 37); printf("Metode Bayar   : %s", data.metode_bayar);
        gotoxy(37, 38); printf("Status         : %s", data.status);

        // ================= KONFIRMASI PEMBATALAN =================
        bentukframe(87, 34, 36, 9);
        gotoxy(98, 35); printf("KONFIRMASI PEMBATALAN");

        gotoxy(90, 37); printf("Refund 80%%     : ");
        tampilanhargatiket(data.harga * 0.8);

        gotoxy(90, 39); printf("Batalkan tiket ini?");
        gotoxy(90, 40); printf("(Y) Ya  (N) Tidak : ");

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

                // Tampilan proses pembatalan
                clearArea(90, 37, 30, 6);
                gotoxy(95, 39);
                printf("Membatalkan tiket");

                for (int i = 0; i < 3; i++) {
                    printf(".");
                    fflush(stdout);
                    Sleep(500);
                }

                gotoxy(90, 41);
                printf("Pembatalan berhasil!");
                Sleep(1000);

                gotoxy(37, 40); printf("Status         : Batal");
                gotoxy(37, 42); printf("Tiket berhasil dibatalkan!");
                gotoxy(37, 43); printf("Batalkan lagi? (y/n): ");

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

// ================= INPUT ID TIKET =================
static void inputIDTiketBatal(char *id, int x, int y) {
    int i = 0;
    char ch;

    gotoxy(x, y);

    while (1) {
        ch = getch();

        // ENTER
        if (ch == 13) {
            if (i > 0) {
                id[i] = '\0';
                return;
            }
        }
        // ESC → batal
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
        // HURUF DAN ANGKA SAJA
        else if ((ch >= 'A' && ch <= 'Z') ||
                 (ch >= 'a' && ch <= 'z') ||
                 (ch >= '0' && ch <= '9')) {
            if (i < 19) {
                id[i++] = ch;
                printf("%c", ch);
            }
        }
        // selain itu DIABAIKAN
    }
}

#endif