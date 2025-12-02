#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>


//==================================//
static void fullscreen();
static void clearscreen();
static void setPointer(int row, int col);
static void tampilanlogin(char *filename, int startX, int startY);
static void inputPassword(char *pw);
void gotoxy(int x, int y);
void fillBackground(int colorPair);
//=================================//



static void validLogin() {
    char filename[100] = "GAMBARASCI.txt";
    char id[50];
    char pw[50];
    char validID[] = "1";
    char validPW[] = "1";
    int percobaan = 0;
    int Maxpercobaan = 3;
    int trash;

    while (percobaan < Maxpercobaan) {

        fillBackground(0x70);
        clearscreen();
        gotoxy(70, 10);
        printf("SELAMAT DATANG");

        tampilanlogin("GAMBARASCI.txt", 42, 15);


        gotoxy(73, 26);
        printf("Login");
        gotoxy(45, 27);
        printf("=============================================================");
        gotoxy(45, 28);
        printf("||                                                         ||");
        gotoxy(45,29);
        printf("||    ID       :                                           ||");
        gotoxy(45,30);
        printf("||    Password :                                           ||");
        gotoxy(45,31);
        printf("||                                                         ||");
        gotoxy(45,32);
        printf("=============================================================");
        gotoxy(45,33);
        printf("[Tab] Untuk Melihat Password");

        setPointer(30, 62);
        scanf("%s", id);

        setPointer(31, 62);
        inputPassword(pw);

        if (strcmp(id, validID) == 0 && strcmp(pw, validPW) == 0) {
            printf("\n\n\n\n                     [OK] Login berhasil!\n");
            printf("                     Tekan Enter untuk melanjutkan...");

            while ((trash = getchar()) != '\n');
            clearscreen();

            return;
        } else {
            percobaan++;

            printf("\n\n\n\n                     ID atau Password salah!\n");
            printf("\t\t     Sisa percobaan: %d\n", Maxpercobaan - percobaan);

            if (percobaan < Maxpercobaan) {
                printf("                     Tekan Enter untuk coba lagi...");
                while ((trash = getchar()) != '\n');
                getchar();
            }
        }
    }

    clearscreen();
    printf("\n\n\n\n\n\n\n");
    printf("\t\t\t\t\t   Batas percobaan habis, program keluar...\n");
    getchar();
}



//Untuk Clearscreen
static void clearscreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


//setting pointer nya
static void setPointer(int row, int col){
    printf("\033[%d;%dH", row, col);
}


//buat nampilin ASCI nya
static void tampilanlogin(char *filename, int startX, int startY) {
    FILE *f = fopen(filename, "r");
    if (!f) return;

    char line[300];
    int currentRow = 0;

    while (fgets(line, sizeof(line), f)) {
        gotoxy(startX, startY + currentRow);
        printf("%s", line);
        currentRow++;
    }

    fclose(f);
}

//biar tiap print teks ga harus n sama t
void gotoxy(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



//biar ga ada blank hitam di cmd saat di run
void fillBackground(int colorPair) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(h, &csbi);

    int width  = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    SetConsoleTextAttribute(h, colorPair);

    COORD pos = {0, 0};
    SetConsoleCursorPosition(h, pos);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf(" ");
        }
    }
    (h, pos);
}



//Bagian Password
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


#endif
