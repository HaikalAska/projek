#ifndef PROJEK_UPDATE_JADWAL_H
#define PROJEK_UPDATE_JADWAL_H

#include "../FrameTabel.h"
#include "createJadwal.h"
#include "../rute/createrute.h"

void inputJams(char jam[], int x, int y) {
    char ch;
    int pos = 0;

    while (pos < 5) {
        ch = _getch();

        // BACKSPACE
        if (ch == 8) {
            if (pos > 0) {
                pos--;
                gotoxy(x + pos, y);
                printf(" ");
                gotoxy(x + pos, y);
            }
            continue;
        }

        // JAM PULUHAN (0–2)
        if (pos == 0 && ch >= '0' && ch <= '2') {
            gotoxy(x + pos, y);
            jam[pos++] = ch;
            printf("%c", ch);
        }

        // JAM SATUAN
        else if (pos == 1) {
            if ((jam[0] == '2' && ch <= '3') ||
                (jam[0] != '2' && ch <= '9')) {
                gotoxy(x + pos, y);
                jam[pos++] = ch;
                printf("%c", ch);
                }
        }

        // AUTO :
        else if (pos == 2) {
            gotoxy(x + pos, y);
            jam[pos++] = ':';
            printf(":");
        }

        // MENIT PULUHAN (0–5)
        else if (pos == 3 && ch >= '0' && ch <= '5') {
            gotoxy(x + pos, y);
            jam[pos++] = ch;
            printf("%c", ch);
        }

        // MENIT SATUAN (0–9)
        else if (pos == 4 && ch >= '0' && ch <= '9') {
            gotoxy(x + pos, y);
            jam[pos++] = ch;
            printf("%c", ch);
        }
    }

    jam[5] = '\0';
}


