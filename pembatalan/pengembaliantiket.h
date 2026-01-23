#ifndef PROJEK_DELETE_TIKET_H
#define PROJEK_DELETE_TIKET_H

#include <stdio.h>
#include <string.h>
#include <windows.h>

void readTiketAktif();
void generateIDPembatalan(char *id_pembatalan);
static void inputIDTiketBatal(char *id, int x, int y);

void BatalTiket() {
    char n;

    do {
        // ================= TAMPILAN AWAL =================
        system("chcp 65001 > nul");
        fillBackground(0x90);
        bentukframe(2, 1, 30, 45);
        bentukframe(3, 4, 27, 3);
        gotoxy(8, 5); printf("Kelompok 5");
        bentukframe(34, 1, 121, 10);
        tampilanlogin("GAMBARASCI.txt", 60, 3);
        bentukframe(3, 29, 27, 10);
        gotoxy(5, 30); printf("=== MENU NAVIGASI ===");
        gotoxy(4, 32); printf("NAVIGASI [↑ ↓]");
        gotoxy(4, 34); printf("[ENTER] Pilih");
        gotoxy(4, 36); printf("[ESC] Keluar");
        readTiketAktif();



        // ================= CEK FILE TIKET =================
        FILE *fp_tiket = fopen("tiket.dat", "rb");
        if (!fp_tiket) {
            bentukframe(35, 27, 70, 5);
            gotoxy(50, 28); printf("=== BATALKAN TIKET ===");
            gotoxy(37, 30); printf("Belum ada data tiket!");
            gotoxy(37, 31); printf("Silakan pesan tiket terlebih dahulu.");
            getch();
            return;
        }
        fclose(fp_tiket);


        bentukframe(34, 27, 70, 18);
        gotoxy(50, 28); printf("=== BATALKAN TIKET ===");

        tiket data;
        char id_cari[20];
        int found = 0;

        while (!found) {
            char id_pembatalan[10];
            generateIDPembatalan(id_pembatalan);
            clearArea(36, 29, 35, 5);
            gotoxy(36, 29); printf("ID Pembatalan : %s", id_pembatalan);
            gotoxy(36, 30); printf("ID Tiket      : ");

            inputIDTiketBatal(id_cari, 52, 30);

            // Jika user tekan ESC
            if (strlen(id_cari) == 0) {
                return;
            }

            // ================= CARI TIKET =================
            fp_tiket = fopen("tiket.dat", "rb");
            found = 0;

            while (fread(&data, sizeof(tiket), 1, fp_tiket)) {
                if (strcmp(data.id_tiket, id_cari) == 0) {
                    found = 1;
                    break;
                }
            }
            fclose(fp_tiket);

            // Jika tidak ditemukan
            if (!found) {
                gotoxy(36, 32); printf("ID Tiket  tidak ditemukan!", id_cari);
                gotoxy(36, 33); printf("Silakan coba lagi...");
                Sleep(1500);
                continue;
            }

            // ================= CEK STATUS =================
            if (strcmp(data.status, "Batal") == 0) {
                gotoxy(36, 32); printf("Tiket ini sudah dibatalkan!");
                gotoxy(36, 33); printf("Silakan coba lagi...");
                Sleep(1500);
                found = 0; // Reset agar loop lanjut
                continue;
            }
        }

        // ================= TAMPILKAN DATA TIKET (KIRI) =================

        gotoxy(36, 31); printf("ID Penumpang   : %s", data.id_penumpang);
        gotoxy(36, 32); printf("Nama Penumpang : %s", data.nama_penumpang);
        gotoxy(36, 33); printf("No. Telepon    : %s", data.notlpn);
        gotoxy(36, 34); printf("Email          : %s", data.Email);
        gotoxy(36, 35); printf("Rute           : %s → %s", data.rute_awal, data.tujuan);
        gotoxy(36, 36); printf("Armada         : %s", data.nama_armada);
        gotoxy(36, 37); printf("Berangkat      : %s | %s", data.tanggal_berangkat, data.jam_berangkat);
        gotoxy(36, 38); printf("Harga          : ");
        tampilanhargatiket(data.harga);
        gotoxy(36, 39); printf("Metode Bayar   : %s", data.metode_bayar);
        gotoxy(36, 40); printf("Status         : %s", data.status);

        // ================= FRAME METODE PENGEMBALIAN (KANAN) =================
        bentukframe(106, 27, 48, 18);
        gotoxy(115, 28); printf("METODE PENGEMBALIAN DANA");
        gotoxy(108, 30); printf("Refund 70%%     : Rp ");
        tampilanhargatiket(data.harga * 0.7);

        long metode_pengembalian;
        char pilihan_refund;

        gotoxy(108, 32); printf("Pilih metode pengembalian:");
        gotoxy(108, 33); printf("(T) Tunai");
        gotoxy(108, 34); printf("(N) Non Tunai");
        gotoxy(108, 35); printf("Pilihan Anda   : ");

        // Loop validasi metode pengembalian
        while (1) {
            pilihan_refund = getch();

            if (pilihan_refund == 27) {
                clearArea(34, 27, 120, 18);
                return;
            }

            if (pilihan_refund == 'T' || pilihan_refund == 't') {
                metode_pengembalian = 1;
                gotoxy(127, 35); printf("T");
                break;
            }

            if (pilihan_refund == 'N' || pilihan_refund == 'n') {
                metode_pengembalian = 2;
                gotoxy(127, 35); printf("N");
                break;
            }
        }

        // ================= KONFIRMASI PEMBATALAN =================
        clearArea(108, 30, 44, 6);
        gotoxy(108, 30); printf("Metode Refund  : %s", (metode_pengembalian == 1) ? "Tunai" : "Non Tunai");
        gotoxy(108, 31); printf("Refund 70%%     : Rp ");
        tampilanhargatiket(data.harga * 0.7);
        gotoxy(108, 37); printf("Batalkan tiket ini?");
        gotoxy(108, 38); printf("(Y) Ya (N) Tidak : ");

        char confirm;
        while (1) {
            confirm = getch();

            if (confirm == 27) {
                clearArea(34, 27, 120, 18);
                return;
            }

            // YA - PROSES PEMBATALAN
            if (confirm == 'Y' || confirm == 'y') {
                FILE *fp_read = fopen("tiket.dat", "rb");
                FILE *fp_temp = fopen("temp.dat", "wb");

                if (!fp_read || !fp_temp) {
                    gotoxy(108, 40); printf("Error: Tidak dapat membatalkan tiket!");
                    getch();
                    if (fp_read) fclose(fp_read);
                    if (fp_temp) fclose(fp_temp);
                    return;
                }

                tiket temp_data;
                while (fread(&temp_data, sizeof(tiket), 1, fp_read)) {
                    if (strcmp(temp_data.id_tiket, id_cari) == 0) {
                        strcpy(temp_data.status, "Batal");

                        // TAMBAHKAN INI - Update metode pengembalian
                        if (metode_pengembalian == 1) {
                            strcpy(temp_data.metode_bayar, "Tunai");
                        } else {
                            strcpy(temp_data.metode_bayar, "Non-Tunai");
                        }

                        // TAMBAHKAN INI - Hitung refund 70%
                        temp_data.harga = temp_data.harga * 0.7;
                    }
                    fwrite(&temp_data, sizeof(tiket), 1, fp_temp);
                }
                fclose(fp_read);
                fclose(fp_temp);
                remove("tiket.dat");
                rename("temp.dat", "tiket.dat");

                // Tampilan proses pembatalan
                clearArea(108, 30, 44, 10);
                gotoxy(115, 35); printf("Membatalkan tiket");
                for (int i = 0; i < 3; i++) {
                    printf(".");
                    fflush(stdout);
                    Sleep(500);
                }

                clearArea(108, 30, 44, 10);
                gotoxy(108, 31); printf("Pembatalan berhasil!");
                Sleep(1000);

                gotoxy(36, 40); printf("Status         : Batal");
                gotoxy(108, 33); printf("Status         : Batal");
                gotoxy(108, 34); printf("Metode Refund  : %s", (metode_pengembalian == 1) ? "Tunai" : "Non Tunai");
                gotoxy(108, 35); printf("Tiket berhasil dibatalkan!");
                gotoxy(108, 37); printf("Batalkan lagi? (y/n): ");

                while (1) {
                    n = getch();
                    if (n == 27) {
                        clearArea(34, 27, 120, 18);
                        return;
                    }
                    if (n == 'y' || n == 'Y' || n == 'n' || n == 'N') {
                        clearArea(34, 27, 120, 18);
                        if (n == 'n' || n == 'N') return;
                        break;
                    }
                }
                break;
            }
            // TIDAK
            else if (confirm == 'N' || confirm == 'n') {
                clearArea(34, 27, 120, 18);
                return;
            }
        }

    } while (n == 'y' || n == 'Y');
}

