#ifndef PROJEK_KELOLASTAFF_H
#define PROJEK_KELOLASTAFF_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../FrameTabel.h"
#include "create.h"
#include "delete.h"
#include "update.h"
#include "read.h"
#include "../Menu.h"

 void menuSuperAdmin();


void MenukelolaStaff() {
    int pilih;

    while (1) {
        clearscreen();
        fillBackground(0x90);
        printBorder(1, 1, 153, 43);
        FrameYangTengah(31, 1, 43);
        FrameYangHider(1,9,153);
        tampilanlogin("GAMBARASCI.txt", 60, 3);
        gotoxy(8,5); printf("Kelompok 5");
        baca();

        gotoxy(75,10); printf("====== KELOLA DATA STAFF ======");
        gotoxy(75, 11); printf("create\n");
        gotoxy(80, 11);printf("delete\n");
        gotoxy(100, 11);printf("update\n");
        gotoxy(113, 11);printf("menu\n");
        pilih = KAKINavigasi(4, 11,72, 13);
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