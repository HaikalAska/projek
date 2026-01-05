//
// Created by Asus on 16/12/2025.
//

#ifndef PROJEK_PEMBATALAN_H
#define PROJEK_PEMBATALAN_H

#include <stdio.h>
#include <stdlib.h>

#include "../FrameTabel.h"
#include "createpembatalan.h"
#include "readpembatalan.h"
#include "deletepembatalan.h"
#include "../login.h"
#include "../pemesanantiket.h"
//#include "Menu.h"


void (pemesanantiket)();

void menupembatalan() {
    int pilih;

    while (1) {
        clearscreen();
        system("chcp 65001 > nul");
        fillBackground(0x90);

        // ===== FRAME UTAMA =====
        bentukframe(2, 1, 30, 45);      // Sidebar kiri
        bentukframe(34, 1, 121, 10);    // Header ASCII
        bentukframe(3, 4, 27, 3);       // Kelompok

        tampilanlogin("GAMBARASCI.txt", 45, 3);
        gotoxy(11, 5); printf("Kelompok 5");

        // ===== TAMPIL DATA PROMO =====
        readPembatalan();

        // ===== MENU NAVIGASI =====
        bentukframe(3, 29, 27, 10);
        gotoxy(5,30); printf("===  MENU NAVIGASI  ===");
        gotoxy(4,32); printf("NAVIGASI [\xE2\x86\x91 \xE2\x86\x93]");
        gotoxy(4,34); printf("[ENTER] Pilih");
        gotoxy(4,36); printf("[Esc] Keluar");

        // ===== MENU UTAMA PROMO =====
        bentukframe(3, 10, 27, 14);
        gotoxy(4,11); printf("=== KELOLA DATA PEMBATALAN ===");
        gotoxy(6,13); printf("Buat ");
        gotoxy(6,15); printf("Kembali");
        //gotoxy(6,17); printf("Dummy Pembatalan");

        pilih = menuNavigasi(2, 13, 2);

        switch (pilih) {
        case 1:
            createPembatalan();
            break;
        case 2:
            pemesanantiket();
            //menuStaff();
            //deletepembatalan();
            break;
        case 3:
           // buatdummy_pembatalan_ke_file();
            break;
        case 4:
            return; // kembali ke menu sebelumnya
        case 5:
            // buatdummy_promo_ke_file();
            break;
        }
    }
}

#endif // PROJEK_REFUND_H

