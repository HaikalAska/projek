#ifndef PROJEK_LAPORAN_H
#define PROJEK_LAPORAN_H
#include <stdio.h>
#include "../FrameTabel.h"
#include "Laporan-Bulanan.h"
#include "SortirA-Z.h"


void menuManager();

void Laporan() {
    int Pilih;
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
    readTiketPenumpang();
    bentukframe(3, 29, 27, 10);
    gotoxy(5,30); printf("===  MENU NAVIGASI  ===");
    gotoxy(4, 32);printf("NAVIGASI [\xE2\x86\x91 \xE2\x86\x93]");
    gotoxy(4, 34);printf("[ENTER] Pilih");
    gotoxy(4, 36);printf("[Esc] Keluar");

    bentukframe(3, 10, 27, 14);
    gotoxy(9, 11);printf(" LIHAT LAPORAN \n");
    gotoxy(3, 13);printf("    Laporan Bulan-Tahun\n");
    gotoxy(3, 15);printf("    Urutkan A-Z\n");
    gotoxy(3, 17);printf("    Kembali\n");

    Pilih = menuNavigasi(3, 13, 2);

    switch (Pilih) {
        case 1:
            laporanBulanan();
            break;
        case 2:
            SortirLaporan();
            break;
        case 3:
            menuManager();
            break;
    }
}

#endif //PROJEK_LAPORAN_H