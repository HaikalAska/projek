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
        clearLine(12,37,60);
        clearLine(14,35,60);
        clearLine(15,35,60);
        clearLine(16,35,60);
        clearLine(21,35,80);
        clearLine(18,35,60);
        BentukFrame(35,11,60,10);

        FILE *kategorifile = fopen("kategori.dat", "ab");
        kategori k;
        gotoxy(53,12); printf("=== Buat Kategori ===");
        gotoxy(37,14);
        printf("Id           : ");
        scanf("%s", k.id);

        gotoxy(37,15);
        printf("Kategori     : ");
        scanf("%s", k.nama);

        gotoxy(37,16);
        printf("Deskripsi    : ");
        scanf("%s", k.deskripsi);

        fwrite(&k, sizeof(kategori), 1, kategorifile);
        fclose(kategorifile);

        gotoxy(53,21);
        printf("Kategori telah dibuat!!");

        gotoxy(37,18);
        printf("Tambah lagi? (y/n) : ");
        scanf(" %c", &lanjut);

    } while (lanjut == 'y' || lanjut == 'Y');
}


#endif //PROJEK_CREATE_H