void updateJadwal() {

    int startY = 29;
    int startX = 50;

    FILE *fp, *tmp;
    jadwal data;
    int targetNo = 0, currentNo = 1, found = 0;
    char strNo[10];
    int idx = 0;

    // ================= INPUT NOMOR =================
    gotoxy(3, 25); printf("Pilih No Urut: ");

    while (1) {
        char ch = _getch();
        if (ch == 27) return;
        if (ch == 13) {
            strNo[idx] = '\0';
            targetNo = atoi(strNo);
            break;
        }
        if (ch == 8 && idx > 0) {
            idx--; printf("\b \b");
        }
        else if (ch >= '0' && ch <= '9' && idx < 9) {
            strNo[idx++] = ch;
            printf("%c", ch);
        }
    }

    if (targetNo <= 0) return;

    fp  = fopen("jadwal.dat", "rb");
    tmp = fopen("sampah.dat", "wb");
    if (!fp || !tmp) return;

    while (fread(&data, sizeof(jadwal), 1, fp)) {

        if (currentNo == targetNo) {
            found = 1;

            // ============ MENU NAVIGASI ============
            bentukframe(3, 29, 27, 10);
            gotoxy(5,30); printf("===  MENU NAVIGASI  ===");
            gotoxy(4,32); printf("NAVIGASI [↑ ↓]");
            gotoxy(4,34); printf("[ENTER] Pilih");
            gotoxy(4,36); printf("[ESC] Keluar");

            // ============ DATA LAMA ============
            bentukframe(37, 29, 45, 12);
            gotoxy(54, 30); printf("Data Lama");

            gotoxy(40, startY + 3);  printf("Tanggal       : %s", data.tanggal);
            gotoxy(40, startY + 4);  printf("Kota Asal     : %s", data.kotaAsal);
            gotoxy(40, startY + 5);  printf("Kota Tujuan   : %s", data.kotaTujuan);
            gotoxy(40, startY + 6);  printf("Jam Berangkat : %s", data.jamBerangkat);
            char hargaLama[25];
            formatHarga((int)data.harga, hargaLama);

            gotoxy(40, startY + 7);
            printf("Harga         : %s", hargaLama);

            gotoxy(40, startY + 8);  printf("Armada        : %s", data.armada);
            gotoxy(40, startY + 9);  printf("Kategori      : %s", data.kategori);

            // ============ DATA BARU ============
            bentukframe(83, 29, 55, 12);
            gotoxy(100, 30); printf("Data Baru");

            gotoxy(86,32); printf("Tanggal       : ");
            gotoxy(86,33); printf("Kota Asal     : ");
            gotoxy(86,34); printf("Kota Tujuan   : ");
            gotoxy(86,35); printf("Jam Berangkat : ");
            gotoxy(86,36); printf("Harga         : ");
            gotoxy(86,37); printf("Armada        : ");
            gotoxy(86,38); printf("Kategori      : ");
            gotoxy(86,39); printf("[ SIMPAN PERUBAHAN ]");

            int selected = 0;
            int total = 7;
            int edit = 1;

            while (edit) {

                for (int i = 0; i <= total; i++) {
                    gotoxy(83, 32 + i);
                    printf(i == selected ? ">>" : "│ ");
                }

                int ch = _getch();

                if (ch == 0 || ch == 224) {
                    ch = _getch();
                    if (ch == 72) selected--;
                    if (ch == 80) selected++;
                    if (selected < 0) selected = total;
                    if (selected > total) selected = 0;
                }

                else if (ch == 13) {

                    int inputX = 102; // FIX POSISI INPUT

                    switch (selected) {

                        case 0:
                            clearArea(inputX, 32, 15, 1);
                            inputTanggals(data.tanggal, inputX, 32);
                            break;

                        case 1:
                            clearArea(inputX, 33, 20, 1);
                            gotoxy(inputX, 33);
                            fgets(data.kotaAsal, sizeof(data.kotaAsal), stdin);
                            data.kotaAsal[strcspn(data.kotaAsal, "\n")] = 0;
                            break;

                        case 2:
                            clearArea(inputX, 34, 20, 1);
                            gotoxy(inputX, 34);
                            fgets(data.kotaTujuan, sizeof(data.kotaTujuan), stdin);
                            data.kotaTujuan[strcspn(data.kotaTujuan, "\n")] = 0;
                            break;

                        case 3:
                            clearArea(inputX, 35, 8, 1);
                            inputJams(data.jamBerangkat, inputX, 35);
                            break;


                        case 4: {
                            int hargaInput;
                            char hargaFmt[25];

                            clearArea(inputX, 36, 20, 1);
                            gotoxy(inputX, 36);

                            scanf("%d", &hargaInput);
                            fflush(stdin);

                            data.harga = (float)hargaInput;

                            formatHarga(hargaInput, hargaFmt);

                            gotoxy(inputX, 36);
                            printf("%s", hargaFmt);
                            break;
                        }

                        case 5:
                            clearArea(inputX, 37, 20, 1);
                            gotoxy(inputX, 37);
                            fgets(data.armada, sizeof(data.armada), stdin);
                            data.armada[strcspn(data.armada, "\n")] = 0;
                            break;

                        case 6:
                            clearArea(inputX, 38, 20, 1);
                            inputKategori(data.kategori, inputX, 38);
                            break;

                        case 7:
                            edit = 0;
                            break;
                    }
                }



                else if (ch == 27) {
                    fclose(fp);
                    fclose(tmp);
                    remove("sampah.dat");
                    return;
                }
            }

            fwrite(&data, sizeof(jadwal), 1, tmp);
        }
        else {
            fwrite(&data, sizeof(jadwal), 1, tmp);
        }

        currentNo++;
    }

    fclose(fp);
    fclose(tmp);

    if (found) {
        remove("jadwal.dat");
        rename("sampah.dat", "jadwal.dat");
        gotoxy(86, startY + 18); printf("Data Berhasil Di Update!");
    } else {
        remove("sampah.dat");
        gotoxy(35, 30); printf("Nomor urut tidak ditemukan!");
    }

    _getch();
}

#endif