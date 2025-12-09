//
// Created by Lenovo on 05/12/2025.
//

#ifndef PROJEK_CREATE_H
#define PROJEK_CREATE_H
#include "../FrameTabel.h"

int getStaffCount();
static void inputID(char *id);

typedef struct {
    char username[50];
    char password[50];
    char id[100];
    char tgl[100];
    char gender[100];
    int NOtlpn[50];
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
        gotoxy(3,15); printf("Nama         : ");inputID(data.username);
        gotoxy(3,16); printf("Kata Sandi   :");inputPassword(data.password,17, 16);
        gotoxy(3,17); printf("Tgl Lahir    : ");scanf("%s", data.tgl);
        gotoxy(3,18); printf("Kelamin      : ");scanf("%s", data.gender);
        gotoxy(3,19); printf("No Telpon    : ");scanf("%d", &data.NOtlpn);

        fwrite(&data, sizeof(staff), 1, fp);
        fclose(fp);

        gotoxy(3,20);
        printf("Data berhasil dibuat!");
        gotoxy(3,22);
        printf("Tambah lagi? (y/n): ");
        getchar();
        n = getchar();

    }while (n == 'y' || n == 'Y');
}

int getStaffCount() {
    FILE *fp = fopen("staff.dat", "rb");
    if (!fp) return 0;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);

    return size / sizeof(staff);
}
#endif