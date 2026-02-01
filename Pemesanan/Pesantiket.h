#ifndef PROJEK_CREATETIKET_H
#define PROJEK_CREATETIKET_H

#include "../FrameTabel.h"
#include <time.h>


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

        // ================= HITUNG TOTAL JADWAL =================
        int totalJadwal = 0;
        jadwal all_jadwal[1000];

        FILE *fp_jadwal = fopen("jadwal.dat", "rb");
        if (fp_jadwal) {
            while (fread(&all_jadwal[totalJadwal], sizeof(jadwal), 1, fp_jadwal) == 1) {
                totalJadwal++;
            }
            fclose(fp_jadwal);
        }

        // Cek apakah ada jadwal
        if (totalJadwal == 0) {
            gotoxy(37, 30);
            printf("Tidak ada jadwal tersedia!");
            getch();
            fclose(fp_tiket);
            return;
        }

        int count = getTiketCount() + 1;
        sprintf(data.id_tiket, "TKT%03d", count);

        gotoxy(37, 28);
        printf("ID Tiket         : %s", data.id_tiket);

        // ================= INPUT NOMOR JADWAL =================
        int nomor_jadwal;

        gotoxy(37, 29);
        printf("No Jadwal        : ");

        while (1) {
            nomor_jadwal = inputNoJadwal(56, 29);

            if (nomor_jadwal == -1) {
                fclose(fp_tiket);
                return;
            }

            if (nomor_jadwal == 0) {
                gotoxy(56, 30);
                printf("Nomor tidak boleh kosong!");
                Sleep(1500);
                gotoxy(56, 30);
                printf("                          ");
                gotoxy(56, 29);
                printf("          ");
                gotoxy(56, 29);
                continue;
            }

            if (nomor_jadwal < 1 || nomor_jadwal > totalJadwal) {
                gotoxy(56, 30);
                printf("Nomor jadwal tidak ada!");
                Sleep(1500);
                gotoxy(56, 30);
                printf("                          ");
                gotoxy(56, 29);
                printf("          ");
                gotoxy(56, 29);
                continue;
            }

            break;
        }

        // ================= AMBIL DATA JADWAL =================
        jadwal_data = all_jadwal[nomor_jadwal - 1];

        // ================= COPY DATA JADWAL =================
        strcpy(data.rute_awal, jadwal_data.kotaAsal);
        strcpy(data.tujuan, jadwal_data.kotaTujuan);
        strcpy(data.nama_armada, jadwal_data.nama_armada);
        strcpy(data.jam_berangkat, jadwal_data.jamBerangkat);
        strcpy(data.tanggal_berangkat, jadwal_data.tanggal);
        data.harga = jadwal_data.harga;

        gotoxy(37, 30); printf("Rute             : %s → %s", data.rute_awal, data.tujuan);
        gotoxy(37, 31); printf("Armada           : %s", data.nama_armada);
        gotoxy(37, 32); printf("Jam Berangkat    : %s", jadwal_data.jamBerangkat);
        gotoxy(37, 33); printf("tanggal Berangkat: %s ", data.tanggal_berangkat);
        gotoxy(37, 34); printf("Harga            : ");
        tampilanhargatiket(data.harga);

        // NAMA
        gotoxy(37, 36);
        printf("Nama Penumpang   : ");
        setPointer(37, 57);
        INPUTNama(data.nama_penumpang);
        if (strlen(data.nama_penumpang) == 0) {
            fclose(fp_tiket);
            return;
        }

        // NO TELP
        gotoxy(37, 37);
        printf("No. Telepon      : ");
        inputNoTelp(data.notlpn, 56, 37);
        if (strlen(data.notlpn) == 0) {
            fclose(fp_tiket);
            return;
        }

        gotoxy(37, 38);
        printf("Email            : ");
        inputEmailGmail(data.Email, 56, 38);
        if (strlen(data.Email) == 0) {
            fclose(fp_tiket);
            return;
        }

        gotoxy(37, 39);
        printf("Metode Bayar     : ");
        inputPaymentMethod(data.metode_bayar, 39, 56);
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
                gotoxy(107, 37); printf("           ");
                gotoxy(107, 40); printf("           ");
                gotoxy(107, 41); printf("           ");

                gotoxy(107, 37);
                dibayar = inputangka7digit(107, 37, &escPressed);

                if (escPressed) {
                    fclose(fp_tiket);
                    return;
                }

                gotoxy(107, 37);
                tampilanhargatiket(dibayar);

                kembalian = dibayar - data.harga;

                if (kembalian < 0) {
                    gotoxy(90, 41);
                    printf("Uang kurang!");
                    Sleep(800);
                    gotoxy(90, 41);
                    printf("             ");
                    continue;
                }

            } while (kembalian < 0);

            gotoxy(107, 40);
            tampilanhargatiket(kembalian);
        }
        else if (strcmp(data.metode_bayar, "Cashless") == 0) {
            gotoxy(103, 35); printf("QRIS");
            gotoxy(90, 37); printf("Scan QR Code berikut:");
            system("cls");
            printQRCodeFromFile("QR.txt", 53, 7);
            gotoxy(75, 6); printf("Rp %ld", data.harga);

            gotoxy(60, 35); printf("Memproses pembayaran");

            for (int i = 0; i < 3; i++) {
                printf(".");
                fflush(stdout);
                Sleep(500);
            }

            gotoxy(50, 57);
            printf("Pembayaran berhasil!");
            Sleep(1000);
        }

        getCurrentDate(data.tanggal_booking);
        strcpy(data.status, "Aktif");

        gotoxy(37, 40); printf("Tgl Booking      : %s", data.tanggal_booking);
        gotoxy(37, 41); printf("Status           : %s", data.status);
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

        if (ch == 27) {
            metode[0] = '\0';
            return;
        }

        else if (ch == 'C' || ch == 'c') {
            strcpy(metode, "Cash");

            gotoxy(inputX, row);
            printf("            ");
            gotoxy(inputX, row);
            printf("Cash");

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

        if (ch == 13) {
            if (i > 0) {
                buffer[i] = '\0';
                return atoi(buffer);
            } else {
                return 0;
            }
        }
        else if (ch == 27) {
            return -1;
        }
        else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if (ch >= '0' && ch <= '9') {
            if (i < 5) {
                buffer[i++] = ch;
                printf("%c", ch);
            }
        }
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

        if (ch == 13) {
            if (i > 0) {
                buffer[i] = '\0';
                sprintf(email, "%s@gmail.com", buffer);

                gotoxy(x, y);
                printf("%s@gmail.com", buffer);

                return;
            }
        }
        else if (ch == 27) {
            email[0] = '\0';
            return;
        }
        else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
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


/////////// HU
void hitungtotalhargatiket(int x, int y) {
    FILE *fp;
    tiket data;
    long total_aktif = 0;
    long total_biaya_batal = 0;

    fp = fopen("tiket.dat", "rb");
    if (fp == NULL) {
        gotoxy(x, y);
        printf("Rp 0");
        return;
    }

    while (fread(&data, sizeof(tiket), 1, fp)) {
        if (strcmp(data.status, "Aktif") == 0) {
            total_aktif += data.harga;
        }
        else if (strcmp(data.status, "Batal") == 0) {
            total_biaya_batal += data.hargaTbatal;
        }
    }

    fclose(fp);

    long pendapatan_bersih = total_aktif + total_biaya_batal;

    gotoxy(x, y);
    tampilanhargatiket(pendapatan_bersih);
}
///////////////////////////////////////////////////////////////




/////////////////MENU LAPORAN PEMBELIAN//////////////////////
void Pembelian(int x, int y) {
    FILE *fp = fopen("tiket.dat", "rb");

    if (!fp) {
        gotoxy(x, y);
        printf("0");
        return;
    }

    tiket data;
    int total = 0;

    while (fread(&data, sizeof(tiket), 1, fp)) {
        if (strcmp(data.status, "Aktif") == 0) {
            total++;
        }
    }

    fclose(fp);

    gotoxy(x, y);
    printf("%d", total);
}
/////////////////////////////////////////////////////////////////




//////////////MENU LAPORAN PEMBATALAN///////////////////
void Pembatalan(int x, int y) {
    FILE *fp = fopen("tiket.dat", "rb");

    if (!fp) {
        gotoxy(x, y);
        printf("0");
        return;
    }

    tiket data;
    int total = 0;

    while (fread(&data, sizeof(tiket), 1, fp)) {
        if (strcmp(data.status, "Batal") == 0) {
            total++;
        }
    }

    fclose(fp);

    gotoxy(x, y);
    printf("%d", total);
}

void TotalBiayaPembatalan(int x, int y) {
    FILE *fp = fopen("tiket.dat", "rb");

    if (!fp) {
        gotoxy(x, y);
        printf("Rp 0");
        return;
    }

    tiket data;
    long total_biaya = 0;

    while (fread(&data, sizeof(tiket), 1, fp)) {
        if (strcmp(data.status, "Batal") == 0) {
            total_biaya += data.hargaTbatal;
        }
    }

    fclose(fp);

    gotoxy(x, y);
    printf("Rp ");
    tampilanhargatiket(total_biaya);
}




// ================  Helper untuk center teks
void printCenter(int width, char *text) {
    int len = strlen(text);
    int padding = (width - len) / 2;
    if (padding < 0) padding = 0;
    printf("%*s%-*s", padding, "", width - padding, text);
}



void readTiketPenumpang() {

    FILE *fp;
    tiket data[1000];
    int total = 0;
    int startX = 35;
    int startY = 11;

    int wNo = 3, wID = 8, wNama = 18, wTelp = 12;
    int wRute = 17, wTgl = 10, wJam = 8, wStatus = 7, wHarga = 15;

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

    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            // Urutkan dari terbesar ke terkecil (descending)
            if (strcmp(data[i].id_tiket, data[j].id_tiket) < 0) {
                tiket temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }


    int total_pages = (total + 25 - 1) / 25;
    int current_page = 1;
    char key;

    int totalWidth =
        1 + (wNo+2)+(wID+2)+(wNama+2)+(wTelp+2)+
        (wRute+2)+(wTgl+2)+(wJam+2)+(wStatus+2)+(wHarga+3);

    char garis[300];
    memset(garis, '-', totalWidth);
    garis[totalWidth] = '\0';

    do {
        int start = (current_page - 1) * 25;
        int end = start + 25;
        if (end > total) end = total;

        clearArea(startX, startY + 1, totalWidth, 30);

        gotoxy(80, 12);
        printf("=== DAFTAR TIKET PENUMPANG ===");

        int row = startY + 2;

        gotoxy(startX, row++); printf("%s", garis);

        gotoxy(startX, row);  // ← Tambahkan gotoxy sebelum header
        printf("|");
        printCenter(wNo+1, "No"); printf("|");
        printCenter(wID+1, "ID Tiket"); printf("|");
        printCenter(wNama+1, "Nama"); printf("|");
        printCenter(wTelp+1, "Telepon"); printf("|");
        printCenter(wRute+1, "Rute"); printf("|");
        printCenter(wTgl+1, "Tanggal"); printf("|");
        printCenter(wJam+1, "Berangkat"); printf("|");          // ← Tambahkan Jam
        printCenter(wStatus+1, "Status"); printf("|");
        printCenter(wHarga+2, "Harga"); printf("|");      // ← Tambahkan Harga
        row++;                                             // ← Increment row manual

        gotoxy(startX, row++); printf("%s", garis);

        for (int i = start; i < end; i++) {

            char rute[60];
            sprintf(rute, "%s-%s",data[i].rute_awal, data[i].tujuan);

            char NamaTampil[20];

            if (strlen(data[i].nama_penumpang) > wNama) {
                strncpy(NamaTampil, data[i].nama_penumpang, wNama - 3);
                NamaTampil[wNama - 3] = '\0';
                strcat(NamaTampil, "-");
            }else {
                strcpy(NamaTampil, data[i].nama_penumpang);
            }

            char ruteTampil[25];

            if (strlen(rute) > wRute) {
                strncpy(ruteTampil, rute, wRute - 3);
                ruteTampil[wRute - 3] = '\0';
                strcat(ruteTampil, "...");
            } else {
                strcpy(ruteTampil, rute);
            }

            gotoxy(startX, row++);

            printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
                   wNo+1, i+1,
                   wID+1, data[i].id_tiket,
                   wNama+1, NamaTampil,
                   wTelp+1, data[i].notlpn,
                   wRute+1, ruteTampil,
                   wTgl+1, data[i].tanggal_berangkat,
                   wJam+1, data[i].jam_berangkat,
                   wStatus+1, data[i].status);

            char hargaStr[30];

            if (strcmp(data[i].status, "Batal") == 0) {
                formatHarga(data[i].harga, hargaStr);
            } else {
                formatHarga(data[i].harga, hargaStr);
            }

            printf(" %*s|", wHarga+1, hargaStr);
        }

        gotoxy(startX, row++); printf("%s", garis);

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



#endif