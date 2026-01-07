#ifndef PROJEK_LAPORAN_H
#define PROJEK_LAPORAN_H

#include "../FrameTabel.h"



void menuManager();
void laporanBulanan();
void laporanTahunan();

void laporan() {
    system("chcp 65001 > nul");
    fillBackground(0x90);
    bentukframe(2, 1, 30, 45); //SIDEBAR KIRI
    bentukframe(34, 1, 121, 10); //ASCI
    bentukframe(3, 4, 27, 3); //KELOMPOK 5
    tampilanlogin("GAMBARASCI.txt", 45, 3);
    gotoxy(10,5); printf("Kelompok 5");
    bentukframe(3, 29, 27, 10);
    gotoxy(5,30); printf("===  MENU NAVIGASI  ===");
    gotoxy(4, 32);printf("NAVIGASI [\xE2\x86\x91 \xE2\x86\x93]");
    gotoxy(4, 34);printf("[ENTER] Pilih");
    gotoxy(4, 36);printf("[Esc] Keluar");

    bentukframe(3, 10, 27, 14);
    bentukframe(3, 10, 27, 14);
    gotoxy(5, 11);
    printf("     MENU LAPORAN   ");
    gotoxy(6, 13);
    printf("Laporan Bulanan\n");
    gotoxy(6, 15);
    printf("Laporan Tahunan\n");
    gotoxy(6, 17);
    printf("Kembali\n");

    int pilih = menuNavigasi(3, 13, 2);

    switch (pilih) {
        case 1:
            laporanBulanan();
            break;
        case 2:
            laporanTahunan();
            break;
        case 3:
            menuManager();
            break;
    }
}




//BUAT BACA LAPORAN BULANAN
void laporanBulanan() {
    clearscreen();
    system("chcp 65001 > nul");
    fillBackground(0x90);
    bentukframe(34, 1, 121, 40);

    gotoxy(40, 3);
    printf("=== LAPORAN PEMBATALAN BULANAN ===");

    int bulan, tahun;
    gotoxy(40, 5);
    printf("Pilih Bulan dan Tahun:");
    gotoxy(40, 7);
    printf("Bulan (1-12): ");
    scanf("%d", &bulan);
    gotoxy(40, 8);
    printf("Tahun: ");
    scanf("%d", &tahun);

    // Validasi input
    if (bulan < 1 || bulan > 12) {
        gotoxy(40, 10);
        printf("Bulan tidak valid! Tekan tombol untuk kembali...");
        _getch();
        return;
    }

    clearscreen();
    fillBackground(0x90);
    bentukframe(34, 1, 121, 40);

    gotoxy(40, 3);
    printf("=== LAPORAN PEMBATALAN BULANAN - %02d/%d ===", bulan, tahun);

    // Baca file batal.dat
    FILE *file = fopen("tiket.dat", "rb");
    if (file == NULL) {
        gotoxy(40, 5);
        printf("File batal.dat tidak ditemukan!");
        gotoxy(40, 38);
        printf("Tekan tombol apapun untuk kembali...");
        _getch();
        return;
    }

    batal data;
    long totalPembatalan = 0;
    int baris = 9;
    int jumlahData = 0;

    // Header tabel
    gotoxy(35, 7);
    printf("===================================================================================");
    gotoxy(35, 8);
    printf("ID Tiket      Nama Penumpang         Rute                Tgl Batal    Harga Batal");
    gotoxy(35, 9);
    printf("===================================================================================");

    // Baca dan filter data berdasarkan bulan dan tahun
    while (fread(&data, sizeof(batal), 1, file) == 1) {
        int tglBulan, tglTahun, tglHari;

        // Parse tanggal booking (asumsi format DD/MM/YYYY atau DD-MM-YYYY)
        if (sscanf(data.tanggal_booking, "%d/%d/%d", &tglHari, &tglBulan, &tglTahun) == 3 ||
            sscanf(data.tanggal_booking, "%d-%d-%d", &tglHari, &tglBulan, &tglTahun) == 3) {

            // Cek apakah sesuai bulan dan tahun yang dipilih
            if (tglBulan == bulan && tglTahun == tahun) {
                if (baris < 35) { // Batasi tampilan agar tidak overflow
                    gotoxy(35, baris);
                    printf("%-13s %-22s %-19s %-12s %12ld",
                           data.id_tiket,
                           data.nama_penumpang,
                           data.rute_awal,
                           data.tanggal_booking,
                           data.hargaTbatal);
                    baris++;
                }

                // Hitung total
                totalPembatalan += data.hargaTbatal;
                jumlahData++;
            }
        }
    }

    fclose(file);

    // Tampilkan total
    gotoxy(35, baris + 1);
    printf("===================================================================================");
    gotoxy(35, baris + 2);
    printf("Total Pembatalan     : Rp %15ld", totalPembatalan);
    gotoxy(35, baris + 3);
    printf("Jumlah Tiket Dibatal : %d tiket", jumlahData);
    gotoxy(35, baris + 4);
    printf("===================================================================================");

    if (jumlahData == 0) {
        gotoxy(40, 10);
        printf("Tidak ada pembatalan pada bulan %02d/%d", bulan, tahun);
    }

    gotoxy(40, 38);
    printf("Tekan tombol apapun untuk kembali...");
    _getch();
}

//LAPORAN TAHUNAN
void laporanTahunan() {
    gotoxy(5, 5);
    printf("=== LAPORAN TAHUNAN ===\n");
    gotoxy(5, 7);
    printf("Pilih Tahun:\n");

    int tahun;
    gotoxy(5, 9);
    printf("Tahun: ");
    scanf("%d", &tahun);

    system("cls");
    gotoxy(5, 5);
    printf("=== LAPORAN TAHUNAN - %d ===\n", tahun);

    gotoxy(5, 7);
    printf("Menampilkan laporan transaksi tahun %d...\n", tahun);
    gotoxy(5, 20);
    printf("Tekan tombol apapun untuk kembali...");
}

#endif //PROJEK_LAPORAN_H