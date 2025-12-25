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

void updaterute() {
    FILE *fp, *temp;
    Rute data;
    int targetNo = 0, currentNo = 1, found = 0;
    char strNo[10];
    int idx = 0;

    // ================= INPUT NOMOR URUT =================
    gotoxy(3, 25);
    printf("Pilih No Urut Rute: ");

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
        if (ch >= '0' && ch <= '9' && idx < 9) {
            strNo[idx++] = ch;
            printf("%c", ch);
        }
    }

    fp   = fopen("rute.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (!fp || !temp) return;

    // ================= PROSES UPDATE =================
    while (fread(&data, sizeof(Rute), 1, fp)) {

        if (currentNo == targetNo) {
            found = 1;

            // ========= DATA LAMA =========
            bentukframe(37, 27, 45, 12);
            gotoxy(55, 28); printf("DATA LAMA");

            gotoxy(39, 30); printf("Kota Asal    : %s", data.kotaAsal);
            gotoxy(39, 31); printf("Kota Tujuan  : %s", data.kotaTujuan);
            char hargaStr[30];
            formatHarga((int)data.harga, hargaStr);
            gotoxy(39, 32); printf("Harga        : %s", hargaStr);
            gotoxy(39, 33); printf("Berangkat    : %s", data.jamBerangkat);
            gotoxy(39, 34); printf("Tiba         : %s", data.jamTiba);

            // ========= DATA BARU =========
            bentukframe(85, 27, 55, 12);
            gotoxy(109, 28); printf("DATA BARU");

            gotoxy(90,30); printf("Kota Asal    : ");
            gotoxy(90,31); printf("Kota Tujuan  : ");
            gotoxy(90,32); printf("Harga        : ");
            gotoxy(90,33); printf("Berangkat    : ");
            gotoxy(90,34); printf("Tiba         : ");
            gotoxy(90,35); printf("[ SIMPAN ]");

            int selectedField = 0;
            int totalFields = 5; // 0-4 input, 5 simpan
            int editing = 1;

            while (editing) {

                // Penanda >>
                for (int i = 0; i <= totalFields; i++) {
                    gotoxy(88, 30 + i);
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
                        clearArea(inputX, 30, 25, 1);
                        gotoxy(105, 30);
                        scanf("%s", data.kotaAsal);
                        break;

                    case 1: // Kota Tujuan
                        clearArea(inputX, 31, 25, 1);
                        gotoxy(105, 31);
                        scanf("%s", data.kotaTujuan);
                        break;

                    case 2: // Harga
                        clearArea(inputX, 32, 25, 1);
                        data.harga = inputHarga(105, 32);
                        break;

                    case 3: // Jam Berangkat
                        clearArea(inputX, 33, 15, 1);
                        gotoxy(105, 33);
                        inputJam(data.jamBerangkat);
                        break;

                    case 4: // Jam Tiba
                        clearArea(inputX, 34, 15, 1);
                        gotoxy(105, 34);
                        inputJam(data.jamTiba);
                        break;

                    case 5: // SIMPAN
                        editing = 0;
                        break;
                    }
                }
            }


            fwrite(&data, sizeof(Rute), 1, temp);
        }
        else {
            fwrite(&data, sizeof(Rute), 1, temp);
        }

        currentNo++;
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("rute.dat");
        rename("temp.dat", "rute.dat");
        gotoxy(40, 42); printf("Rute berhasil diperbarui!");
    } else {
        remove("temp.dat");
        gotoxy(40, 42); printf("Nomor rute tidak ditemukan!");
    }

    getch();
    return;

batal:
    fclose(fp);
    fclose(temp);
    remove("temp.dat");
}

#endif