void readTiketAktif() {
    FILE *fp;
    tiket data[1000];
    tiket aktifData[1000];
    int total = 0;
    int totalAktif = 0;
    int startX = 37;
    int startY = 12;

    int wNo = 3, wID = 10, wNama = 20, wTelp = 15;
    int wRute = 25, wTgl = 12, wStatus = 15;

    fp = fopen("tiket.dat", "rb");
    if (!fp) {
        gotoxy(startX, startY);
        printf("Belum ada data tiket.");
        getch();
        return;
    }

    while (fread(&data[total], sizeof(tiket), 1, fp) == 1) {
        if (total < 1000) {
            if (strcmp(data[total].status, "Aktif") == 0) {
                aktifData[totalAktif] = data[total];
                totalAktif++;
            }
            total++;
        }
    }
    fclose(fp);

    if (totalAktif == 0) {
        gotoxy(startX, startY);
        printf("Belum ada tiket aktif.");
        getch();
        return;
    }

    int rowsPerPage = 10;
    int total_pages = (totalAktif + rowsPerPage - 1) / rowsPerPage;
    int current_page = 1;
    char key;

    int totalWidth = 1 + (wNo+2)+(wID+2)+(wNama+2)+(wTelp+2)+(wRute+2)+(wTgl+2)+(wStatus+2);
    char garis[300];
    memset(garis, '-', totalWidth);
    garis[totalWidth] = '\0';

    do {
        int start = (current_page - 1) * rowsPerPage;
        int end = start + rowsPerPage;
        if (end > totalAktif) end = totalAktif;

        clearArea(startX, startY + 1, totalWidth, 18);
        gotoxy(80, 13); printf("=== DAFTAR TIKET AKTIF ===");

        int row = startY + 2;
        gotoxy(startX, row++); printf("%s", garis);
        gotoxy(startX, row++);
        printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
               wNo+1,"No", wID+1,"ID Tiket", wNama+1,"Nama", wTelp+1,"Telepon",
               wRute+1,"Rute", wTgl+1,"Tanggal", wStatus+1,"Status");
        gotoxy(startX, row++); printf("%s", garis);

        for (int i = start; i < end; i++) {
            char rute[40];
            sprintf(rute, "%s-%s", aktifData[i].rute_awal, aktifData[i].tujuan);
            gotoxy(startX, row++);
            printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
                   wNo+1, i+1, wID+1, aktifData[i].id_tiket,
                   wNama+1, aktifData[i].nama_penumpang,
                   wTelp+1, aktifData[i].notlpn,
                   wRute+1, rute,
                   wTgl+1, aktifData[i].tanggal_berangkat,
                   wStatus+1, aktifData[i].status);
        }
        gotoxy(startX, row++); printf("%s", garis);

        bentukframe(3, 11, 27, 12);
        gotoxy(6, 13); printf("[SPASI] Lanjut");
        gotoxy(6, 15); printf("[BACKSPACE] Kembali");
        gotoxy(6, 17); printf("[ENTER] Keluar");
        gotoxy(6, 19); printf("Halaman: %d/%d", current_page, total_pages);
        gotoxy(6, 21); printf("Total : %d tiket aktif", totalAktif);

        key = getch();
        if (key == ' ' && current_page < total_pages) current_page++;
        else if (key == 8 && current_page > 1) current_page--;

    } while (key != 13);
}

