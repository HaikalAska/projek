//
// Created by yoyop on 09/12/2025.
//

#ifndef PROJEK_CREATERUTE_H
#define PROJEK_CREATERUTE_H
#ifndef READ_RUTE_H
#define READ_RUTE_H

#include "../FrameTabel.h"
#include <stdio.h>
#include <conio.h>

extern RuteBus daftarRute[100];
extern int jumlahRute;

void readRute() {
    clearscreen();
    fillBackground(0x90);
    printBorder(1, 1, 153, 43);

    // HEADER READ
    gotoxy(60, 3); printf("╔══════════════════════════╗");
    gotoxy(60, 4); printf("║        READ RUTE       ║");
    gotoxy(60, 5); printf("╚══════════════════════════╝");

    if (jumlahRute == 0) {
        gotoxy(55, 10); printf("BELUM ADA DATA RUTE!");
        gotoxy(55, 12); printf("Tekan Enter untuk kembali...");
        getch();
        return;
    }

    // Tabel header
    gotoxy(5, 8);  printf("┌─────┬───────────┬──────────────────┬──────────────────┬───────────┬────────┬──────────────┐");
    gotoxy(5, 9);  printf("│ NO  │ KODE RUTE │ POSISI AWAL      │ TUJUAN AKHIR     │ HARGA     │ JARAK  │ WAKTU TEMPUH │");
    gotoxy(5, 10); printf("├─────┼───────────┼──────────────────┼──────────────────┼───────────┼────────┼──────────────┤");

    // Tampilkan data
    for (int i = 0; i < jumlahRute; i++) {
        gotoxy(5, 11 + i);
        printf("│ %-3d │ %-9s │ %-16s │ %-16s │ Rp %-6d │ %-6d │ %-12s │",
               i + 1,
               daftarRute[i].kode_rute,
               daftarRute[i].posisi_awal,
               daftarRute[i].tujuan_akhir,
               daftarRute[i].harga,
               daftarRute[i].jarak,
               daftarRute[i].waktu_tempuh);
    }

    // Footer tabel
    gotoxy(5, 11 + jumlahRute);
    printf("└─────┴───────────┴──────────────────┴──────────────────┴───────────┴────────┴──────────────┘");

    // Info
    gotoxy(5, 13 + jumlahRute);
    printf("TOTAL RUTE: %d DATA", jumlahRute);

    gotoxy(5, 15 + jumlahRute);
    printf("Tekan Enter untuk kembali...");
    getch();
}

#endif //PROJEK_CREATERUTE_H
