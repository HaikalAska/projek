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
            gotoxy(39, 32); printf("Harga        : %.2f", data.harga);
            gotoxy(39, 33); printf("Berangkat    : %s", data.jamBerangkat);
            gotoxy(39, 34); printf("Tiba         : %s", data.jamTiba);

            // ========= DATA BARU =========
            bentukframe(85, 27, 55, 12);
            gotoxy(109, 28); printf("DATA BARU");

            gotoxy(87,30); printf("Kota Asal    : ");
            gotoxy(87,31); printf("Kota Tujuan  : ");
            gotoxy(87,32); printf("Harga        : ");
            gotoxy(87,33); printf("Berangkat    : ");
            gotoxy(87,34); printf("Tiba         : ");
            gotoxy(87,35); printf("[ SIMPAN PERUBAHAN ]");

            int selectedField = 0;
            int totalFields = 5; // 0-4 input, 5 simpan
            int editing = 1;

            while (editing) {
                // Cursor Navigasi
                for (int i = 0; i <= totalFields; i++) {
                    gotoxy(85, 30 + i);
                    printf(i == selectedField ? ">>" : "│ ");
                }

                int ch = _getch();

                if (ch == 0 || ch == 224) {
                    int arrow = _getch();
                    if (arrow == 72) {
                        selectedField--;
                        if (selectedField < 0) selectedField = totalFields;
                    }
                    else if (arrow == 80) {
                        selectedField++;
                        if (selectedField > totalFields) selectedField = 0;
                    }
                }
                else if (ch == 13) {
                    if (selectedField == totalFields) {
                        editing = 0;
                        break;
                    }

                    int inputX = 105;
                    clearArea(inputX, 30 + selectedField, 25, 1);

                    switch (selectedField) {
                        case 0:
                            gotoxy(102,30);
                            scanf("%s", data.kotaAsal);
                            break;

                        case 1:
                            gotoxy(102,31);
                            scanf("%s", data.kotaTujuan);
                            break;

                        case 2:
                            data.harga = inputHarga(102,32);
                            if (data.harga == 0) goto batal;
                            break;

                        case 3:
                            gotoxy(102,33); inputJam(data.jamBerangkat);
                            if (!strlen(data.jamBerangkat)) goto batal;
                            break;

                        case 4:
                            gotoxy(102,34); inputJam(data.jamTiba);
                            if (!strlen(data.jamTiba)) goto batal;
                            break;
                    }
                }
                else if (ch == 27) goto batal;
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

