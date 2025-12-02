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
    gotoxy(3,14);
    wprintf(L"[2] Kembali");



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




    //NOTE GUA PENGEN PAS KEMBALI PENCET TOMBOL DI KYBOARD
    gotoxy(3,18);
    wprintf(L"Masukkan Pilihan : ");
    scanf("%d", &pilihan);


    gotoxy(65, 30);
    printf("Tekan ENTER untuk kembali...");
    getchar();
}

#endif //PROJEK_PESANTIKET_H