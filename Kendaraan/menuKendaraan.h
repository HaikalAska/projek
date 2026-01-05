#ifndef PROJEK_MENUKENDARAAN_H
#define PROJEK_MENUKENDARAAN_H

#include <stdio.h>
#include <stdlib.h>

#include "../FrameTabel.h"
#include "createKendaraan.h"
#include "deleteKendaraan.h"
#include "updateKendaraan.h"
#include "readKendaraan.h"


static void menuStaff();
void menukendaraan() {
    int pilih;

    while (1) {
        clearscreen();
        system("chcp 65001 > nul");
        fillBackground(0x90);
        clearscreen();
        system("chcp 65001 > nul");
        fillBackground(0x90);
        bentukframe(2, 1, 30, 45); //SIDEBAR KIRI
        bentukframe(34, 1, 121, 10); //ASCI
        bentukframe(3, 4, 27, 3); //KELOMPOK 5
        tampilanlogin("GAMBARASCI.txt", 45, 3);
        bentukframe(3, 4, 27, 3); //INFORMASI JABATAN
        gotoxy(13,5); printf("Staff");
        gotoxy(11,2); printf("Kelompok 5");
        readKendaraan();
        bentukframe(3, 29, 27, 10);
        gotoxy(5,30); printf("===  MENU NAVIGASI  ===");
        gotoxy(4, 32);printf("NAVIGASI [\xE2\x86\x91 \xE2\x86\x93]");
        gotoxy(4, 34);printf("[ENTER] Pilih");
        gotoxy(4, 36);printf("[Esc] Keluar");

        // ================= MENU UTAMA =================
        bentukframe(3, 10, 27, 14);
        gotoxy(4, 11); printf("=== KELOLA KENDARAAN ===");

        gotoxy(6, 13); printf("Tambah Kendaraan");
        gotoxy(6, 15); printf("Hapus Kendaraan");
        gotoxy(6, 17); printf("Perbarui Data");
        gotoxy(6, 19); printf("Kembali ");

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
                menuStaff();
                break;

        }
    }
}

#endif // PROJEK_MENUKENDARAAN_H
