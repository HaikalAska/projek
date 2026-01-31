//
// Created by ASUS on 12/16/2025.
//

#ifndef PROJEK_MENUJADWAL_H
#define PROJEK_MENUJADWAL_H

#include "createjadwal.h"
#include "readjadwal.h"
#include "deletejadwal.h"
#include "updatejadwal.h"

static void menuStaff();
void  menujadwal() {
    int pilih;

    while (1) {
        clearscreen();
        system("chcp 65001 > nul");
        fillBackground(0x90);
        bentukframe(2, 1, 30, 45); //SIDEBAR KIRI
        bentukframe(34, 1, 121, 10); //ASCI
        bentukframe(3, 4, 27, 3); //KELOMPOK 5
        tampilanlogin("GAMBARASCI.txt", 45, 3);
        gotoxy(11,5); printf("Kelompok 5");
        bacajadwal();
        bentukframe(3, 29, 27, 14);
        gotoxy(5,30); printf("===  MENU NAVIGASI  ===");
        gotoxy(4, 32);printf("NAVIGASI [\xE2\x86\x91 \xE2\x86\x93]");
        gotoxy(4, 34);printf("[ENTER] Pilih");
        gotoxy(4, 36);printf("[Esc] Keluar");
        gotoxy(4, 38);printf("[Space] Lanjut");
        gotoxy(4, 40);printf("[Backspace] Kembali");

        bentukframe(3, 10, 27, 14);
        gotoxy(4,11); printf("=== KELOLA JADWAL ===");
        gotoxy(6, 13); printf("Buat\n");
        gotoxy(6, 15);printf("Hapus\n");
        gotoxy(6, 17);printf("Perbarui\n");
        gotoxy(6, 19);printf("Kembali\n");
        pilih = menuNavigasi(4, 13,2);
        switch (pilih) {
            case 1:
                buatjadwal();
                break;
            case 2:
                hapusjadwal();
                break;
            case 3:
                perbaruijadwal();//buatdummyjadwal();
                break;
            case 4:
                menuStaff();
                break;
        }
    }
}

#endif //PROJEK_MENUJADWAL_H