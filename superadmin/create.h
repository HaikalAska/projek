//
// Created by Lenovo on 05/12/2025.
//

#ifndef PROJEK_CREATE_H
#define PROJEK_CREATE_H
#include "../FrameTabel.h"

int getStaffCount();
static void inputID(char *id);
int inputWithEsc(char *buffer, int maxLen);
int inputTglWithEsc(char *buffer, int maxLen);
int inputTelpWithEsc(char *buffer, int maxLen);
int pwESC(char *pw, int col, int row);


typedef struct {
    char username[50];
    char password[50];
    char id[100];
    char tgl[100];
    char gender[100];
    char notlpn[20];
}staff;

void create() {
    char n;

    do {
        clearLine(14, 3, 30);
        clearLine(15, 3, 30);
        clearLine(16, 3, 30);
        clearLine(17, 3, 30);
        clearLine(18, 3, 30);
        clearLine(19, 3, 30);
        clearLine(22, 3, 30);
        clearLine(20, 3, 30);
        gotoxy(3,8);
        printf("[Esc] Keluar");

        FILE *fp = fopen("staff.dat", "ab");
        if (!fp) return;

        staff data;

        int count = getStaffCount() + 1;
        sprintf(data.id, "STF%03d", count);
        clearArea(3, 14, 20);
        gotoxy(3,14); printf("ID Otomatis  : %s", data.id);

        // Input Nama dengan deteksi ESC
        gotoxy(3,15); printf("Nama         : ");
        if (!inputWithEsc(data.username, 50)) {
            fclose(fp);
            return; // Keluar jika ESC
        }

        // Input Password dengan deteksi ESC
        gotoxy(3,16); printf("Kata Sandi   : ");
        if (!pwESC(data.password, 17, 16)) {
            fclose(fp);
            return;
        }

        // Input Tanggal Lahir dengan deteksi ESC
        gotoxy(3,17); printf("Tgl Lahir    : ");
        if (!inputTglWithEsc(data.tgl, 100)) {  // FIXED: Ganti dari inputTglWithEsc menjadi !inputTglWithEsc
            fclose(fp);
            return;
        }

        // Input Kelamin dengan deteksi ESC
        gotoxy(3,18); printf("Kelamin      : ");
        if (!inputWithEsc(data.gender, 100)) {
            fclose(fp);
            return;
        }

        // Input No Telepon dengan deteksi ESC
        gotoxy(3,19); printf("No Telpon    : ");
        if (!inputTelpWithEsc(data.notlpn, 20)) {
            fclose(fp);
            return;
        }

        fwrite(&data, sizeof(staff), 1, fp);
        fclose(fp);

        gotoxy(3,20);
        printf("Data berhasil dibuat!");
        gotoxy(3,22);
        printf("Tambah lagi? (y/n): ");

        // Input y/n dengan deteksi ESC
        while (1) {
            n = _getch();
            if (n == 27) return; // ESC keluar
            if (n == 'y' || n == 'Y' || n == 'n' || n == 'N') {
                printf("%c", n);
                break;
            }
        }

    } while (n == 'y' || n == 'Y');
}

int getStaffCount() {
    FILE *fp = fopen("staff.dat", "rb");
    if (!fp) return 0;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);

    return size / sizeof(staff);
}

int inputWithEsc(char *buffer, int maxLen) {
    int idx = 0;
    while (1) {
        char ch = _getch();

        if (ch == 27) { // ESC
            return 0; // Return 0 = user cancel
        }
        else if (ch == 13) { // ENTER
            buffer[idx] = '\0';
            return 1; // Return 1 = success
        }
        else if (ch == 8 && idx > 0) { // BACKSPACE
            idx--;
            printf("\b \b");
        }
        else if (ch >= 32 && ch <= 126 && idx < maxLen - 1) {
            buffer[idx++] = ch;
            printf("%c", ch);
        }
    }
}

int inputTglWithEsc(char *buffer, int maxLen) {
    int idx = 0;
    while (1) {
        char ch = _getch();

        if (ch == 27) { // ESC
            return 0;  // Return 0 = user cancel
        }
        else if (ch == 13) { // ENTER
            buffer[idx] = '\0';
            return 1;  // Return 1 = success
        }
        else if (ch == 8 && idx > 0) { // BACKSPACE
            idx--;
            printf("\b \b");
        }
        else if (((ch >= '0' && ch <= '9') || ch == '-') && idx < maxLen - 1) {
            buffer[idx++] = ch;
            printf("%c", ch);
        }
    }
}

int inputTelpWithEsc(char *buffer, int maxLen) {
    int idx = 0;
    while (1) {
        char ch = _getch();

        if (ch == 27) { // ESC
            return 0;  // Return 0 = user cancel
        }
        else if (ch == 13) { // ENTER
            buffer[idx] = '\0';
            return 1;  // Return 1 = success
        }
        else if (ch == 8 && idx > 0) { // BACKSPACE
            idx--;
            printf("\b \b");
        }
        else if (ch >= '0' && ch <= '9' && idx < maxLen - 1) {
            buffer[idx++] = ch;
            printf("%c", ch);
        }
    }
}

int pwESC(char *pw, int col, int row) {
    int i = 0;
    char ch;

    while (1) {
        ch = _getch();

        if (ch == 27) { // ESC
            return 0;       // Return 0 = user cancel
        }
        else if (ch == 13) { // ENTER
            pw[i] = '\0';
            return 1;       // Return 1 = success
        }
        else if (ch == 8 && i > 0) { // BACKSPACE
            i--;
            printf("\b \b");
        }
        else if (i < 49 && ch >= 32 && ch <= 126) {
            pw[i++] = ch;
            printf("*");
        }
    }
}

#endif