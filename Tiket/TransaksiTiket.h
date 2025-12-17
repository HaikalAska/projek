#ifndef PROJEK_PENUMPANG_H
#define PROJEK_PENUMPANG_H

#include <stdio.h>
#include <stdlib.h>

#include "../FrameTabel.h"
#include "createTiket.h"
// #include "dummy_penumpang.h"
#include "readpenumpang.h"
#include "../pemesanantiket.h"

void pemesanantiket();

void menupenumpang() {
    int pilih;

    while (1) {
        clearscreen();
        system("chcp 65001 > nul");
        fillBackground(0x90);

        // ===== FRAME UTAMA (SAMA DENGAN STAFF) =====
        bentukframe(2, 1, 30, 45);      // Sidebar kiri
        bentukframe(34, 1, 121, 10);    // ASCII Header
        bentukframe(3, 4, 27, 3);       // Kelompok

        tampilanlogin("GAMBARASCI.txt", 60, 3);
        gotoxy(11,5); printf("Kelompok 5");

        // ===== MENU NAVIGASI (IDENTIK STAFF) =====
        bentukframe(3, 29, 27, 10);
        gotoxy(5,30); printf("===  MENU NAVIGASI  ===");
        gotoxy(4,32); printf("NAVIGASI [\xE2\x86\x91 \xE2\x86\x93]");
        gotoxy(4,34); printf("[ENTER] Pilih");
        gotoxy(4,36); printf("[Esc] Keluar");

        // ===== MENU UTAMA (IDENTIK STAFF) =====
        bentukframe(3, 10, 27, 14);
        gotoxy(5,11); printf(" KELOLA DATA PENUMPANG ");
        gotoxy(6,13); printf("Buat");
        gotoxy(6,15); printf("kembali");
        // gotoxy(6,21); printf("50Dummy");

        pilih = menuNavigasi(2, 13, 2);

        switch (pilih) {
        case 1:
            createPenumpang();
            break;
        case 2:
                pemesanantiket();
            break;
        }
    }
}

#endif // PROJEK_PENUMPANG_H
