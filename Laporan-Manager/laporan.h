//
// Created by Asus on 07/01/2026.
//

#ifndef PROJEK_LAPORAN_H
#define PROJEK_LAPORAN_H


#include "../FrameTabel.h"

void laporan() {
    system("chcp 65001 > nul");
    fillBackground(0x90);
    bentukframe(2, 1, 30, 45); //SIDEBAR KIRI
    bentukframe(34, 1, 121, 10); //ASCI
    bentukframe(3, 4, 27, 3); //KELOMPOK 5
    tampilanlogin("GAMBARASCI.txt", 45, 3);
    gotoxy(8,5); printf("Kelompok 5");
    bentukframe(3, 29, 27, 10);
    gotoxy(5,30); printf("===  MENU NAVIGASI  ===");
    gotoxy(4, 32);printf("NAVIGASI [\xE2\x86\x91 \xE2\x86\x93]");
    gotoxy(4, 34);printf("[ENTER] Pilih");
    gotoxy(4, 36);printf("[Esc] Keluar");




}

#endif //PROJEK_LAPORAN_H