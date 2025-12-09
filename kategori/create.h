//
// Created by ASUS on 12/8/2025.
//

#ifndef PROJEK_CREATE_H
#define PROJEK_CREATE_H

typedef struct {
    int id;
    char nama[50];
    char deskripsi[100];
}kategori;

//======================================
//prosedur untuk input data kategori.dat
//======================================
static void buatkategori() {
    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);
    gotoxy(8,5); printf("Kelompok 5");

    // FILE *kategorifile = fopen("kategori.dat","ab");
    // char lagi = 'y';
    // while (lagi == 'y' || lagi == 'Y') {
    //     kategori k;
    //
    //     gotoxy(51,12); printf("===== Buat Kategori =====");
    //     gotoxy(36,14); printf("ID : ");
    //     scanf("%d", &k.id);
    //     getchar();
    //
    //     gotoxy(36,16);printf("Nama kategori : ");
    //     fgets(k.nama, sizeof(k.nama), stdin);
    //     k.nama[strcspn(k.nama, "\n")] = '\0';
    //
    //     gotoxy(36,18);printf("Deskripsi : ");
    //     fgets(k.deskripsi, sizeof(k.deskripsi), stdin);
    //     k.deskripsi[strcspn(k.deskripsi, "\n")] = '\0';
    //
    //     fwrite(&k, sizeof(kategori), 1, kategorifile);
    //
    //     gotoxy(34,21); printf("Tambah lagi? (y/n): ");
    //     scanf(" %c", &lagi);
    // }
    // fclose(kategorifile);
    FILE *kategorifile = fopen("kategori.dat","ab");
    char lagi = 'y';

    do {
        kategori k;

        gotoxy(51,12); printf("===== Buat Kategori =====");
        gotoxy(36,14); printf("ID : ");
        scanf("%d", &k.id);
        getchar();

        gotoxy(36,16); printf("Nama kategori : ");
        fgets(k.nama, sizeof(k.nama), stdin);
        k.nama[strcspn(k.nama, "\n")] = '\0';

        gotoxy(36,18); printf("Deskripsi : ");
        fgets(k.deskripsi, sizeof(k.deskripsi), stdin);
        k.deskripsi[strcspn(k.deskripsi, "\n")] = '\0';

        fwrite(&k, sizeof(kategori), 1, kategorifile);

        gotoxy(34,21); printf("Tambah lagi? (y/n): ");
        scanf(" %c", &lagi);

    } while (lagi == 'y' || lagi == 'Y');

    fclose(kategorifile);

}

#endif //PROJEK_CREATE_H