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
    while (fread(&s, sizeof(staff), 1, file)) {
        if (strcmp(s.username, username) == 0 && strcmp(s.password, pw) == 0) {
            strcpy(role, "Staff");
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void validLogin() {
    char username[50];
    char pw[50];
    char role[50] = "";

    // Hardcoded super admin
    char AdminID[] = "123";
    char AdminPW[] = "123";

    char ManagerID[] = "Manager";
    char ManagerPW[] = "Manager";

    int percobaan = 0;
    int Maxpercobaan = 3;

    while (percobaan < Maxpercobaan) {

        fillBackground(0x90);
        clearscreen();
        gotoxy(70, 10);
        printf("SELAMAT DATANG");

        tampilanlogin("GAMBARASCI.txt", 42, 15);

        gotoxy(73, 26);printf("Masuk");
        gotoxy(45, 27);printf("=============================================================");
        gotoxy(45, 28);printf("||                                                         ||");
        gotoxy(45,29); printf("||  Username   :                                           ||");
        gotoxy(45,30); printf("||  Kata Sandi :                                           ||");
        gotoxy(45,31); printf("||                                                         ||");
        gotoxy(45,32); printf("=============================================================");
        gotoxy(45,33); printf("[Tab] Untuk Melihat Password");
        gotoxy(86,33); printf("[ESC] Keluar Program");

        setPointer(30, 62);
        inputID(username);

        setPointer(31, 62);
        inputPassword(pw, 61, 30);


        if (cekLoginDariFile(username, pw, role)) {
            break;
        }
        // Backup: cek super admin hardcoded
        else if (strcmp(username, AdminID) == 0 && strcmp(pw, AdminPW) == 0) {
            strcpy(role, "Admin");
            break;
        }else if (strcmp(username, ManagerID) == 0 && strcmp(pw, ManagerPW) == 0) {
            strcpy(role, "Manager");
            break;
        }
        else {
            percobaan++;
            printf("\n\n\n\n\t\t\t\t\t                     Username atau Password salah!\n");
            printf("\t\t\t\t\t\t                   Sisa percobaan: %d\n", Maxpercobaan - percobaan);

            if (percobaan < Maxpercobaan) {
                printf("\t\t\t\t\t                     Tekan Enter untuk coba lagi...");
                getchar();
            }
            continue;
        }
    }

    if (percobaan == Maxpercobaan) {
        clearscreen();
        printf("Batas percobaan habis, program keluar...\n");
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

//INPUT ID KHUSUS LOGIN//
static void inputID(char *id) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();

        if (ch == 13) {                 // ENTER
            id[i] = '\0';
            break;
        }
        else if (ch == 27) {            // ESC
            exit(0);
        }
        else if (ch == 8) {             // BACKSPACE
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if (ch == 32) {
            continue;
        }
        else {                          // INPUT NORMAL
            id[i++] = ch;
            printf("%c", ch);
        }
    }
}

//=============================================//
//==============Bagian Password KHUSUS LOGIN===============//
static void inputPassword(char *pw, int row, int col) {
    int i = 0;
    char ch;
    int showPw = 0;

    while (1) {
        ch = getch();

        //ENTER
        if (ch == 13) {
            pw[i] = '\0';
            printf("\n");
            break;
        }

        //ESC
        else if (ch == 27) {
            exit(0);
        }

        //BACKSPACE
        else if (ch == 9) {             // TAB = toggle show/hide
            showPw = !showPw;

            // refresh tampilan
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