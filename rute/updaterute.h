//
// Created by ASUS on 12/14/2025.
//

#ifndef PROJEK_UPDATERUTE_H
#define PROJEK_UPDATERUTE_H

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "../FrameTabel.h"
#include "createrute.h"

void renderDataBaru(Rute data) {
    bentukframe(85, 29, 55, 14);
    gotoxy(109, 30); printf("DATA BARU");

    gotoxy(90,32); printf("Kota Asal    : %s ", data.kotaAsal);
    gotoxy(90,33); printf("Kota Tujuan  : %s ", data.kotaTujuan);
    gotoxy(90,34); printf("Harga        : ");
    gotoxy(90,35); printf("Berangkat    : %s ", data.jamBerangkat);
    gotoxy(90,36); printf("Tiba         : %s ", data.jamTiba);
    gotoxy(90,37); printf("Status       : %s ", data.statusRute);
    gotoxy(90,38); printf("[ SIMPAN ]");
}

void updaterute() {
    FILE *fp, *temp;
    Rute data;
    Rute ruteList[1000];  // ← Tambahkan array untuk menyimpan semua rute
    int targetNo = 0, currentNo = 1, found = 0;
    char strNo[10];
    int idx = 0;
    int totalRute = getRuteCount();  // Hitung total rute yang ada

    // ================= VALIDASI: CEK APAKAH ADA DATA =================
    if (totalRute == 0) {
        gotoxy(3, 27);
        printf("Tidak ada data rute!");
        getch();
        return;
    }

    fp = fopen("rute.dat", "rb");
    if (!fp) return;

    int count = 0;
    while (fread(&ruteList[count], sizeof(Rute), 1, fp) == 1) {
        count++;
    }
    fclose(fp);

    // Bubble Sort berdasarkan ID (terbesar ke terkecil)
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(ruteList[i].id, ruteList[j].id) < 0) {
                Rute temp = ruteList[i];
                ruteList[i] = ruteList[j];
                ruteList[j] = temp;
            }
        }
    }

    // ================= INPUT NOMOR URUT =================
    while (1) {
        idx = 0;
        memset(strNo, 0, sizeof(strNo));

        gotoxy(3, 25);
        printf("Pilih No Urut Rute:");
        gotoxy(21 + (totalRute >= 10 ? 2 : 1), 25);
        printf("    "); // Bersihkan input sebelumnya
        gotoxy(21 + (totalRute >= 10 ? 2 : 1), 25);

        while (1) {
            char ch = _getch();

            // ESC → batal
            if (ch == 27) return;

            // ENTER
            if (ch == 13) {
                if (idx == 0) {
                    gotoxy(3, 26);
                    printf("tidak boleh kosong!");
                    Sleep(1500);
                    gotoxy(3, 26);
                    printf("                      ");
                    break; // Kembali ke input ulang
                }

                strNo[idx] = '\0';
                targetNo = atoi(strNo);

                // Validasi range
                if (targetNo < 1 || targetNo > totalRute) {
                    gotoxy(3, 26);
                    printf("Nomor urut tidak valid!");
                    Sleep(1500);
                    gotoxy(3, 26);
                    printf("                       ");
                    break; // Kembali ke input ulang
                }

                // Input valid, keluar dari loop
                goto inputValid;
            }

            // BACKSPACE
            if (ch == 8 && idx > 0) {
                idx--;
                printf("\b \b");
            }

            // ANGKA
            if (ch >= '0' && ch <= '9' && idx < 9) {
                strNo[idx++] = ch;
                printf("%c", ch);
            }
        }
    }

    inputValid:
        // Ambil data rute yang dipilih dari array yang sudah di-sort
        data = ruteList[targetNo - 1];

    fp   = fopen("rute.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (!fp || !temp) return;

    // ================= PROSES UPDATE =================
    Rute tempData;  // ← Buat variabel baru untuk baca file

    while (fread(&tempData, sizeof(Rute), 1, fp)) {  // ← Baca ke tempData, bukan data

        // Cari berdasarkan ID, bukan currentNo
        if (strcmp(tempData.id, data.id) == 0) {  // ← Bandingkan ID
            found = 1;

            // ========= DATA LAMA =========
            bentukframe(37, 29, 45, 14);
            gotoxy(55, 30); printf("DATA LAMA");

            gotoxy(39, 32); printf("Kota Asal    : %s", data.kotaAsal);
            gotoxy(39, 33); printf("Kota Tujuan  : %s", data.kotaTujuan);
            char hargaStr[30];
            formatHarga((int)data.harga, hargaStr);
            gotoxy(39, 34); printf("Harga        : %s", hargaStr);
            gotoxy(39, 35); printf("Berangkat    : %s", data.jamBerangkat);
            gotoxy(39, 36); printf("Tiba         : %s", data.jamTiba);
            gotoxy(39, 37); printf("Status       : %s", data.statusRute);

            // ========= DATA BARU =========
            bentukframe(85, 29, 55, 14);
            gotoxy(109, 30); printf("DATA BARU");

            gotoxy(90,32); printf("Kota Asal    : ");
            gotoxy(90,33); printf("Kota Tujuan  : ");
            gotoxy(90,34); printf("Harga        : ");
            gotoxy(90,35); printf("Berangkat    : ");
            gotoxy(90,36); printf("Tiba         : ");
            gotoxy(90,37); printf("Status       : ");
            gotoxy(90,38); printf("[ SIMPAN ]");

            int selectedField = 0;
            int totalFields = 6; // 0-5 input, 6 simpan
            int editing = 1;

            while (editing) {

                // Penanda >>
                for (int i = 0; i <= totalFields; i++) {
                    gotoxy(88, 32 + i);
                    printf(i == selectedField ? ">>" : "  ");
                }

                int ch = _getch();

                // ESC → batal
                if (ch == 27) {
                    fclose(fp);
                    fclose(temp);
                    remove("temp.dat");
                    return;
                }

                // Arrow key
                if (ch == 0 || ch == 224) {
                    ch = _getch();
                    if (ch == 72)
                        selectedField = (selectedField - 1 + totalFields + 1) % (totalFields + 1);
                    if (ch == 80)
                        selectedField = (selectedField + 1) % (totalFields + 1);
                }

                // ENTER
                else if (ch == 13) {
                    int inputX = 105;

                    switch (selectedField) {

                    case 0: // Kota Asal
                        clearArea(85, 29, 55, 14);
                        pilihKota(data.kotaAsal, data.kotaTujuan);
                        renderDataBaru(data);
                        gotoxy(105, 32);
                        printf("%s", data.kotaAsal);
                        break;

                    case 1: // Kota Tujuan
                        clearArea(85, 29, 55, 14);
                        pilihKota(data.kotaTujuan, data.kotaAsal);
                        renderDataBaru(data);
                        gotoxy(105, 33);
                        printf("%s", data.kotaTujuan);
                        break;

                        case 2: // Harga
                            clearArea(inputX, 34, 25, 1);

                            // Simpan harga lama dulu
                            int hargaLama = data.harga;

                            int tempHarga = inputHarga(105, 34);

                            if (tempHarga == -1) {  // Jika ESC ditekan
                                data.harga = hargaLama;

                                // Tampilkan kembali harga lama
                                char hargaStr[30];
                                formatHarga((int)hargaLama, hargaStr);
                                gotoxy(105, 34);
                                printf("%s", hargaStr);
                            } else {
                                data.harga = tempHarga;
                            }
                            break;

                        case 3: // Jam Berangkat
                            clearArea(inputX, 35, 15, 1);
                            gotoxy(105, 35);

                            // Simpan jam lama
                            char jamBerangkatLama[10];
                            strcpy(jamBerangkatLama, data.jamBerangkat);

                            if (inputJam(data.jamBerangkat) == -1) {  // Jika ESC
                                // Kembalikan ke jam lama
                                strcpy(data.jamBerangkat, jamBerangkatLama);
                                gotoxy(105, 35);
                                printf("%s", jamBerangkatLama);
                            }
                            break;

                        case 4: // Jam Tiba
                            clearArea(inputX, 36, 15, 1);
                            gotoxy(105, 36);

                            // Simpan jam lama
                            char jamTibaLama[10];
                            strcpy(jamTibaLama, data.jamTiba);

                            if (inputJam(data.jamTiba) == -1) {  // Jika ESC
                                // Kembalikan ke jam lama
                                strcpy(data.jamTiba, jamTibaLama);
                                gotoxy(105, 36);
                                printf("%s", jamTibaLama);
                            }
                            break;

                            case 5: // Status
                            clearArea(85, 29, 55, 14);

                            bentukframe(85, 29, 45, 8);
                            gotoxy(103, 30); printf("PILIH STATUS");

                            gotoxy(95, 32); printf("Aktif");
                            gotoxy(95, 33); printf("Nonaktif");

                            int pilihStatus = rutenavigasi(93, 32, 2, 1);

                            // Pastikan pilihan valid sebelum update
                            if (pilihStatus == 0) {
                                strcpy(data.statusRute, "Aktif");
                            } else if (pilihStatus == 1) {
                                strcpy(data.statusRute, "Nonaktif");
                            }

                            clearArea(85, 29, 55, 14);
                            renderDataBaru(data);

                            gotoxy(105, 37);
                            printf("%s", data.statusRute);
                            break;

                    case 6: // SIMPAN
                        editing = 0;
                        break;
                    }
                }
            }
            // Tulis data yang sudah di-update
            fwrite(&data, sizeof(Rute), 1, temp);
        }
        else {
            // Tulis data lain tanpa perubahan
            fwrite(&tempData, sizeof(Rute), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("rute.dat");
        rename("temp.dat", "rute.dat");
        gotoxy(40, 42); printf("Rute berhasil diperbarui!");
    } else {
        remove("temp.dat");
        gotoxy(3, 27); printf("Nomor rute tidak ditemukan!");
    }

    getch();
    return;
}

#endif

