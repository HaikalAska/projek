#ifndef PROJEK_UPDATEPENUMPANG_H
#define PROJEK_UPDATEPENUMPANG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "../FrameTabel.h"
#include "createpenumpang.h"

void updatePenumpang() {
    FILE *fp, *temp;
    penumpang data;
    char strNo[10];
    int targetNo = 0;
    int currentNo = 1;
    int found = 0;
    int idx = 0;

    int leftX = 50;
    int startY = 29;

    // ================= INPUT NO URUT =================
    gotoxy(3, 25);
    printf("Pilih No Urut: ");

    while (1) {
        char ch = _getch();
        if (ch == 27) return;

        if (ch == 13) {
            strNo[idx] = '\0';
            targetNo = atoi(strNo);
            break;
        }
        else if (ch == 8 && idx > 0) {
            idx--;
            printf("\b \b");
        }
        else if (ch >= '0' && ch <= '9' && idx < 9) {
            strNo[idx++] = ch;
            printf("%c", ch);
        }
    }

    if (targetNo <= 0) return;

    fp   = fopen("penumpang.dat", "rb");
    temp = fopen("temp_penumpang.dat", "wb");
    if (!fp || !temp) return;

    while (fread(&data, sizeof(penumpang), 1, fp)) {

        if (currentNo == targetNo) {
            found = 1;

            // ================= DATA LAMA =================
            bentukframe(48, 29, 45, 10);
            gotoxy(63, 29); printf("DATA LAMA");

            gotoxy(leftX, startY + 2); printf("ID    : %s", data.id);
            gotoxy(leftX, startY + 3); printf("Nama  : %s", data.nama);
            gotoxy(leftX, startY + 4); printf("No HP : %s", data.no_hp);
            gotoxy(leftX, startY + 5); printf("rute  : %s", data.rute);
            gotoxy(leftX, startY + 6); printf("Email : %s", data.email);

            // ================= DATA BARU =================
            bentukframe(95, 29, 55, 10);
            gotoxy(115, 29); printf("DATA BARU");

            gotoxy(100,32); printf("Nama  : ");
            gotoxy(100,33); printf("No HP : ");
            gotoxy(100,34); printf("rute  : ");
            gotoxy(100,35); printf("Email : ");
            gotoxy(100,36); printf("[ SIMPAN ]");

            int selected = 0;
            int total = 4;
            int editing = 1;

            while (editing) {

                // Penanda >>
                for (int i = 0; i <= total; i++) {
                    gotoxy(98, 32 + i);
                    printf(i == selected ? ">>" : "  ");
                }

                int ch = _getch();

                // ESC → batal
                if (ch == 27) {
                    fclose(fp); fclose(temp);
                    remove("temp_penumpang.dat");
                    return;
                }

                // Arrow key
                if (ch == 0 || ch == 224) {
                    ch = _getch();
                    if (ch == 72) selected = (selected - 1 + total + 1) % (total + 1);
                    if (ch == 80) selected = (selected + 1) % (total + 1);
                }

                // ENTER
                else if (ch == 13) {
                    int inputX = 109;

                    switch (selected) {
                        case 0: // Nama
                            clearArea(inputX, 32, 30, 1);
                            gotoxy(inputX, 32);
                            INPUTNama(data.nama);
                            break;

                         case 1: // NO HP
                            clearArea(109, 33, 30, 1);     // col = 109, row = 33
                            gotoxy(109, 33);               // pastikan cursor tepat
                             inputNoTelp(data.no_hp, 33, 109);
                             break;
                        case 2: // Rute
                            clearArea(inputX, 34, 25, 1);
                            inputRute(data.rute, 34, inputX);
                            break;
                        case 3: // Email
                            clearArea(inputX, 35, 30, 1);
                            inputEmail(data.email, 35, inputX);
                            break;

                        case 4: // Simpan
                            editing = 0;
                            break;
                    }
                }
            }

            fwrite(&data, sizeof(penumpang), 1, temp);
        }
        else {
            fwrite(&data, sizeof(penumpang), 1, temp);
        }

        currentNo++;
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("penumpang.dat");
        rename("temp_penumpang.dat", "penumpang.dat");
        gotoxy(leftX, startY + 12);
        printf("Data penumpang berhasil diperbarui!");
    } else {
        remove("temp_penumpang.dat");
        gotoxy(leftX, startY + 12);
        printf("Data tidak ditemukan!");
    }

    _getch();
}

#endif