void generateIDPembatalan(char *id_pembatalan) {
    FILE *fp;
    tiket data;
    int count = 0;

    fp = fopen("batal.dat", "rb");
    if (fp != NULL) {
        while (fread(&data, sizeof(tiket), 1, fp) == 1) {
            count++;
        }
        fclose(fp);
    }

    sprintf(id_pembatalan, "BTL%03d", count + 1);
}

static void inputIDTiketBatal(char *id, int x, int y) {
    int i = 0;
    char ch;
    char buffer[4];

    gotoxy(x, y);
    printf("TKT");

    int inputX = x + 3;
    gotoxy(inputX, y);

    while (1) {
        ch = getch();

        // ENTER
        if (ch == 13) {
            // Validasi: harus 3 angka
            if (i < 3) {
                gotoxy(36, 32);
                printf("ID Tiket harus 3 angka!");
                Sleep(1500);
                gotoxy(36, 32);
                printf("                        ");

                // ===== RESET INPUT =====
                i = 0;
                for (int j = 0; j < 4; j++) {
                    buffer[j] = '\0';
                }
                gotoxy(inputX, y);
                printf("   ");
                gotoxy(inputX, y);
                continue;
            }

            if (i == 3) {
                buffer[i] = '\0';
                sprintf(id, "TKT%s", buffer);
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
        // ANGKA (maksimal 3 digit)
        else if (ch >= '0' && ch <= '9') {
            if (i < 3) {
                buffer[i++] = ch;
                printf("%c", ch);
            }
        }
    }
}

#endif