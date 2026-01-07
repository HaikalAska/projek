#ifndef PROJEK_MENU_H
#define PROJEK_MENU_H
#include "FrameTabel.h"

#include "superadmin/KelolaStaff.h"
#include "Kendaraan/menuKendaraan.h"
#include "rute/menurute.h"
#include "jadwal/menujadwal.h"
#include "pemesanantiket.h"
#include "Laporan-Manager/laporan.h"
#include "pembatalan/pengembaliantiket.h"


void validLogin();

 void menuSuperAdmin() {
    int pilih;

    while (1) {
        system("chcp 65001 > nul");
        fillBackground(0x90);
        bentukframe(2, 1, 30, 45); //SIDEBAR KIRI
        bentukframe(34, 1, 121, 10); //ASCI
        bentukframe(3, 4, 27, 3); //KELOMPOK 5
        tampilanlogin("GAMBARASCI.txt", 45, 3);
        gotoxy(11,5); printf("Kelompok 5");
        bentukframe(3, 29, 27, 8);
        gotoxy(5,30); printf("===  MENU NAVIGASI  ===");
        gotoxy(4, 32);printf("NAVIGASI [\xE2\x86\x91 \xE2\x86\x93]");
        gotoxy(4, 34);printf("[ENTER] Pilih");



        bentukframe(3, 10, 27, 8);
        gotoxy(4, 11); printf("==== MENU SUPERADMIN ====\n");
        gotoxy(3, 13); printf("[1] Kelola Data Staff\n");;
        gotoxy(3, 15);printf("    Log Out\n");
        pilih = menuNavigasi(2, 13, 2);

        switch (pilih) {
            case 1:
                MenukelolaStaff();
                break;
            case 2:
                validLogin();
               break;
        }

    }

}



 void menuStaff() {
    int pilih;

    while (1) {
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



        bentukframe(3, 10, 27, 14);
        gotoxy(10, 11); printf(" MENU STAFF \n");
        gotoxy(3, 13); printf("    Pemesanan Tiket\n");
        gotoxy(3, 15);printf("    Buat Kendaraan\n");
        gotoxy(3, 17);printf("    Buat rute\n");
        gotoxy(3, 19);printf("    Buat jadwal\n");
        gotoxy(3, 21);printf("    Log Out\n");
        pilih = menuNavigasi(5, 13, 2);

        switch (pilih) {
            case 1:
                pemesanantiket();
                break;
            case 2:
                menukendaraan();
                break;
            case 3:
            menurute();
                break;
            case 4:
                menujadwal();
                break;
            case 5:
                validLogin();
                break;
        }
    }
}


 void menuManager() {
    int pilih;

    while (1) {
        system("chcp 65001 > nul");
        fillBackground(0x90);
        bentukframe(2, 1, 30, 45); //SIDEBAR KIRI
        bentukframe(34, 1, 121, 10); //ASCI
        bentukframe(3, 4, 27, 3); //KELOMPOK 5
        tampilanlogin("GAMBARASCI.txt", 45, 3);
        gotoxy(8,5); printf("Kelompok 5");
        bacaManagerHalo(60,12);
        bentukframe(3, 29, 27, 10);
        gotoxy(5,30); printf("  MENU NAVIGASI  ");
        gotoxy(4, 32);printf("NAVIGASI [\xE2\x86\x91 \xE2\x86\x93]");
        gotoxy(4, 34);printf("[ENTER] Pilih");
        gotoxy(4, 36);printf("[Esc] Keluar");


        bentukframe(3, 10, 27, 14);
        gotoxy(9, 11);printf(" MENU MANAGER \n");
        gotoxy(3, 13);printf("    Lihat Laporan\n");
        gotoxy(3, 15);printf("    Log Out\n");

        bentukTabel(35, 17, 30, 7, "TOTAL KARYAWAN");
        totalStaff(48, 21);


        bentukTabel(67, 17, 30, 7, "TOTAL TRANSAKSI");
        transaksi(81,21);

        bentukTabel(100, 17, 30, 7, "TOTAL PENGEMBALIAN");
        pengembalian(114,21);


        bentukTabel(35, 25, 95, 7, "TOTAL PENDAPATAN");
        pendapatan(79,29);


        pilih = menuNavigasi(2, 13, 2);


        switch (pilih) {
            case 1:
                laporanBulanan();
                break;
            case 2:
                validLogin();
                break;
        }


        gotoxy(3, 25); printf("====== Anda Log Out ======");
        getchar();
        return;
    }
}

#endif