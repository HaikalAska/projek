#ifndef PROJEK_UPDATE_JADWAL_H
#define PROJEK_UPDATE_JADWAL_H

#include "../FrameTabel.h"
#include "createJadwal.h"
//========================//
//Untuk memperbarui jadwal//
//========================//
void perbaruijadwal() {

    int startY = 29;
    int startX = 50;

    FILE *fp, *tmp;
    jadwal j;
    int targetNo = 0, currentNo = 1, found = 0;
    char strNo[10];
    int idx = 0;

    // ================= INPUT NOMOR =================
    gotoxy(3, 25);
    printf("Pilih No Urut : ");
    gotoxy(20, 25);
    printf("          ");
    gotoxy(20, 25);

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

    while (fread(&j, sizeof(jadwal), 1, fp)) {

        if (currentNo == targetNo) {
            found = 1;

            // ============ MENU NAVIGASI ============
            bentukframe(3, 29, 27, 10);
            gotoxy(5,30); printf("===  MENU NAVIGASI  ===");
            gotoxy(4,32); printf("NAVIGASI [↑ ↓]");
            gotoxy(4,34); printf("[ENTER] Pilih");
            gotoxy(4,36); printf("[ESC] Keluar");

            // ============ DATA LAMA ============
            bentukframe(37, 29, 45, 16);
            gotoxy(54, 30); printf("Data Lama");

            gotoxy(40, 32);  printf("Tanggal            : %s", j.tanggal);
            gotoxy(40, 33);  printf("No Urut Rute       : %d", j.rute);
            gotoxy(40, 34);  printf("No Urut Kendaraan  : %d", j.kendaraan);

            gotoxy(40, 36);  printf("Kota Asal          : %s", j.kotaAsal);
            gotoxy(40, 37);  printf("Kota Tujuan        : %s", j.kotaTujuan);
            gotoxy(40, 38);  printf("Jam Berangkat      : %s", j.jamBerangkat);

            char hargaLama[25];
            formatHarga(j.harga, hargaLama);
            gotoxy(40, 39);  printf("Harga              : %s", hargaLama);

            gotoxy(40, 40); printf("Armada             : %s", j.nama_armada);
            gotoxy(40, 41); printf("Kategori           : %s", j.kategori);


            // ============ DATA BARU ============
            bentukframe(83, 29, 55, 16);
            gotoxy(100, 30); printf("Data Baru");

            gotoxy(86,32); printf("Tanggal        : ");
            gotoxy(86,33); printf("Pilih Rute     : ");
            gotoxy(86,34); printf("Pilih Kendaraan: ");
            gotoxy(86,35); printf("[SIMPAN PERUBAHAN]");

            gotoxy(86,37); printf("Kota Asal      : ");
            gotoxy(86,38); printf("Kota Tujuan    : ");
            gotoxy(86,39); printf("Jam Berangkat  : ");
            gotoxy(86,40); printf("Harga          : ");

            gotoxy(86,41); printf("Armada         : ");
            gotoxy(86,42); printf("Kategori       : ");

            int selected = 0;
            int total = 3;
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

                    int inputX = 102;
                    char bufferHarga[20];

                    switch (selected) {

                        case 0:
                            clearArea(inputX, 32, 20, 1);
                            gotoxy(inputX, 32);

                            if (inputtanggaljadwal(j.tanggal) == -1) {
                                // ESC ditekan → batal input
                                clearArea(inputX, 32, 20, 1);
                            }

                            break;

                        case 1: {

                            if (liatrute() == -1) {
                                // user tekan ESC di tabel
                                break;
                            }

                            int noRute;
                            int ketemu;
                            Rute r;

                            do {
                                ketemu = 0;
                                idx = 0;
                                char buf[10] = "";

                                clearArea(inputX, 33, 10, 1);
                                gotoxy(103, 33);

                                // ===== INPUT ANGKA SAJA =====
                                while (1) {
                                    char ch = _getch();

                                    if (ch == 27) break;   // ESC
                                    if (ch == 13) break;   // ENTER

                                    if (ch == 8 && idx > 0) {
                                        idx--;
                                        printf("\b \b");
                                    }
                                    else if (ch >= '0' && ch <= '9') {
                                        buf[idx++] = ch;
                                        printf("%c", ch);
                                    }
                                }

                                buf[idx] = '\0';
                                noRute = atoi(buf);

                                FILE *fr = fopen("rute.dat", "rb");
                                int cur = 1;

                                while (fr && fread(&r, sizeof(Rute), 1, fr)) {
                                    if (cur == noRute) {
                                        ketemu = 1;

                                        // ===== ISI DATA OTOMATIS =====
                                        strcpy(j.kotaAsal, r.kotaAsal);
                                        strcpy(j.kotaTujuan, r.kotaTujuan);
                                        strcpy(j.jamBerangkat, r.jamBerangkat);
                                        j.harga = r.harga;
                                        j.rute  = noRute;

                                        break;
                                    }
                                    cur++;
                                }
                                if (fr) fclose(fr);

                                if (!ketemu) {
                                    gotoxy(103,33);
                                    printf("Rute tidak ditemukan!");
                                    Sleep(1000);
                                    clearArea(103,33,30,1);
                                }

                            } while (!ketemu);   // 🔑 INI KUNCI UTAMA

                            // ===== REFRESH TAMPILAN DATA BARU =====
                            gotoxy(86,37); printf("Kota Asal      : %-20s", j.kotaAsal);
                            gotoxy(86,38); printf("Kota Tujuan    : %-20s", j.kotaTujuan);
                            gotoxy(86,39); printf("Jam Berangkat  : %-20s", j.jamBerangkat);

                            char hargaBaru[25];
                            formatHarga(j.harga, hargaBaru);
                            gotoxy(86,40); printf("Harga          : %-20s", hargaBaru);

                            // ===== KEMBALI KE DAFTAR JADWAL =====
                            // getch();          // (opsional) pause sebentar
                            liatjadwal();     // 🔑 INI DIA TEMPATNYA

                            break;
                        }


                        case 2: {

                            if (liatkendaraan() == -1) {
                                // user tekan ESC di tabel
                                break;
                            }

                            int noKen = 0, idx = 0;
                            char buf[10] = "";
                            Kendaraan k;
                            int ketemu = 0;

                            clearArea(inputX, 34, 10, 1);
                            gotoxy(103, 34);

                            // ===== INPUT ANGKA =====
                            while (1) {
                                char ch = _getch();
                                if (ch == 27) break;
                                if (ch == 13) break;
                                if (ch == 8 && idx > 0) {
                                    idx--; printf("\b \b");
                                }
                                else if (ch >= '0' && ch <= '9') {
                                    buf[idx++] = ch;
                                    printf("%c", ch);
                                }
                            }
                            buf[idx] = 0;
                            noKen = atoi(buf);

                            FILE *fk = fopen("kendaraan.dat", "rb");
                            int cur = 1;

                            while (fk && fread(&k, sizeof(Kendaraan), 1, fk)) {
                                if (cur == noKen) {
                                    ketemu = 1;

                                    // ===== ISI DATA =====
                                    strcpy(j.nama_armada, k.nama_armada);
                                    strcpy(j.kategori, k.kategori);
                                    j.kendaraan = noKen;

                                    // ===== INI YANG KAMU TANYA (TARO DI SINI) =====
                                    gotoxy(86,41); printf("Armada         : %-20s", j.nama_armada);
                                    gotoxy(86,42); printf("Kategori       : %-20s", j.kategori);

                                    liatjadwal();

                                    break;
                                }
                                cur++;
                            }
                            if (fk) fclose(fk);

                            if (!ketemu) {
                                gotoxy(103,34);
                                printf("Kendaraan tidak ditemukan!");
                                Sleep(1000);
                                clearArea(103,34,30,1);
                            }

                            break;
                        }


                        case 3:
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

            fwrite(&j, sizeof(jadwal), 1, tmp);
        }
        else {
            fwrite(&j, sizeof(jadwal), 1, tmp);
        }

        currentNo++;
    }

    fclose(fp);
    fclose(tmp);

    if (found) {
        remove("jadwal.dat");
        rename("sampah.dat", "jadwal.dat");
        gotoxy(86, 35); printf("Data Berhasil Di Update!");
    } else {
        remove("sampah.dat");
        gotoxy(3, 26);
        printf("Pilihan tidak valid!");
        Sleep(1000);
        gotoxy(3, 26);
        printf("                     ");
    }

    _getch();
}

#endif