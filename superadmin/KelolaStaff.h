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


void MenukelolaStaff() {
    int pilih;

    while (1) {
        clearscreen();
        system("chcp 65001 > nul");
        fillBackground(0x90);
        printBorder(1, 1, 153, 43);
        FrameYangTengah(31, 1, 43);
        FrameYangHider(1,9,153);
        tampilanlogin("GAMBARASCI.txt", 60, 3);
        gotoxy(8,5); printf("Kelompok 5");
        gotoxy(35, 10);printf("NAVIGASI \xE2\x86\x90 \xE2\x86\x92");
        baca();

        gotoxy(75,10); printf("====== KELOLA DATA STAFF ======");
        gotoxy(70, 11); printf("Buat\n");
        gotoxy(82, 11);printf("Hapus\n");
        gotoxy(94, 11);printf("Perbarui\n");
        gotoxy(106, 11);printf("Halaman\n");
        pilih = KAKINavigasi(4, 11,68, 12);
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