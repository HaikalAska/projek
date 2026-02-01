#ifndef PROJEK_KELOLASTAFF_H
#define PROJEK_KELOLASTAFF_H
#include <stdio.h>
#include <stdlib.h>

#include "../FrameTabel.h"
#include "create.h"
#include "delete.h"
#include "update.h"
#include "read.h"


 void menuSuperAdmin();


void  MenukelolaStaff() {
    int pilih;

    while (1) {
        clearscreen();
        system("chcp 65001 > nul");
        fillBackground(0x90);
        bentukframe(2, 1, 30, 45); //SIDEBAR KIRI
        bentukframe(34, 1, 121, 10); //ASCI
        bentukframe(3, 4, 27, 3); //KELOMPOK 5
        tampilanlogin("GAMBARASCI.txt", 45, 3);
        bentukframe(3, 4, 27, 3); //INFORMASI JABATAN
        gotoxy(11,5); printf("SuperAdmin");
        gotoxy(11,2); printf("Kelompok 5");
        baca();
        bentukframe(3, 29, 27, 10);
        gotoxy(5,30); printf("===  MENU NAVIGASI  ===");
        gotoxy(4, 32);printf("NAVIGASI [\xE2\x86\x91 \xE2\x86\x93]");
        gotoxy(4, 34);printf("[ENTER] Pilih Menu");
        gotoxy(4, 36);printf("[ESC] Daftar Staf");


        bentukframe(3, 10, 27, 13);
        gotoxy(4,11); printf("=== KELOLA DATA STAFF ===");
        gotoxy(6, 13); printf("Buat\n");
        gotoxy(6, 15);printf("Hapus\n");
        gotoxy(6, 17);printf("Perbarui\n");
        gotoxy(6, 19);printf("Kembali\n");
        pilih = menuNavigasi(4, 13,2);
        switch (pilih) {
            case 1:
                create();
                break;
            case 2:
                delete();
                break;
            case 3:
                update();
                break;
                case 4:
                menuSuperAdmin();
                break;
        }
    }
}

#endif //PROJEK_KELOLASTAFF_H