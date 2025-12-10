#ifndef PROJEK_READRUTE_H
#define PROJEK_READRUTE_H

#include <stdio.h>
#include <string.h>
#include <conio.h>

void inputRute(Rute *temp) {
    char buffer[100];

    // VALIDASI ID HARUS TEPAT 4 DIGIT
    while (1) {
        printf("Masukkan ID Rute (4 digit angka): ");

        fgets(buffer, sizeof(buffer), stdin);


        buffer[strcspn(buffer, "\n")] = 0;


        if (strlen(buffer) != 4) {
            printf("ID harus tepat 4 digit!\n");
            continue;
        }

        // CEK HARUS ANGKA SEMUA
        if (strspn(buffer, "0123456789") != 4) {
            printf("ID hanya boleh angka!\n");
            continue;
        }

        // VALID → MASUKKAN KE STRUCT
        strcpy(temp->id, buffer);
        break;
    }

    printf("Masukkan Kota Awal   : ");
    scanf("%19s", temp->kotaAwal);

    printf("Masukkan Kota Tujuan : ");
    scanf("%19s", temp->kotaTujuan);

    printf("Masukkan Harga       : Rp ");
    scanf("%d", &temp->harga);

    // Bersihkan buffer setelah scanf angka
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    FILE *rutefile = fopen("rute.dat", "ab");
    fwrite(temp, sizeof(Rute), 1, rutefile);
    fclose(rutefile);

    printf("\nData rute berhasil ditambahkan!\n");
    getch();
}


void tampilkanSemuaRute() {
    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);

    gotoxy(8,5);
    printf("Kelompok 5");

    FILE *rutefile = fopen("rute.dat", "rb");
    if (!rutefile) {
        gotoxy(55, 12);
        printf("File rute tidak ditemukan!");
        getch();
        return;
    }

    Rute temp;

    int x = 32;
    int y = 14;
    int row = y + 3;

    gotoxy(55, 12);
    printf("========  DAFTAR RUTE  ========");

    gotoxy(x, y);
    printf("======================================================================");
    gotoxy(x, y + 1);
    printf("| %-4s | %-15s | %-15s | %-10s |",
           "ID", "Kota Awal", "Kota Tujuan", "Harga");
    gotoxy(x, y + 2);
    printf("======================================================================");

    while (fread(&temp, sizeof(Rute), 1, rutefile)) {

        gotoxy(x, row++);
        printf("| %-4s | %-15s | %-15s | Rp %-7d |",
               temp.id, temp.kotaAwal, temp.kotaTujuan, temp.harga);
    }

    fclose(rutefile);

    // FOOTER
    gotoxy(x, row);
    printf("======================================================================");

    gotoxy(55, row + 2);
    printf("Tekan apa saja untuk kembali...");

    getch();
}

#endif
