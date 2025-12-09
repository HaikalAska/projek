#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include "FrameTabel.h"
#include "Menu.h"


void menuSuperAdmin();
void menuStaff();
void menuManager();


//==================================//
static void setPointer(int row, int col);
static void inputPassword(char *pw,int row,int col);
static void inputID(char *id);
//=================================//





void validLogin() {
    system("chcp 65001 > nul");
    char id[50];
    char pw[50];
    char role[50] = "";

    char AdminID[] = "123";
    char AdminPW[] = "123";

    char staffID[] = "staff";
    char staffPW[] = "staff";

    char managerID[] = "manager";
    char managerPW[] = "manager";

    int percobaan = 0;
    int Maxpercobaan = 3;
    int trash;

    while (percobaan < Maxpercobaan) {

        fillBackground(0x90);
        clearscreen();
        gotoxy(70, 10);
        printf("SELAMAT DATANG");

        tampilanlogin("GAMBARASCI.txt", 42, 15);



        gotoxy(73, 26);printf("Masuk");
        gotoxy(45, 26);printf("\xE2\x86\x91 \xE2\x86\x93 \xE2\x86\x92 \xE2\x86\x90");
        gotoxy(45, 27);printf("=============================================================");
        gotoxy(45, 28);printf("||                                                         ||");
        gotoxy(45,29); printf("||  Id Pengguna:                                           ||");
        gotoxy(45,30); printf("||  Kata Sandi :                                           ||");
        gotoxy(45,31); printf("||                                                         ||");
        gotoxy(45,32); printf("=============================================================");
        gotoxy(45,33); printf("[Tab] Untuk Melihat Password");
        gotoxy(86,33); printf("[ESC] Keluar Program");




        setPointer(30, 62);
        inputID(id);

        setPointer(31, 62);
        inputPassword(pw, 61, 30);


        if (strcmp(id, AdminID) == 0 && strcmp(pw, AdminPW) == 0) {
            strcpy(role, "Admin");
        }
        else if (strcmp(id, staffID) == 0 && strcmp(pw, staffPW) == 0) {
            strcpy(role, "Staff");
        }
        else if (strcmp(id, managerID) == 0 && strcmp(pw, managerPW) == 0) {
            strcpy(role, "Manager");
        }
        else {
            percobaan++;
            printf("\n\n\n\n\t\t\t\t\t                        ID atau Password salah!\n");
            printf("\t\t\t\t\t\t                   Sisa percobaan: %d\n", Maxpercobaan - percobaan);

            if (percobaan < Maxpercobaan) {
                printf("\t\t\t\t\t                     Tekan Enter untuk coba lagi...");
                //while ((trash = getchar()) != '\n');
                getchar();
            }
            continue;
        }
        break;
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

//=========================================//
//==========setting pointer nya============//
static void setPointer(int row, int col){
    printf("\033[%d;%dH", row, col);
}
//=======================================//




//===================================================//
//======================ID==========================//
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

//==================================================//

#endif
