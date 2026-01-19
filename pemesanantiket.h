//
// Created by Asus on 14/12/2025.
//

#ifndef PROJEK_PEMESANANTIKET_H
#define PROJEK_PEMESANANTIKET_H

#include "Pemesanan/Pesantiket.h"
#include "pembatalan/pengembaliantiket.h"

static void menuStaff();
void generateDummyTiket();

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
void generateDummyTiket() {
    FILE *fp = fopen("tiket.dat", "ab");
    if (!fp) {
        printf("Error: Tidak bisa buka file tiket.dat!\n");
        return;
    }

    // Data dummy nama
    char *nama[] = {
        "Budi Santoso", "Siti Nurhaliza", "Ahmad Dahlan",
        "Dewi Lestari", "Eko Prasetyo", "Fitri Handayani",
        "Gunawan Wijaya", "Hana Permata", "Irfan Hakim",
        "Joko Widodo", "Kartika Sari", "Linda Wijaya",
        "Muhammad Rizki", "Nur Azizah", "Oscar Lawalata"
    };

    // Data dummy rute
    char *rute_awal[] = {"Jakarta", "Bandung", "Surabaya", "Yogyakarta", "Semarang"};
    char *tujuan[] = {"Bali", "Malang", "Solo", "Medan", "Makassar"};

    // Data dummy armada
    char *armada[] = {"Eka Prima", "Harapan Jaya", "Sinar Jaya", "Pusaka Jaya", "Maju Lancar"};

    // Data dummy tanggal & jam
    char *tanggal[] = {"12/02/2026", "13/05/2026", "14/04/2026", "15/10/2026", "16/09/2026"};
    char *jam[] = {"08:00", "10:30", "13:00", "15:30", "18:00"};

    // Harga
    long harga[] = {150000, 200000, 250000, 300000, 350000};

    // Metode bayar
    char *metode[] = {"Cash", "Cashless"};

    // No telp prefix
    char *telp_prefix[] = {"0812", "0813", "0851", "0852", "0877"};

    int count = getTiketCount();

    // Generate 15 dummy data
    for (int i = 0; i < 15; i++) {
        tiket data;

        // ID Tiket
        sprintf(data.id_tiket, "TKT%03d", count + i + 1);

        // ID Penumpang
        sprintf(data.id_penumpang, "PNP%03d", count + i + 1);

        // Nama
        strcpy(data.nama_penumpang, nama[i % 15]);

        // Rute
        strcpy(data.rute_awal, rute_awal[i % 5]);
        strcpy(data.tujuan, tujuan[i % 5]);

        // Armada
        strcpy(data.nama_armada, armada[i % 5]);

        // Tanggal & Jam berangkat
        strcpy(data.tanggal_berangkat, tanggal[i % 5]);
        strcpy(data.jam_berangkat, jam[i % 5]);

        // Harga
        data.harga = harga[i % 5];

        // No Telepon (random 8 digit)
        sprintf(data.notlpn, "%s%04d%04d", telp_prefix[i % 5], 1000 + (i * 123) % 9000, 1000 + (i * 456) % 9000);

        // Email
        sprintf(data.Email, "%s%d@gmail.com", "user", count + i + 1);

        // Metode bayar
        strcpy(data.metode_bayar, metode[i % 2]);

        // Tanggal booking
        strcpy(data.tanggal_booking, "11/01/2026");

        // Time (waktu pemesanan)
        sprintf(data.jam_berangkat, "%02d:%02d", 8 + (i % 10), (i * 7) % 60, (i * 13) % 60);

        // Status
        strcpy(data.status, "Aktif");

        // Tulis ke file
        fwrite(&data, sizeof(tiket), 1, fp);
    }

    fclose(fp);

    printf("\n=== DUMMY DATA BERHASIL DIBUAT ===\n");
    printf("Total: 15 tiket dummy telah ditambahkan!\n");
    printf("Tekan tombol apapun untuk kembali...");
    getch();
}
#endif //PROJEK_PEMESANANTIKET_H