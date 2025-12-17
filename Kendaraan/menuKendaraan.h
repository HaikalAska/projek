#ifndef PROJEK_MENUKENDARAAN_H
#define PROJEK_MENUKENDARAAN_H

#include <stdio.h>
#include <stdlib.h>

#include "../FrameTabel.h"
#include "createKendaraan.h"
#include "deleteKendaraan.h"
#include "updateKendaraan.h"
#include "readKendaraan.h"
#include "../login.h"
#include "../Menu.h"


void menukendaraan() {
    int pilih;

    while (1) {
        clearscreen();
        system("chcp 65001 > nul");
        fillBackground(0x90);

        // ================= FRAME =================
        bentukframe(2, 1, 30, 45);      // SIDEBAR KIRI
        bentukframe(34, 1, 121, 10);    // ASCII HEADER
        bentukframe(3, 4, 27, 3);       // KELOMPOK
        tampilanlogin("GAMBARASCI.txt", 60, 3);
        gotoxy(11, 5); printf("Kelompok 5");

        readKendaraan();

        // ================= NAVIGASI =================
        bentukframe(3, 29, 27, 10);
        gotoxy(5, 30); printf("===  MENU NAVIGASI  ===");
        gotoxy(4, 32); printf("NAVIGASI [↑ ↓]");
        gotoxy(4, 34); printf("[ENTER] Pilih");
        gotoxy(4, 36); printf("[ESC] Keluar");

        // ================= MENU UTAMA =================
        bentukframe(3, 10, 27, 14);
        gotoxy(4, 11); printf("=== KELOLA KENDARAAN ===");

        gotoxy(6, 13); printf("Tambah Kendaraan");
        gotoxy(6, 15); printf("Hapus Kendaraan");
        gotoxy(6, 17); printf("Perbarui Data");
        gotoxy(6, 19); printf("Kembali");
        //gotoxy(6, 19); printf("Lihat Data");

        pilih = menuNavigasi(4, 13, 2);

        switch (pilih) {
            case 1:
                createKendaraan();
                break;
            case 2:
                deleteKendaraan();
                break;
            case 3:
                updateKendaraan();
                break;
            case 4:
                break;
            case 5:
                // buatDummyKendaraan();
                break;
        }
    }
}

#endif // PROJEK_MENUKENDARAAN_H
