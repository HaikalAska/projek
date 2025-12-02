#ifndef PROJEK_MENU_H
#define PROJEK_MENU_H
#include "login.h"

void BorderMenu(char filename[50]);
void printFileAtPosition(char *filename, int startX, int startY);

static void tampilanMenu() {
    char filename [50];

    strcpy (filename, "MenuTabel.txt");

    fillBackground(0x70);
    clearscreen();

    BorderMenu(filename);
    printFileAtPosition("GAMBARASCI.txt", 50, 1);

    gotoxy(8,3);
    printf("Kelompok 5");

    getchar();
    getchar();
};



void BorderMenu(char filename[50]){
    FILE *Asci = fopen(filename, "r");
    char line[200];
    while (fgets(line, sizeof(line), Asci)) {
        printf("%s", line);
    }
    fclose(Asci);
}

void printFileAtPosition(char *filename, int startX, int startY) {
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
#endif
