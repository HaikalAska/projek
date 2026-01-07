#ifndef PROJEK_CREATETIKET_H
#define PROJEK_CREATETIKET_H

#include "../FrameTabel.h"
#include <time.h>
// #include "../pembatalan/pengembaliantiket.h"

// ================= STRUCT =================
typedef struct {
    char id_tiket[20];
    char id_penumpang[20];
    char nama_penumpang[50];
    char rute_awal[30];
    char tujuan[30];
    char nama_armada[30];
    char tanggal_berangkat[15];
    char jam_berangkat[10];
    long harga;
    long hargaTtiket;
    long hargaTbatal;
    char tanggal_booking[15];
    char metode_bayar[10];
    char status[20];
    char notlpn[15];
    char Email[50];
} tiket;

int getTiketCount();
void getCurrentDate(char *date);
static void inputPaymentMethod(char *metode, int row, int col);
static int inputNoJadwal(int x, int y);
int getPenumpangCount();
static void inputEmailGmail(char *email, int x, int y);

// ================= PESAN TIKET =================
void PesanTiket() {
      char n;

    do {
        system("chcp 65001 > nul");
        fillBackground(0x90);
        bentukframe(2, 1, 30, 45);
        bentukframe(34, 1, 121, 10);
        bentukframe(3, 4, 27, 3);
        tampilanlogin("GAMBARASCI.txt", 45, 3);
        gotoxy(8,5); printf("Kelompok 5");
        bentukframe(3, 29, 27, 10);
        gotoxy(5,30); printf("=== MENU NAVIGASI ===");
        gotoxy(4,32); printf("NAVIGASI [↑ ↓]");
        gotoxy(4,34); printf("[ENTER] Pilih");
        gotoxy(4,36); printf("[ESC] Keluar");
        bacajadwal();


        bentukframe(35, 27, 108, 18);
        gotoxy(78, 27); printf("=== BUAT TIKET ===");

        FILE *fp_tiket = fopen("tiket.dat", "ab");
        if (!fp_tiket) return;

        tiket data;
        jadwal jadwal_data;


        int count = getTiketCount() + 1;
        sprintf(data.id_tiket, "TKT%03d", count);

        gotoxy(37, 28);
        printf("ID Tiket       : %s", data.id_tiket);

        // ================= INPUT NOMOR JADWAL =================
        int nomor_jadwal;

        gotoxy(37, 29);
        printf("No Jadwal      : ");

        nomor_jadwal = inputNoJadwal(54, 29);
        if (nomor_jadwal == -1) {
            fclose(fp_tiket);
            return;
        }

        FILE *fp_jadwal = fopen("jadwal.dat", "rb");

        int found = 0;
        int index = 1;

        while (fread(&jadwal_data, sizeof(jadwal), 1, fp_jadwal)) {
            if (index == nomor_jadwal) {
                found = 1;
                break;
            }
            index++;
        }
        fclose(fp_jadwal);

        if (!found) {
            fclose(fp_tiket);
            gotoxy(37, 30);
            printf("Nomor Tidak Ada di Data!");
            getch();
            clearArea(35, 27, 80, 18);
            continue;
        }

        // ================= COPY DATA JADWAL =================
        strcpy(data.rute_awal, jadwal_data.kotaAsal);
        strcpy(data.tujuan, jadwal_data.kotaTujuan);
        strcpy(data.nama_armada, jadwal_data.nama_armada);
        strcpy(data.tanggal_berangkat, jadwal_data.tanggal);
        strcpy(data.jam_berangkat, jadwal_data.jamBerangkat);
        data.harga = jadwal_data.harga;

        gotoxy(37, 30); printf("Rute           : %s → %s", data.rute_awal, data.tujuan);
        gotoxy(37, 31); printf("Armada         : %s", data.nama_armada);
        gotoxy(37, 32);printf("Berangkat      : %s | %s",data.tanggal_berangkat, data.jam_berangkat);
        gotoxy(37, 33); printf("Harga          : ");
        tampilanhargatiket(data.harga);



        int pCount = getPenumpangCount() + 1;
        sprintf(data.id_penumpang, "PNP%03d", pCount);
        gotoxy(37, 35); printf("ID Penumpang   : %s", data.id_penumpang);



        // NAMA
        gotoxy(37, 36);
        printf("Nama Penumpang : ");
        setPointer(37, 55);
        INPUTNama(data.nama_penumpang);
        if (strlen(data.nama_penumpang) == 0) {
            fclose(fp_tiket);
            return;
        }

        // NO TELP
        gotoxy(37, 37);
        printf("No. Telepon    : ");
        inputNoTelp(data.notlpn, 54, 37);
        if (strlen(data.notlpn) == 0) {
            fclose(fp_tiket);
            return;
        }

        gotoxy(37, 38);
        printf("Email          : ");
        inputEmailGmail(data.Email, 54, 38);

        if (strlen(data.Email) == 0) {
            fclose(fp_tiket);
            return;
        }


        gotoxy(37, 39);
        printf("Metode Bayar   : ");
        inputPaymentMethod(data.metode_bayar, 39, 54);
        if (strlen(data.metode_bayar) == 0) {
            fclose(fp_tiket);
            return;
        }

        if (strcmp(data.metode_bayar, "Cash") == 0) {
            long dibayar = 0;
            long kembalian = 0;
            int escPressed;

            bentukframe(87, 34, 36, 9);
            gotoxy(103,35); printf("CASH");

            gotoxy(90, 37); printf("Dibayar        : ");
            gotoxy(90, 38); printf("Harga          : ");
            tampilanhargatiket(data.harga);

            gotoxy(90, 39); printf("------------------------------");
            gotoxy(90, 40); printf("Kembalian      : ");

            do {
                // Kosongkan nilai input & kembalian
                gotoxy(107, 37); printf("           ");
                gotoxy(107, 40); printf("           ");
                gotoxy(107, 41); printf("           ");

                // INPUT DIBAYAR
                gotoxy(107, 37);
                dibayar = inputangka7digit(107, 37, &escPressed );

                // ESC ditekan
                if (escPressed) {
                    fclose(fp_tiket);
                    return;
                }

                // Tampilkan dibayar
                gotoxy(107, 37);
                tampilanhargatiket(dibayar);

                kembalian = dibayar - data.harga;

                // Jika uang kurang
                if (kembalian < 0) {
                    gotoxy(90, 41);
                    printf("Uang kurang!");

                    Sleep(800);

                    gotoxy(90, 41);
                    printf("             "); // hapus pesan

                    continue;
                }

            } while (kembalian < 0);

            // ===== TAMPILKAN KEMBALIAN =====
            gotoxy(107, 40);
            tampilanhargatiket(kembalian);
        }
        else if (strcmp(data.metode_bayar, "Cashless") == 0) {
            // ===== PROSES PEMBAYARAN QRIS =====

            gotoxy(103, 35); printf("QRIS");
            gotoxy(90, 37); printf("Scan QR Code berikut:");
            system("cls");
            printQRCodeFromFile("QR.txt", 53, 7);


            // ===== PROSES PEMBAYARAN =====
            gotoxy(60, 35); printf("Memproses pembayaran");

            for (int i = 0; i < 3; i++) {
                printf(".");
                fflush(stdout); // Paksa print langsung
                Sleep(500);
            }

            gotoxy(50, 57);
            printf("Pembayaran berhasil!");
            Sleep(1000);
        }



        getCurrentDate(data.tanggal_booking);
        strcpy(data.status, "Aktif");

        gotoxy(37, 40); printf("Tgl Booking    : %s", data.tanggal_booking);
        gotoxy(37, 41); printf("Status         : %s", data.status);
        fwrite(&data, sizeof(tiket), 1, fp_tiket);
        fclose(fp_tiket);

        gotoxy(37, 42); printf("Tiket berhasil dibuat!");
        gotoxy(37, 43); printf("Tambah lagi? (y/n): ");

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

    } while (n == 'y' || n == 'Y');
}


