#ifndef PROJEK_UPDATE_H
#define PROJEK_UPDATE_H
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "create.h"

void update() {
    gotoxy(3,8); printf("[Esc] Keluar");

    FILE *fp, *sampah;
    staff data;
    char target [50];
    int found = 0;
    int idx;

    fp = fopen("staff.dat", "rb");
    sampah = fopen("sampah.dat", "wb");

    gotoxy(3,13); printf("username update :");
    idx = 0;
    while (1) {
        char ch = _getch();

        if (ch == 27) {
            fclose(fp);
            fclose(sampah);
            remove("sampah.dat");
            return;
        }
        else if (ch == 13) {
            target [idx] = '\0';
            break;
        }
        else if (ch == 8 && idx > 0) {
            idx--;
            printf("\b \b");
        }
        else if (ch >= 32 && ch <= 126 && idx < 49 ) {
            target [idx++] = ch;
            printf("%c", ch);
        }
    }

    while (fread(&data, sizeof(staff), 1, fp) == 1) {
        if (strcmp(data.username, target) == 0) {
            found = 1;
            gotoxy(3, 15); printf("Username lama: %s", data.username);

            gotoxy(3, 18); printf("Username Baru :");
            idx = 0;
            while (1) {
                char ch = _getch();
                if (ch == 27) {
                    fclose(fp);
                    remove("sampah.dat");
                    return;
                }
                else if (ch == 13) {
                    data.username[idx] = '\0';
                    break;
                }
                else if (ch == 8 && idx > 0) {
                    idx--;
                    printf("\b \b");
                }
                else if (ch >= 32 && ch <= 126 && idx < 49) {
                    data.username[idx++] = ch;
                    printf("%c", ch);
                }
            }

            gotoxy(3,19); printf("Password Baru: ");
            idx = 0;
            while (1) {
                char ch = _getch();

                if (ch ==27) {
                    fclose(fp);
                    fclose(sampah);
                    remove("sampah.dat");
                    return;
                }
                else if (ch == 13) {
                    data.password[idx] = '\0';
                    break;
                }
                else if (ch == 8 && idx > 0) {
                    idx--;
                    printf("\b \b");
                }
                else if (ch >= 32 && ch <= 126 && idx < 49) {
                    data.password[idx++] = ch;
                    printf("%c", ch);
                }
            }
            fwrite(&data, sizeof(staff), 1, sampah);
        }
    }
    fclose(fp);
    fclose(sampah);
    if (found) {
        remove("staff.dat");
        rename ("sampah.dat", "satff.dat");
        gotoxy(3,15); printf("Data Berhasil Di Update");
    }
    else {
        remove("sampah.dat");
        gotoxy(3,15); printf("Data tidak ditemukan!");
    }
    _getch();
}

#endif //PROJEK_UPDATE_H