#ifndef PROJEK_DELETE_H
#define PROJEK_DELETE_H
#include <stdio.h>
#include <string.h>

#include "create.h"

void delete(){
FILE *fp, *sampah;
    staff data;
    char target[50];
    int found = 0;

    fp = fopen("staff.dat","rb");
    sampah = fopen("sampah.dat","wb");

    gotoxy(3,13); printf("user delete:");
    scanf("%s", target);

    while (fread(&data, sizeof(staff), 1, fp) == 1) {
        if (strcmp(data.id, target) != 0) {
            fwrite(&data, sizeof(staff), 1, sampah);
        }
        else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(sampah);

    if (found) {
        remove( "staff.dat");
        rename("sampah.dat", "staff.dat");
        gotoxy(3,15); printf("User '%s' berhasil dihapus!", target);
    } else {
        remove("sampah.dat");
        gotoxy(3,15); printf("Data tidak ditemukan!");
    }
    getchar();
    getchar();

}


#endif