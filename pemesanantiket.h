//
// Created by Asus on 14/12/2025.
//

#ifndef PROJEK_PEMESANANTIKET_H
#define PROJEK_PEMESANANTIKET_H

#include "Pemesanan/Pesantiket.h"
#include "pembatalan/pengembaliantiket.h"

static void menuStaff();
void generateDummyTiket(int Total);

void pemesanantiket() {
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
        readTiketPenumpang();


        bentukframe(3, 10, 27, 14);
        gotoxy(8, 11); printf(" MENU PESAN TIKET \n");
        gotoxy(3, 13); printf("    Pesan tiket\n");
        gotoxy(3, 15); printf("    Pengembalian tiket\n");
        gotoxy(3, 17);printf("    Kembali\n");
        pilih = menuNavigasi(3, 13, 2);

        switch (pilih) {
        case 1:
                PesanTiket();
            break;
        case 2:
                BatalTiket();
            break;
        case 3:
                menuStaff();
            break;
        }
    }
}








//========CUMA BUAT DUMMY AJA =============================//


int randRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

void generateDummyTiket(int total) {
    FILE *fp = fopen("tiket.dat", "ab");
    if (!fp) {
        printf("Error: Tidak bisa buka file tiket.dat!\n");
        return;
    }

    srand(time(NULL));

    char *nama[] = {
        "Budi Santoso", "Siti Nurhaliza", "Ahmad Dahlan",
        "Dewi Lestari", "Eko Prasetyo", "Fitri Handayani",
        "Gunawan Wijaya", "Hana Permata", "Irfan Hakim",
        "Joko Widodo", "Kartika Sari", "Linda Wijaya",
        "Muhammad Rizki", "Nur Azizah", "Oscar Lawalata",
        "Rama Putra", "Putri Ayu", "Dika Pratama"
    };

    char *kota[] = {
        "Jakarta", "Bandung", "Surabaya", "Yogyakarta",
        "Semarang", "Malang", "Solo", "Medan", "Makassar"
    };

    char *armada[] = {
        "Eka Prima", "Harapan Jaya", "Sinar Jaya",
        "Pusaka Jaya", "Maju Lancar"
    };

    char *metode[] = {"Tunai", "Non-Tunai"};
    char *telp_prefix[] = {"0812", "0813", "0851", "0852", "0877"};

    int count = getTiketCount();

    for (int i = 0; i < total; i++) {
        tiket data;

        sprintf(data.id_tiket, "TKT%03d", count + i + 1);
        sprintf(data.id_penumpang, "PNP%03d", count + i + 1);

        strcpy(data.nama_penumpang, nama[rand() % 18]);

        strcpy(data.rute_awal, kota[rand() % 9]);
        strcpy(data.tujuan, kota[rand() % 9]);
        while (strcmp(data.rute_awal, data.tujuan) == 0) {
            strcpy(data.tujuan, kota[rand() % 9]);
        }

        strcpy(data.nama_armada, armada[rand() % 5]);

        int hari = randRange(1, 28);
        int bulan = randRange(1, 12);
        int tahun = randRange(2023, 2026);
        sprintf(data.tanggal_berangkat, "%02d/%02d/%d", hari, bulan, tahun);

        int jam = randRange(0, 23);
        int menit = randRange(0, 59);
        sprintf(data.jam_berangkat, "%02d:%02d", jam, menit);

        data.harga = randRange(70000, 300000);

        sprintf(data.notlpn, "%s%08d",
                telp_prefix[rand() % 5],
                randRange(10000000, 99999999));

        sprintf(data.Email, "user%d@gmail.com", count + i + 1);

        strcpy(data.metode_bayar, metode[rand() % 2]);

        sprintf(data.tanggal_booking, "%02d/%02d/%d",
                randRange(1, 28),
                randRange(1, 12),
                randRange(2023, 2026));

        strcpy(data.status, "Aktif");

        fwrite(&data, sizeof(tiket), 1, fp);
    }

    fclose(fp);

    printf("\n=== DUMMY DATA RANDOM BERHASIL DIBUAT ===\n");
    printf("Total: %d tiket dummy ditambahkan!\n", total);
    printf("Tekan tombol apapun untuk kembali...");
    getch();
}

#endif //PROJEK_PEMESANANTIKET_H