//
// Created by ASUS on 12/8/2025.
//

#ifndef PROJEK_DELETE_H
#define PROJEK_DELETE_H




//=================================================================
//prosedur untuk menghapus data yang ada di dalam file kategori.dat
//=================================================================
static void hapuskategori() {

    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);
    gotoxy(8,5); printf("Kelompok 5");
    BentukFrame(34, 11, 60, 9);


    FILE *kategorifile = fopen("kategori.dat", "rb");

    FILE *temp = fopen("temp.dat", "wb");

    int idHapus;
    kategori k;
    int found = 0;

    gotoxy(51,12);printf("===== Hapus Kategori =====");
    gotoxy(36, 14); printf("ID yang ingin dihapus : ");
    scanf("%d", &idHapus);
    getchar();

    rewind(kategorifile);

    while (fread(&k, sizeof(kategori), 1, kategorifile)) {
        if (k.id == idHapus) {
            found = 1;
        } else {
            fwrite(&k, sizeof(kategori), 1, temp); // salin yang bukan target
        }
    }

    fclose(kategorifile);
    fclose(temp);

    remove("kategori.dat");
    rename("temp.dat", "kategori.dat");

    if (found) {
        gotoxy(75, 13); printf("Data kategori dengan ID %d berhasil dihapus!\n", idHapus);
    } else {
        gotoxy(75, 13); printf("Data dengan ID %d tidak ditemukan!\n", idHapus);
    }
}

#endif //PROJEK_DELETE_H