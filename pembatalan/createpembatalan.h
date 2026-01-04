#ifndef PROJEK_CREATEPEMBATALAN_H
#define PROJEK_CREATEPEMBATALAN_H

#include "../FrameTabel.h"

// ================= STRUKTUR DATA ================= //
typedef struct {
    char id_pembatalan[20];
    char id_pemesanan[20];
    char tanggal_pembatalan[15];
    float pengembalian;
    char id_staf[20];
} pembatalan;

// ================= DEKLARASI ================= //
int getPembatalanCount();

// ================= INPUT ANGKA ================= //
void inputAngka3Digit(char *angka, int row, int col) {
    int i = 0;
    char ch;

    gotoxy(col, row);

    while (i < 3) {
        ch = getch();

        // ESC → batal
        if (ch == 27) {
            angka[0] = '\0';
            return;
        }

        // BACKSPACE
        if (ch == 8 && i > 0) {
            i--;
            gotoxy(col + i, row);
            printf(" ");
            gotoxy(col + i, row);
            continue;
        }

        // HANYA ANGKA
        if (ch >= '0' && ch <= '9') {
            angka[i++] = ch;
            printf("%c", ch);
        }
    }

    // AUTO SELESAI (LOCK)
    angka[3] = '\0';
}


// ================= INPUT TANGGAL ================= //
void inputTanggalpembatalan(char *tgl, int row, int col) {
    int i = 0;
    char ch;

    gotoxy(col, row);

    while (i < 8) {   // DD/MM/YY = 8 karakter
        ch = getch();

        // ESC → batal
        if (ch == 27) {
            tgl[0] = '\0';
            return;
        }

        // BACKSPACE
        if (ch == 8 && i > 0) {
            i--;
            gotoxy(col + i, row);
            printf(" ");
            gotoxy(col + i, row);
            continue;
        }

        // HANYA ANGKA
        if (ch >= '0' && ch <= '9') {

            // posisi slash otomatis
            if (i == 2 || i == 5) {
                tgl[i] = '/';
                printf("/");
                i++;
            }

            tgl[i] = ch;
            printf("%c", ch);
            i++;
        }
    }

    // AUTO SELESAI (tidak bisa input lagi)
    tgl[8] = '\0';
}


// ================= CREATE PEMBATALAN ================= //
void createPembatalan() {
    char n;

    do {
        bentukframe(35, 26, 108, 12);
        gotoxy(70, 26); printf("=== BUAT PEMBATALAN ===");

        FILE *fp = fopen("pembatalan.dat", "ab");
        if (!fp) return;

        pembatalan data;
        char angka[10];

        // ===== ID PEMBATALAN (AUTO PENUH) =====
        int count = getPembatalanCount() + 1;
        sprintf(data.id_pembatalan, "BTL%03d", count);
        gotoxy(37, 27); printf("ID Pembatalan     : %s", data.id_pembatalan);

        // ===== ID PEMESANAN (PSN + ANGKA) =====
        strcpy(data.id_pemesanan, "PSN");
        gotoxy(37, 28); printf("ID Pemesanan      : PSN");
        inputAngka3Digit(angka, 28, 60 );
        if (strlen(angka) == 0) { fclose(fp); return; }
        strcat(data.id_pemesanan, angka);

        // ===== TANGGAL =====
        gotoxy(37, 29); printf("Tanggal Pembatalan: ");
        inputTanggalpembatalan(data.tanggal_pembatalan, 29, 57);
        if (strlen(data.tanggal_pembatalan) == 0) { fclose(fp); return; }

        // ===== PENGEMBALIAN =====
        gotoxy(37, 30); printf("Pengembalian      : 70%%");
        data.pengembalian = 0.7f;

        // ===== ID STAF (STF + ANGKA) =====
        strcpy(data.id_staf, "STF");
        gotoxy(37, 31); printf("ID Staf           : STF");
        inputAngka3Digit(angka, 31, 60);
        if (strlen(angka) == 0) { fclose(fp); return; }
        strcat(data.id_staf, angka);

        // ===== SIMPAN =====
        fwrite(&data, sizeof(pembatalan), 1, fp);
        fclose(fp);

        gotoxy(37, 32); printf("Data pembatalan berhasil disimpan!");
        gotoxy(37, 33); printf("Tambah lagi? (y/n): ");

        while (1) {
            n = getch();
            if (n == 'y' || n == 'Y' || n == 'n' || n == 'N') {
                clearArea(35, 26, 80, 12);
                if (n == 'n' || n == 'N') return;
                break;
            }
        }

    } while (n == 'y' || n == 'Y');
}

// ================= HITUNG DATA ================= //
int getPembatalanCount() {
    FILE *fp = fopen("pembatalan.dat", "rb");
    if (!fp) return 0;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);

    return size / sizeof(pembatalan);
}
void buatdummy_pembatalan_ke_file() {
    FILE *fp;
    pembatalan data;
    int max_data = 40;   // jumlah data dummy

    // ===== DATA TANGGAL DUMMY (DD/MM/YY) =====
    char *tanggal_dummy[] = {
        "01/01/24", "05/01/24", "10/01/24", "15/01/24",
        "20/01/24", "25/01/24", "30/01/24",
        "04/02/24", "09/02/24", "14/02/24"
    };

    int total_tgl = sizeof(tanggal_dummy) / sizeof(tanggal_dummy[0]);

    fp = fopen("pembatalan.dat", "wb");
    if (!fp) {
        printf("ERROR: Gagal membuat pembatalan.dat\n");
        getch();
        return;
    }

    printf("        MEMBUAT DATA DUMMY PEMBATALAN\n\n");

    for (int i = 0; i < max_data; i++) {

        // ===== ID PEMBATALAN (BTL001, BTL002, ...) =====
        sprintf(data.id_pembatalan, "BTL%03d", i + 1);

        // ===== ID PEMESANAN (PSN001 - PSN999) =====
        sprintf(data.id_pemesanan, "PSN%03d", (i % 999) + 1);

        // ===== TANGGAL PEMBATALAN (DD/MM/YY) =====
        strcpy(data.tanggal_pembatalan, tanggal_dummy[i % total_tgl]);

        // ===== PENGEMBALIAN (70%) =====
        data.pengembalian = 0.7f;

        // ===== ID STAF (STF001 - STF015) =====
        sprintf(data.id_staf, "STF%03d", (i % 15) + 1);

        // ===== SIMPAN KE FILE =====
        fwrite(&data, sizeof(pembatalan), 1, fp);
    }

    fclose(fp);

    printf("[✓] Berhasil membuat %d data dummy pembatalan\n", max_data);
    printf("Tekan tombol apapun untuk kembali...");
    getch();
}


#endif
