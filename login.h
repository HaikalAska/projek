#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include "FrameTabel.h"
#include "Menu.h"

typedef struct {
    char username[50];
    char password[50];
    char id[100];
    char tgl[100];
    char gender[100];
    char notlpn[20];
} stafff;

void menuSuperAdmin();
void menuStaff();
void menuManager();

static void setPointer(int row, int col);
static void inputPassword(char *pw, int row, int col);
static void inputID(char *id);
static int cekLoginDariFile(char *username, char *pw, char *role);


static int cekLoginDariFile(char *username, char *pw, char *role) {
    FILE *file = fopen("staff.dat", "rb");
    staff s;

    if (file == NULL)
        return 0;

    while (fread(&s, sizeof(staff), 1, file)) {
        if (strcmp(s.username, username) == 0 &&
            strcmp(s.password, pw) == 0) {

            if (strcmp(s.status, "Aktif") == 0) {
                if (strcmp(s.Role, "Manager") == 0) {
                    strcpy(role, "Manager");
                } else {
                    strcpy(role, "Staff");
                }
                fclose(file);
                return 1;
            } else {
                fclose(file);
                return -1;
            }
        }
    }

    fclose(file);
    return 0;
}


void validLogin() {
    char username[50];
    char pw[50];
    char role[50] = "";

    char AdminID[] = "1";
    char AdminPW[] = "12";

    int percobaan = 0;
    int Maxpercobaan = 3;

    while (percobaan < Maxpercobaan) {

        fillBackground(0x90);
        clearscreen();
        bentukframe(69, 9, 16, 3);
        gotoxy(70, 10); printf("SELAMAT DATANG");


        bentukframe(41, 14, 67, 20);
        tampilanlogin("WELCOME.txt", 42, 17);
        gotoxy(73, 26);printf("Masuk");
        bentukframe(45, 27, 60, 6);
        gotoxy(47,29); printf("  Username   : ");
        gotoxy(47,30); printf("  Kata Sandi : ");
        gotoxy(45,33); printf("[Tab] Untuk Melihat Password");
        gotoxy(86,33); printf("[ESC] Keluar Program");

        setPointer(30, 62);
        inputID(username);

        setPointer(31, 62);
        inputPassword(pw, 61, 30);


        int hasil = cekLoginDariFile(username, pw, role);

        if (hasil == 1) {
            break;
        }
        else if (hasil == -1) {
            percobaan++;
            gotoxy(55,36);printf("Akun Anda tidak aktif! Hubungi Admin.");
            gotoxy(65,37);printf("Sisa percobaan: %d", Maxpercobaan - percobaan);
            if (percobaan < Maxpercobaan) {
                gotoxy(60,38);printf("Tekan Enter untuk coba lagi...");
                getchar();
            }
            continue;
        }
        else if (strcmp(username, AdminID) == 0 && strcmp(pw, AdminPW) == 0) {
            strcpy(role, "Admin");
            break;
        }
        else {
            percobaan++;
            gotoxy(60,36);printf("Username atau Password salah!");
            gotoxy(65,37);printf("Sisa percobaan: %d", Maxpercobaan - percobaan);
            if (percobaan < Maxpercobaan) {
                gotoxy(60,38);printf("Tekan Enter untuk coba lagi...");
                getchar();
            }
            continue;
        }
    }

    if (percobaan == Maxpercobaan) {
        bentukframe(47, 20, 55, 12);
        gotoxy(64,22);printf("Batas percobaan habis\n");
        gotoxy(64,28); printf("Silakan lapor ke Admin\n");
        getchar();
        getchar();
        exit(0);
    }

    gotoxy(65, 35); printf("[OK] Login berhasil!");
    gotoxy(60, 36); printf("Tekan Enter untuk melanjutkan...");
    getchar();


    if (strcmp(role, "Admin") == 0) {
        menuSuperAdmin();
        return;
    }
    else if (strcmp(role, "Staff") == 0) {
        menuStaff();
        return;
    }
    else if (strcmp(role, "Manager") == 0) {
        menuManager();
        return;
    }
}

static void inputID(char *id) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();

        if (ch == 13) {
            id[i] = '\0';
            break;
        }
        else if (ch == 27) {
            exit(0);
        }
        else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if (ch == 32) {
            continue;
        }
        else {
            id[i++] = ch;
            printf("%c", ch);
        }
    }
}

static void inputPassword(char *pw, int row, int col) {
    int i = 0;
    char ch;
    int showPw = 0;

    while (1) {
        ch = getch();

        if (ch == 13) {
            pw[i] = '\0';
            printf("\n");
            break;
        }

        else if (ch == 27) {
            exit(0);
        }

        else if (ch == 9) {
            showPw = !showPw;

            gotoxy(row, col);
            for (int j = 0; j < i; j++) {
                printf(showPw ? "%c" : "*", pw[j]);
            }
        }
        else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if (ch == 32) {
            continue;
        }
        else {
            pw[i++] = ch;

            if (showPw)
                printf("%c", ch);
            else
                printf("*");
        }
    }
}

#endif