// ================= ID TIKET =================
int getTiketCount() {
    FILE *fp = fopen("tiket.dat", "rb");
    if (!fp) return 0;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);

    return size / sizeof(tiket);
}

//============= ID PENUMPANG OTOMATIS ====================
int getPenumpangCount() {
    FILE *fp = fopen("tiket.dat", "rb");
    if (!fp) return 0;
    fseek(fp, 0, SEEK_END);
    int count = ftell(fp) / sizeof(tiket);
    fclose(fp);
    return count;
}


// ================= TANGGAL SEKARANG =================
void getCurrentDate(char *date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%02d/%02d/%d",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// ================= INPUT METODE BAYAR =================
static void inputPaymentMethod(char *metode, int row, int col) {
    char ch;

    gotoxy(col, row);
    printf("C/L : ");

    int inputX = col + 6;

    while (1) {
        ch = getch();

        // ESC
        if (ch == 27) {
            metode[0] = '\0';
            return;
        }

        // CASH
        else if (ch == 'C' || ch == 'c') {
            strcpy(metode, "Cash");

            // clear area input
            gotoxy(inputX, row);
            printf("            ");
            gotoxy(inputX, row);
            printf("Cash");

            while (1) {
                ch = getch();
                if (ch == 13) return; // ENTER
                else if (ch == 8) break;
                else if (ch == 27) {
                    metode[0] = '\0';
                    return;
                }
            }


            gotoxy(inputX, row);
            printf("            ");
            gotoxy(inputX, row);
        }

        // CASHLESS
        else if (ch == 'L' || ch == 'l') {
            strcpy(metode, "Cashless");

            gotoxy(inputX, row);
            printf("            ");
            gotoxy(inputX, row);
            printf("Cashless");

            while (1) {
                ch = getch();
                if (ch == 13) return;
                else if (ch == 8) break;
                else if (ch == 27) {
                    metode[0] = '\0';
                    return;
                }
            }

            gotoxy(inputX, row);
            printf("            ");
            gotoxy(inputX, row);
        }
    }
}


//======================INPUT ANGKA JADWAL===========================//
static int inputNoJadwal(int x, int y) {
    int i = 0;
    char ch;
    char buffer[6];

    gotoxy(x, y);

    while (1) {
        ch = getch();

        // ENTER
        if (ch == 13) {
            if (i > 0) {
                buffer[i] = '\0';
                return atoi(buffer);
            }
        }
        // ESC → batal
        else if (ch == 27) {
            return -1;
        }
        // BACKSPACE
        else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        // ANGKA SAJA
        else if (ch >= '0' && ch <= '9') {
            if (i < 5) {
                buffer[i++] = ch;
                printf("%c", ch);
            }
        }
        // selain angka DIABAIKAN
    }
}

//===========EMAIL OTOMATIS============================
static void inputEmailGmail(char *email, int x, int y) {
    int i = 0;
    char ch;
    char buffer[40];

    gotoxy(x, y);

    while (1) {
        ch = getch();

        // ENTER → baru tambah @gmail.com
        if (ch == 13) {
            if (i > 0) {
                buffer[i] = '\0';
                sprintf(email, "%s@gmail.com", buffer);

                // tampilkan hasil akhir di layar
                gotoxy(x, y);
                printf("%s@gmail.com", buffer);

                return;
            }
        }
        // ESC → batal
        else if (ch == 27) {
            email[0] = '\0';
            return;
        }
        // BACKSPACE
        else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        // KARAKTER VALID EMAIL (DEPAN AJA)
        else if (
            (ch >= 'a' && ch <= 'z') ||
            (ch >= 'A' && ch <= 'Z') ||
            (ch >= '0' && ch <= '9') ||
            ch == '.' || ch == '_'
        ) {
            if (i < 30) {
                buffer[i++] = ch;
                printf("%c", ch);
            }
        }
        // selain itu diabaikan
    }
}


///////////////////////////////////////////////
//              TRANSAKSI                   //
//////////////////////////////////////////////
void transaksi(int x, int y) {
    FILE *fp = fopen("tiket.dat", "rb");

    if (!fp) {
        gotoxy(x, y);
        printf("0");
        return;
    }

    tiket data;
    int total = 0;

    while (fread(&data, sizeof(tiket), 1, fp)) {
        total++;
    }

    fclose(fp);

    gotoxy(x, y);
    printf("%d", total);
}

void hitungtotalhargatiket() {
    FILE *fp;
    tiket data;
    long total = 0;

    fp = fopen("tiket.dat", "rb");
    if (fp == NULL) {
        gotoxy(37, 30);
        printf("Data tiket belum tersedia!");
        return;
    }

    while (fread(&data, sizeof(tiket), 1, fp)) {
        total += data.harga;
    }

    fclose(fp);

    gotoxy(37, 32);
    printf("Total Pendapatan Tiket : ");
    tampilanhargatiket(total);
}



void readTiketPenumpang() {

    FILE *fp;
    tiket data[1000];
    int total = 0;

    int startX = 37;
    int startY = 12;

    // ===== LEBAR KOLOM =====
    int wNo = 3, wID = 10, wNama = 20, wTelp = 15;
    int wRute = 25, wTgl = 12;

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
        (wRute+2)+(wTgl+2);

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
        printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
               wNo+1,"No",
               wID+1,"ID Tiket",
               wNama+1,"Nama",
               wTelp+1,"Telepon",
               wRute+1,"Rute",
               wTgl+1,"Tanggal");

        gotoxy(startX, row++); printf("%s", garis);

        for (int i = start; i < end; i++) {
            char rute[40];
            sprintf(rute, "%s-%s",
                    data[i].rute_awal,
                    data[i].tujuan);

            gotoxy(startX, row++);
            printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*s|",
                   wNo+1, i+1,
                   wID+1, data[i].id_tiket,
                   wNama+1, data[i].nama_penumpang,
                   wTelp+1, data[i].notlpn,
                   wRute+1, rute,
                   wTgl+1, data[i].tanggal_berangkat);
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


#endif