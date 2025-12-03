#ifndef PROJEK_PESANTIKET_H
#define PROJEK_PESANTIKET_H

#include "FrameTabel.h"
#include <stdio.h>
#include <io.h>



typedef struct {
    wchar_t destinasi[50];
    float harga;
} Destinasi;


static void PesanTiket() {
    int pilihan;
    char ch;
    clearscreen();
    printBorder(1, 1, 153, 43);
    FrameYangTengah(31, 1, 43);
    FrameYangHider(1,9,153);
    tampilanlogin("GAMBARASCI.txt", 60, 3);
    BentukFrame(34, 12, 60, 10);

    gotoxy(57, 11);
    wprintf(L"SELAMAT DATANG");
    gotoxy(9,11);
    wprintf(L"Pemesanan Tiket");


    Destinasi list[] = {
        {L"Jakarta --> Bandung", 65000.00},
        {L"Jakarta --> Surabaya", 170000.00},
        {L"Jakarta --> Jogja", 140000.00},
    };
    int jumlah = sizeof(list) / sizeof(Destinasi);

    gotoxy(38, 13);
    wprintf(L"  %-3s | %-25s |   %-15s ",
                   "No", "      Destinasi", "   Harga");
    for (int i = 0; i < jumlah; i++) {
        gotoxy(38, 15 + i * 2);
        wprintf(L"  %-3d | %-25ls |   Rp %-12.2f ",
               i + 1, list[i].destinasi, list[i].harga);
    }



    gotoxy(97,11);
    printf("Data Penumpang");



    //NOTE GUA PENGEN PAS KEMBALI PENCET TOMBOL DI KYBOARD
    while (1) {
        gotoxy(5, 18);
        printf("Tekan Esc untuk Kembali");

        ch = getch();

        if (ch == 27) {
            return;
        }
    }


    gotoxy(65, 30);
    printf("Tekan ENTER untuk kembali...");
    getchar();
}

#endif //PROJEK_PESANTIKET_H