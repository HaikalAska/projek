//
// Created by Lenovo on 05/12/2025.
//

#ifndef PROJEK_CREATE_H
#define PROJEK_CREATE_H
#include "../FrameTabel.h"

typedef struct {
    char username[50];
    char password[50];
    char id[100];
}staff;

void create() {
    gotoxy(3,8); printf("[Esc] Keluar");
    FILE *fp = fopen("staff.dat", "wb");
    staff data;
    int n;
    gotoxy(3,13);printf("masukkan banyak user : ");
    scanf("%d",&n);



    for (int i = 0; i < n; i++) {

        clearArea(3, 14, 17);

        gotoxy(3,14); printf("User %d", i + 1);

        gotoxy(3,15); printf("Id: ");
        scanf("%s",data.id);
        gotoxy(3,16); printf("Username: ");
        scanf("%s", data.username);
        gotoxy(3,17); printf("Password: ");
        scanf("%s", data.password);
        fwrite(&data, sizeof(staff), 1, fp);
    }

    fclose(fp);
    gotoxy(3,18); printf("Data berhasil di buat");
    getchar();
    getchar();
}
#endif