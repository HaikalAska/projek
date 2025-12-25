//
// Created by Asus on 16/12/2025.
//

#ifndef PROJEK_CREATEPEMBATALAN_H
#define PROJEK_CREATEPEMBATALAN_H


#include "../FrameTabel.h"

// ================= STRUKTUR DATA ================= //
typedef struct {
    char id_pembatalan[20];
    char id_pemesanan[20];
    float pengembalian;
} pembatalan;

// ================= DEKLARASI ================= //
int getPembatalanCount();
void inputAngka(char *data, int row, int col, int maxLen) {
    int i = 0;
    char ch;

    gotoxy(col, row);

    while (1) {
        ch = getch();

        // ENTER
        if (ch == 13) {
            if (i == 0) {
                gotoxy(col, row);
                printf("Tidak boleh kosong!");
                Sleep(800);
                clearArea(col, row, maxLen, 1);
                gotoxy(col, row);
                i = 0;
                continue;
            }
            data[i] = '\0';
            break;
        }

        // ESC
        else if (ch == 27) {
            data[0] = '\0';
            break;
        }

        // BACKSPACE
        else if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        }

        // HANYA ANGKA
        else if (ch >= '0' && ch <= '9') {
            if (i < maxLen - 1) {
                data[i++] = ch;
                printf("%c", ch);
            }
        }
    }
}

// ================= CREATE PEMBATALAN ================= //
void createPembatalan() {
    char n;

    do {
        bentukframe(35, 27, 108, 9);
        gotoxy(75, 27); printf("=== BUAT PEMBATALAN ===");

        FILE *fp = fopen("pembatalan.dat", "ab");
        if (!fp) return;

        pembatalan data;

        // ================= ID PEMBATALAN (AUTO) ================= //
        int count = getPembatalanCount() + 1;
        sprintf(data.id_pembatalan, "BTL%03d", count);

        gotoxy(37, 28);
        printf("ID Pembatalan : %s", data.id_pembatalan);

        // ================= ID PEMESANAN ================= //
        gotoxy(37, 29); printf("ID Pemesanan  : ");
        inputAngka(data.id_pemesanan, 29, 53, 20);

        if (strlen(data.id_pemesanan) == 0) {
            fclose(fp);
            return;
        }

        // ================= PENGEMBALIAN (AUTO 70%) ================= //
        gotoxy(37, 30); printf("Pengembalian  : ");
        gotoxy(53, 30);
        printf("70%%");               // tampil di layar

        // tunggu ENTER atau ESC
        char ch;
        while (1) {
            ch = getch();
            if (ch == 13) {          // ENTER
                data.pengembalian = 0.7f;  // simpan 70%
                break;
            }
            else if (ch == 27) {     // ESC
                fclose(fp);
                return;
            }
        }


        // ================= SIMPAN ================= //
        fwrite(&data, sizeof(pembatalan), 1, fp);
        fclose(fp);

        gotoxy(37, 31);
        printf("Data pembatalan berhasil dibuat!");

        gotoxy(37, 32);
        printf("Tambah lagi? (y/n): ");

        while (1) {
            n = _getch();
            if (n == 27) {
                clearArea(35, 27, 80, 9);
                return;
            }
            if (n == 'y' || n == 'Y' || n == 'n' || n == 'N') {
                clearArea(35, 27, 80, 9);
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
    int max_data = 30;   // jumlah data dummy

    fp = fopen("pembatalan.dat", "wb");
    if (!fp) {
        printf("ERROR: Gagal membuat pembatalan.dat\n");
        getch();
        return;
    }

    printf("        MEMBUAT DATA DUMMY PEMBATALAN\n\n");

    for (int i = 0; i < max_data; i++) {

        // ================= ID PEMBATALAN (AUTO) =================
        sprintf(data.id_pembatalan, "BTL%03d", i + 1);

        // ================= ID PEMESANAN (ANGKA SAJA) =================
        // sesuai inputAngka()
        sprintf(data.id_pemesanan, "%d", 0 + i + 1);
        // contoh: 1001, 1002, 1003, ...

        // ================= PENGEMBALIAN (70%) =================
        data.pengembalian = 0.7f;   // 70%

        // ================= SIMPAN =================
        fwrite(&data, sizeof(pembatalan), 1, fp);
    }

    fclose(fp);

    printf("[✓] Berhasil membuat %d data dummy pembatalan\n", max_data);
    printf("Tekan tombol apapun untuk kembali...");
    getch();
}



#endif //PROJEK_CREATEPEMBATALAN_H