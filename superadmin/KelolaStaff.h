#ifndef PROJEK_KELOLASTAFF_H
#define PROJEK_KELOLASTAFF_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../FrameTabel.h"


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

        gotoxy(75,10); printf("====== KELOLA DATA STAFF ======");
        gotoxy(75, 11); printf("create\n");
        gotoxy(88, 11);printf("delete\n");
        gotoxy(100, 11  );printf("update\n");
        pilih = KAKINavigasi(3, 11,72, 13);
        switch (pilih) {}
    }
}

#endif //PROJEK_KELOLASTAFF_H