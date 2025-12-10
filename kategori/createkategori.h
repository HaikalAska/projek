//
// Created by ASUS on 12/8/2025.
//

#ifndef PROJEK_CREATEKATEGORI_H
#define PROJEK_CREATEKATEGORI_H

typedef struct {
    char id[50];
    char nama[50];
    char deskripsi[200];
}kategori;

//======================================
//prosedur untuk input data kategori.dat
//======================================
void buatkategori() {
    char lanjut;

    do {
        clearLine(11,35,60);
        clearLine(13,35,60);
        clearLine(15,35,60);
        clearLine(19,35,60);
        clearLine(21,35,60);

        FILE *kategorifile = fopen("kategori.dat", "ab");
        kategori k;

        gotoxy(35,11);
        printf("Id           : ");
        scanf("%s", k.id);

        gotoxy(35,13);
        printf("Kategori     : ");
        scanf("%s", k.nama);

        gotoxy(35,15);
        printf("Deskripsi    : ");
        scanf("%s", k.deskripsi);

        fwrite(&k, sizeof(kategori), 1, kategorifile);
        fclose(kategorifile);

        gotoxy(35,19);
        printf("Kategori telah dibuat");

        gotoxy(35,21);
        printf("Tambah lagi? (y/n) : ");
        scanf(" %c", &lanjut);

    } while (lanjut == 'y' || lanjut == 'Y');
}


#endif //PROJEK_CREATE_H