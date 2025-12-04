#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include "FrameTabel.h"
#include "Menu.h"


//==================================//
static void setPointer(int row, int col);
static void inputPassword(char *pw);
//=================================//



void validLogin() {
    char id[50];
    char pw[50];
    char role[50] = "";

    char AdminID[] = "SuperAdmin";
    char AdminPW[] = "SuperAdmin";

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



        gotoxy(73, 26);printf("Login");
        gotoxy(45, 27);printf("=============================================================");
        gotoxy(45, 28);printf("||                                                         ||");
        gotoxy(45,29); printf("||          ID :                                           ||");
        gotoxy(45,30); printf("||    Password :                                           ||");
        gotoxy(45,31); printf("||                                                         ||");
        gotoxy(45,32); printf("=============================================================");
        gotoxy(45,33); printf("[Tab] Untuk Melihat Password");



        setPointer(30, 62);
        scanf("%s", id);

        setPointer(31, 62);
        inputPassword(pw);


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
            printf("\n\n\n\n                    ID atau Password salah!\n");
            printf("                    Sisa percobaan: %d\n", Maxpercobaan - percobaan);

            if (percobaan < Maxpercobaan) {
                printf("                    Tekan Enter untuk coba lagi...");
                while ((trash = getchar()) != '\n');
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


//=============================================//
//==============Bagian Password===============//
static void inputPassword(char *pw) {
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
        else if (ch == 9) {
            showPw = !showPw;

            printf("\r");

            gotoxy(45, 30);
            printf("||    Password :");
            for (int j = 0; j < i; j++) {
                if (showPw)
                    printf("%c", pw[j]);
                else
                    printf("*");
            }
        }
        else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
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
//=============================================//

#endif
