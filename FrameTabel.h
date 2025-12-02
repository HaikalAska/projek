#ifndef PROJEK_FRAMETABEL_H
#define PROJEK_FRAMETABEL_H
#include <fcntl.h>

//==================================================================//
//=====================buat nampilin ASCI nya======================//
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
//===================================================================//




//==============================================//
//=============BUAT CLEARSCREEN===============//
static void clearscreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
//============================================//


//======================================================================//
//==============BIAR TIAP PRINT GA HARUS (\N DAN \t)  =================//
void gotoxy(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//===================================================================//






//***********************************************************************//
//***************** INI BAGIAN FRAME HITAM NYA DOANG*********************//
//**********************************************************************//


//==================================================================//
//===========================BUAT FRAME============================//
void MoveCursor(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//==================================================================//






//==================================================================//
//================BIAR GA HARUS UTF8 (BORDER)=========================//
void printBlock(wchar_t wc) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    WriteConsoleW(h, &wc, 1, &written, NULL);
}
//===========================================================================//






//===================================================================//
//============================BENTUK FRAME============================//
void BentukFrame(int x, int y, int width, int height) {
    gotoxy(x, y);
    printf("╔");
    for (int i = 0; i < width - 2; i++)
        printf("═");
    printf("╗");

    for (int i = 1; i < height - 1; i++) {
        gotoxy(x, y + i);
        printf("║");
        for (int j = 0; j < width - 2; j++)
            printf(" ");
        printf("║");
    }

    gotoxy(x, y + height - 1);
    printf("╚");
    for (int i = 0; i < width - 2; i++)
        printf("═");
    printf("╝");
}
//===================================================================//






//====================================================================//
//=======================PRINT BORDER================================//
void printBorder(int posX, int posY, int width, int height) {
    SetConsoleOutputCP(65001);
    gotoxy(posX, posY);
    for (int i = 0; i < width; i++)
        printf("█");
    for (int y = 1; y < height - 1; y++) {
        gotoxy(posX, posY + y);
        printf("█");
        for (int x = 0; x < width - 2; x++)
            printf(" ");
        printf("█");
    }

    gotoxy(posX, posY + height - 1);
    for (int i = 0; i < width; i++)
        printf("█");
}
//===========================================================//





//=======================================================//
//======================FRAME TENGAH=====================//
void FrameYangTengah(int x, int y, int height) {
    for (int i = 0; i < height; i++) {
        MoveCursor(x, y + i);
        printBlock(L'█');
    }
}
//======================================================//




//======================================================//
//=====================FRAME HIDER=====================//
void FrameYangHider(int x, int y, int width) {
    MoveCursor(x, y);
    for (int i = 0; i < width; i++) {
        printBlock(L'█');
    }
}
//====================================================//

#endif