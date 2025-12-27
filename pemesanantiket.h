//
// Created by Asus on 14/12/2025.
//

#ifndef PROJEK_PEMESANANTIKET_H
#define PROJEK_PEMESANANTIKET_H

#include "Pemesanan/Pesantiket.h"

static void menuStaff();


void pemesanantiket() {
    int pilih;

    while (1) {
        system("chcp 65001 > nul");
        fillBackground(0x90);
        bentukframe(2, 1, 30, 45); //SIDEBAR KIRI
        bentukframe(34, 1, 121, 10); //ASCI
        bentukframe(3, 4, 27, 3); //KELOMPOK 5
        tampilanlogin("GAMBARASCI.txt", 60, 3);
        gotoxy(8,5); printf("Kelompok 5");
        bentukframe(3, 29, 27, 10);
        gotoxy(5,30); printf("===  MENU NAVIGASI  ===");
        gotoxy(4, 32);printf("NAVIGASI [\xE2\x86\x91 \xE2\x86\x93]");
        gotoxy(4, 34);printf("[ENTER] Pilih");
        gotoxy(4, 36);printf("[Esc] Keluar");



        bentukframe(3, 10, 27, 14);
        gotoxy(8, 11); printf(" MENU PESAN TIKET \n");
        gotoxy(3, 13); printf("    Pesan tiket\n");
        gotoxy(3, 15); printf("    Pengembalian tiket\n");
        gotoxy(3, 17);printf("    Kembali\n");
        pilih = menuNavigasi(3, 13, 2);

        switch (pilih) {
        case 1:
                PesanTiket();
            break;
        case 2:

            break;
        case 3:
                menuStaff();
            break;
        }
    }
}
#endif //PROJEK_PEMESANANTIKET_H