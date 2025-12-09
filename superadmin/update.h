#ifndef PROJEK_UPDATE_H
#define PROJEK_UPDATE_H
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "create.h"
#include "read.h"
#include "../FrameTabel.h"

void update() {
    clearscreen();
    system("chcp 65001 > nul");
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);
    gotoxy(8,5); printf("Kelompok 5");
    gotoxy(75,10); printf("======MENU PERUBAHAN======");


    int startY_input = 14;
    int startX_input = 50;
    FILE *fp, *sampah;
    staff data;
    char strNo[10];
    int targetNo = 0;
    int currentNo = 1;
    int found = 0;
    int idx;


    gotoxy(48, startY_input); printf("Pilih No Urut: ");

    idx = 0;
    while (1) {
        char ch = _getch();

        if (ch == 27) {
            return;
        }
        else if (ch == 13) {
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

    if (targetNo <= 0) {
        gotoxy(startX_input, startY_input + 2); printf("Input nomor tidak valid!");
        _getch();
        return;
    }

    fp = fopen("staff.dat", "rb");
    sampah = fopen("sampah.dat", "wb");

    if (!fp || !sampah) {
        gotoxy(startX_input, startY_input + 2); printf("Gagal membuka file database!");
        _getch();
        return;
    }


    while (fread(&data, sizeof(staff), 1, fp) == 1) {

        if (currentNo == targetNo) {
            found = 1;

            gotoxy(33,11); printf("[ESC] Keluar");
            gotoxy(33,10); printf("[ENTER] Memilih");
            gotoxy(100, 14);printf("NAVIGASI \xE2\x86\x91 \xE2\x86\x93");


            printBorder(48, 15, 35, 10);
            gotoxy(startX_input, startY_input + 2); printf("=== Data Lama ===");
            gotoxy(startX_input, startY_input + 3); printf("Nama      : %s", data.username);

            char maskedPw[50];
            int pwLen = strlen(data.password);
            for(int i = 0; i < pwLen; i++) maskedPw[i] = '*';
            maskedPw[pwLen] = '\0';
            gotoxy(startX_input, startY_input + 4); printf("Password  : %s", maskedPw);

            gotoxy(startX_input, startY_input + 5); printf("Tgl Lahir : %s", data.tgl);
            gotoxy(startX_input, startY_input + 6); printf("No Telpon : %s", data.notlpn);
            gotoxy(startX_input, startY_input + 7); printf("Gender    : %s", data.gender);


            printBorder(98, 15, 35, 10);
            gotoxy(100, 16); printf("=== MASUKKAN DATA BARU ===");


            gotoxy(103,17); printf("Nama      : ");
            gotoxy(103, 18); printf("Password  : ");
            gotoxy(103, 19); printf("Tgl Lahir : ");
            gotoxy(103, 20); printf("No Telpon : ");
            gotoxy(103, 21); printf("Gender    : ");
            gotoxy(103, 22); printf("[Selesai]");

            int selectedField = 0;
            int editing = 1;

            while (editing) {

                for (int i = 0; i < 6; i++) {
                    gotoxy(100, 17 + i);
                    if (i == selectedField) {
                        printf(">>");
                    } else {
                        printf("  ");
                    }
                }

                int ch = _getch();


                if (ch == 0 || ch == 224) {
                    int arrow = _getch();

                    if (arrow == 72) {
                        selectedField--;
                        if (selectedField < 0) selectedField = 5;
                    }
                    else if (arrow == 80) {
                        selectedField++;
                        if (selectedField > 5) selectedField = 0;
                    }
                }

                else if (ch == 13) {
                    if (selectedField == 5) {
                        editing = 0;
                        break;
                    }


                    int inputX = 114;
                    int inputY = 17 + selectedField;

                    // Clear area input
                    gotoxy(inputX, inputY);
                    printf("                  ");
                    gotoxy(inputX, inputY);

                    idx = 0;


                    if (selectedField == 0) {
                        while (1) {
                            char c = _getch();
                            if (c == 13) { data.username[idx] = '\0'; break; }
                            else if (c == 27) break;
                            else if (c == 8 && idx > 0) { idx--; printf("\b \b"); }
                            else if (c >= 32 && c <= 126 && idx < 49) { data.username[idx++] = c; printf("%c", c); }
                        }
                    }
                    else if (selectedField == 1) {
                        while (1) {
                            char c = _getch();
                            if (c == 13) { data.password[idx] = '\0'; break; }
                            else if (c == 27) break;
                            else if (c == 8 && idx > 0) { idx--; printf("\b \b"); }
                            else if (c >= 32 && c <= 126 && idx < 49) { data.password[idx++] = c; printf("*"); }
                        }
                    }
                    else if (selectedField == 2) {
                        while (1) {
                            char c = _getch();
                            if (c == 13) { data.tgl[idx] = '\0'; break; }
                            else if (c == 27) break;
                            else if (c == 8 && idx > 0) { idx--; printf("\b \b"); }
                            else if (((c >= '0' && c <= '9') || c == '-') && idx < 49) { data.tgl[idx++] = c; printf("%c", c); }
                        }
                    }
                    else if (selectedField == 3) {
                        while (1) {
                            char c = _getch();
                            if (c == 13) { data.notlpn[idx] = '\0'; break; }
                            else if (c == 27) break;
                            else if (c == 8 && idx > 0) { idx--; printf("\b \b"); }
                            else if (c >= '0' && c <= '9' && idx < 49) { data.notlpn[idx++] = c; printf("%c", c); }
                        }
                    }
                    else if (selectedField == 4) {
                        while (1) {
                            char c = _getch();
                            if (c == 13) { data.gender[idx] = '\0'; break; }
                            else if (c == 27) break;
                            else if (c == 8 && idx > 0) { idx--; printf("\b \b"); }
                            else if (c >= 32 && c <= 126 && idx < 49) { data.gender[idx++] = c; printf("%c", c); }
                        }
                    }
                }

                else if (ch == 'w' || ch == 'W') {
                    selectedField--;
                    if (selectedField < 0) selectedField = 5;
                }
                else if (ch == 's' || ch == 'S') {
                    selectedField++;
                    if (selectedField > 5) selectedField = 0;
                }

                else if (ch == 27) {
                    fclose(fp);
                    fclose(sampah);
                    remove("sampah.dat");
                    return;
                }
            }


            fwrite(&data, sizeof(staff), 1, sampah);

        } else {

            fwrite(&data, sizeof(staff), 1, sampah);
        }

        currentNo++;
    }

    fclose(fp);
    fclose(sampah);


    if (found) {
        remove("staff.dat");
        rename("sampah.dat", "staff.dat");
        gotoxy(startX_input, startY_input + 18); printf("Data Berhasil Di Update!");
    }
    else {
        remove("sampah.dat");
        gotoxy(startX_input, startY_input + 18); printf("Nomor urut %d tidak ditemukan!", targetNo);
    }

    _getch();
}

#endif //PROJEK_UPDATE_H