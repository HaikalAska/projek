//
// Created by ASUS on 12/5/2025.
//

#ifndef PROJEK_KATEGORI_H
#define PROJEK_KATEGORI_H
#include <stdio.h>
#include "../FrameTabel.h"
#include "../Menu.h"
#include "../PesanTiket.h"

void buatkategori();
void editkategori();
void hapuskategori();
void tampilanmenukategori();

typedef struct {
    int id;
    char nama[50];
    char deskripsi[100];
}kategori;

void tampilanmenukategori() {
    gotoxy(3,11); printf("===== DAFTAR KATEGORI =====");
    gotoxy(5,13); printf("   Create");
    gotoxy(5,15); printf("   Edit");
    gotoxy(5,17); printf("   Delete");
    gotoxy(5,19); printf("   Kembali");
}


//=========================================
//prosedur untuk menu pilihan pada kategori
//=========================================
void pilihkategori() {
    int pilih;

    while (1) {
    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);
    gotoxy(8,5); printf("Kelompok 5");
    //BentukFrame(14, 13, 60, 10);

    gotoxy(3,11); printf("===== DAFTAR KATEGORI =====");
    gotoxy(5,13); printf("   Create");
    gotoxy(5,15); printf("   Edit");
    gotoxy(5,17); printf("   Delete");
    gotoxy(5,19); printf("   Kembali");
    pilih = menuNavigasi(4,13,5);

        switch (pilih) {
            case 1:
                buatkategori();
                break;
            case 2:
                editkategori();
                break;
            case 3:
                hapuskategori();
                break;
            case 4:
                menuSuperAdmin();
                break;
        }
    }
}


//======================================
//prosedur untuk input data kategori.dat
//======================================
void buatkategori() {
    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);
    gotoxy(8,5); printf("Kelompok 5");
    BentukFrame(34, 11, 60, 10);
    tampilanmenukategori();

    FILE *kategorifile = fopen("kategori.dat","ab");
    if (!kategorifile) {
        perror("Gagal membuka file");
        return;
    }
    char lagi = 'y';
    while (lagi == 'y' || lagi == 'Y') {
        kategori k;

        gotoxy(51,12); printf("===== Buat Kategori =====");
        gotoxy(36,14); printf("ID : ");
        scanf("%d", &k.id);
        getchar();

        gotoxy(36,16);printf("Nama kategori : ");
        fgets(k.nama, sizeof(k.nama), stdin);
        k.nama[strcspn(k.nama, "\n")] = '\0';

        gotoxy(36,18);printf("Deskripsi : ");
        fgets(k.deskripsi, sizeof(k.deskripsi), stdin);
        k.deskripsi[strcspn(k.deskripsi, "\n")] = '\0';

        fwrite(&k, sizeof(kategori), 1, kategorifile);

        gotoxy(34,21); printf("Tambah lagi? (y/n): ");
        scanf(" %c", &lagi);
    }
    fclose(kategorifile);
}


//=========================================
//prosedur untuk mengedit file kategori.dat
//=========================================
void editkategori() {
    tampilanmenukategori();
    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);
    gotoxy(8,5); printf("Kelompok 5");
    BentukFrame(34, 11, 60, 13);
    tampilanmenukategori();

    FILE *kategorifile = fopen("kategori.dat", "rb+");
    if (!kategorifile) {
        perror("Gagal membuka file");
        return;
    }

    int idCari;
    kategori k;
    int found = 0;

    gotoxy(51,12);printf("===== Edit Kategori =====");

    gotoxy(36, 14); printf("ID yang ingin di edit : ");
    scanf("%d", &idCari);
    getchar();

    rewind(kategorifile);

    while (fread(&k, sizeof(kategori), 1, kategorifile)) {
        if (k.id == idCari) {
            found = 1;

            gotoxy(36, 16); printf("Nama kategori lama : %s", k.nama);
            gotoxy(36, 17); printf("Deskripsi lama     : %s", k.deskripsi);

            gotoxy(36, 19); printf("Nama kategori baru : ");
            fgets(k.nama, sizeof(k.nama), stdin);
            k.nama[strcspn(k.nama, "\n")] = '\0';

            gotoxy(36, 21); printf("Deskripsi baru     : ");
            fgets(k.deskripsi, sizeof(k.deskripsi), stdin);
            k.deskripsi[strcspn(k.deskripsi, "\n")] = '\0';

            fseek(kategorifile, -sizeof(kategori), SEEK_CUR);

            fwrite(&k, sizeof(kategori), 1, kategorifile);

            gotoxy(75, 19); printf("Data berhasil diperbarui!\n");
            break;
        }
    }

    if (!found) {
        gotoxy(75, 12); printf("Kategori dengan ID %d tidak ditemukan!\n", idCari);
    }

    fclose(kategorifile);
}


//=================================================================
//prosedur untuk menghapus data yang ada di dalam file kategori.dat
//=================================================================
void hapuskategori() {
    tampilanmenukategori();
    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);
    gotoxy(8,5); printf("Kelompok 5");
    tampilanmenukategori();

    FILE *kategorifile = fopen("kategori.dat", "rb");
    if (!kategorifile) {
        perror("Gagal membuka kategori.dat");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        perror("Gagal membuat file temp.dat");
        fclose(kategorifile);
        return;
    }

    int idHapus;
    kategori k;
    int found = 0;

    gotoxy(75, 10); printf("Masukkan ID kategori yang ingin dihapus: ");
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
#endif //PROJEK_KATEGORI_H