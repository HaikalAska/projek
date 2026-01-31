#ifndef PROJEK_UPDATE_JADWAL_H
#define PROJEK_UPDATE_JADWAL_H

#include "../FrameTabel.h"
#include "createJadwal.h"

//========================//
// Untuk memperbarui jadwal
//========================//
void perbaruijadwal() {

    int startY = 29;
    int startX = 50;

    FILE *fp, *tmp;
    jadwal j;
    int targetNo = 0, currentNo = 1, found = 0;
    char strNo[10];
    int idx = 0;
    jadwal list[200];
    int totalData = 0;


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
            idx--;
            printf("\b \b");
        }
        else if (ch >= '0' && ch <= '9' && idx < 9) {
            strNo[idx++] = ch;
            printf("%c", ch);
        }
    }

    if (targetNo <= 0) return;

    fp = fopen("jadwal.dat", "rb");
    if (!fp) return;

    // === BACA SEMUA DATA KE ARRAY ===
    while (fread(&list[totalData], sizeof(jadwal), 1, fp)) {
        totalData++;
    }
    fclose(fp);

    if (totalData == 0) return;

    // === BUBBLE SORT BERDASARKAN ID ===
    for (int i = 0; i < totalData - 1; i++) {
        for (int j = 0; j < totalData - i - 1; j++) {
            if (strcmp(list[j].id, list[j + 1].id) > 0) {
                jadwal temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
    tmp = fopen("sampah.dat", "wb");
    if (!tmp) return;

    for (int i = 0; i < totalData; i++) {
        j = list[i];

        if (currentNo == targetNo) {
            found = 1;

            // ============ DATA LAMA ============
            bentukframe(37, 29, 45, 16);
            gotoxy(54, 30); printf("Data Lama");

            gotoxy(40, 32); printf("Tanggal            : %s", j.tanggal);

            gotoxy(40, 33); printf("Kota Asal          : %s", j.kotaAsal);
            gotoxy(40, 34); printf("Kota Tujuan        : %s", j.kotaTujuan);
            gotoxy(40, 35); printf("Jam Berangkat      : %s", j.jamBerangkat);

            char hargaLama[25];
            formatHarga(j.harga, hargaLama);
            gotoxy(40, 36); printf("Harga              : %s", hargaLama);

            gotoxy(40, 37); printf("Armada             : %s", j.nama_armada);
            gotoxy(40, 38); printf("Kategori           : %s", j.kategori);
            gotoxy(40, 39);
            printf(
     "Status             : %-10s",
     strcmp(j.status, "Aktif") == 0 ? "Aktif" : "Nonaktif"
 );


            // ============ DATA BARU ============
            bentukframe(83, 29, 55, 16);
            gotoxy(100, 30); printf("Data Baru");

            gotoxy(86, 32); printf("Tanggal        : ");
            gotoxy(86, 33); printf("Pilih Rute     : ");
            gotoxy(86, 34); printf("Pilih Kendaraan: ");
            gotoxy(86, 35); printf("Status [A/N]   : ");
            gotoxy(86, 36); printf("[SIMPAN PERUBAHAN]");

            gotoxy(86, 38); printf("Kota Asal      : ");
            gotoxy(86, 39); printf("Kota Tujuan    : ");
            gotoxy(86, 40); printf("Jam Berangkat  : ");
            gotoxy(86, 41); printf("Harga          : ");
            gotoxy(86, 42); printf("Armada         : ");
            gotoxy(86, 43); printf("Kategori       : ");

            int selected = 0;
            int total    = 4;
            int edit     = 1;

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

                    int inputX = 103;

                    switch (selected) {

                        case 0:
                            clearArea(inputX, 32, 20, 1);
                            gotoxy(inputX, 32);

                            if (inputtanggaljadwal(j.tanggal, inputX, 32) == -1) {
                                clearArea(inputX, 32, 20, 1);
                            }
                            break;

                        case 1: {
                            clearArea(inputX, 33, 20, 1);
                            clearArea(inputX, 37, 20, 1);
                            clearArea(inputX, 38, 20, 1);
                            clearArea(inputX, 39, 20, 1);
                            clearArea(inputX, 40, 20, 1);

                            if (liatrute() == -1) break;

                            int noRute, ketemu, batal = 0;
                            Rute r;

                            do {
                                ketemu = 0;
                                idx    = 0;
                                char buf[10] = "";

                                clearArea(inputX, 33, 10, 1);
                                gotoxy(103, 33);

                                while (1) {
                                    char ch = _getch();

                                    if (ch == 27) { batal = 1; break; }
                                    if (ch == 13) break;

                                    if (ch == 8 && idx > 0) {
                                        idx--;
                                        printf("\b \b");
                                    }
                                    else if (ch >= '0' && ch <= '9') {
                                        buf[idx++] = ch;
                                        printf("%c", ch);
                                    }
                                }

                                if (batal) break;

                                if (idx == 0) {
                                    gotoxy(103, 33);
                                    printf("Tidak boleh kosong!");
                                    Sleep(1000);
                                    clearArea(103, 33, 25, 1);
                                    gotoxy(103, 33);
                                    continue;
                                }

                                buf[idx] = '\0';
                                noRute = atoi(buf);

                                FILE *fr = fopen("rute.dat", "rb");
                                int cur = 1;

                                while (fr && fread(&r, sizeof(Rute), 1, fr)) {
                                    if (cur == noRute) {
                                        ketemu = 1;
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
                                    gotoxy(103, 33);
                                    printf("Rute tidak ditemukan!");
                                    Sleep(1000);
                                    clearArea(103, 33, 30, 1);
                                    gotoxy(103, 33);
                                }

                            } while (!ketemu);

                            if (batal) break;

                            gotoxy(86, 37); printf("Kota Asal      : %-20s", j.kotaAsal);
                            gotoxy(86, 38); printf("Kota Tujuan    : %-20s", j.kotaTujuan);
                            gotoxy(86, 39); printf("Jam Berangkat  : %-20s", j.jamBerangkat);

                            char hargaBaru[25];
                            formatHarga(j.harga, hargaBaru);
                            gotoxy(86, 40); printf("Harga          : %-20s", hargaBaru);

                            liatjadwal();
                            break;
                        }

                        case 2: {
    clearArea(inputX, 34, 20, 1);
    clearArea(inputX, 42, 20, 1);
    clearArea(inputX, 43, 20, 1);

    if (liatkendaraan() == -1) break;

    int noKen, ketemu, batal = 0;
    char buf[10];
    Kendaraan k;

    do {
        idx = 0;
        ketemu = 0;
        memset(buf, 0, sizeof(buf));

        clearArea(inputX, 34, 10, 1);
        gotoxy(103, 34);

        while (1) {
            char ch = _getch();

            if (ch == 27) { batal = 1; break; }
            if (ch == 13) break;

            if (ch == 8 && idx > 0) {
                idx--;
                printf("\b \b");
            }
            else if (ch >= '0' && ch <= '9') {
                buf[idx++] = ch;
                printf("%c", ch);
            }
        }

        if (batal) break;

        if (idx == 0) {
            gotoxy(103, 34);
            printf("Tidak boleh kosong!");
            Sleep(1000);
            clearArea(103, 34, 25, 1);
            continue;
        }

        noKen = atoi(buf);

        FILE *fk = fopen("kendaraan.dat", "rb");
        int cur = 1;

        while (fk && fread(&k, sizeof(Kendaraan), 1, fk)) {

            // 🔥 FILTER: HANYA KENDARAAN AKTIF
            if (strcmp(k.status, "Aktif") != 0)
                continue;

            if (cur == noKen) {
                ketemu = 1;

                strcpy(j.nama_armada, k.nama_armada);
                strcpy(j.kategori, k.kategori);
                j.kendaraan = noKen;

                gotoxy(86, 42);
                printf("Armada         : %-20s", j.nama_armada);

                gotoxy(86, 43);
                printf("Kategori       : %-20s", j.kategori);

                liatjadwal();
                break;
            }

            cur++;
        }

        if (fk) fclose(fk);

        if (!ketemu) {
            gotoxy(103, 34);
            printf("Kendaraan tidak ditemukan!");
            Sleep(1000);
            clearArea(103, 34, 30, 1);
        }

    } while (!ketemu);

    if (batal) break;
    break;
}

                        case 3: {
                            clearArea(inputX, 35, 10, 1);

                            int temp = -1; // -1 = belum dipilih, 1 = Aktif, 0 = Nonaktif

                            while (1) {
                                gotoxy(86,35);
                                printf("Status [A/N]   : ");
                                char ch = _getch();

                                // ESC → batal
                                if (ch == 27) {
                                    clearArea(inputX, 35, 25, 1);
                                    break;
                                }

                                // ENTER → simpan
                                if (ch == 13) {
                                    if (temp == -1) {
                                        gotoxy(86,36);
                                        printf("tidak boleh kosong!");
                                        Sleep(1000);
                                        clearArea(inputX, 36, 25, 1);
                                        clearArea(inputX, 35, 25, 1);
                                        continue;
                                    } else {
                                        if (temp == 1)
                                            strcpy(j.status, "Aktif");
                                        else
                                            strcpy(j.status, "Nonaktif");
                                        // 🔥 keluar menu edit
                                        break;

                                    }
                                }

                                // A = Aktif
                                if (ch == 'A' || ch == 'a') {
                                    temp = 1;
                                    gotoxy(86,35);
                                    printf("Status [A/N]   : Aktif   ");
                                }

                                // N = Nonaktif
                                if (ch == 'N' || ch == 'n') {
                                    temp = 0;
                                    gotoxy(86,35);
                                    printf("Status [A/N]   : Nonaktif");
                                }
                            }
                            break;
                        }

                        case 4:
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
    }
    else {
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
