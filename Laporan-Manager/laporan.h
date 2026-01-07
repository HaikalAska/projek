void laporanBulanan() {
    int bulan, tahun;
    char pilihan;
    
    do {
        system("chcp 65001 > nul");
        fillBackground(0x90);
        bentukframe(2, 1, 30, 45);
        bentukframe(34, 1, 121, 10);
        bentukframe(3, 4, 27, 3);
        tampilanlogin("GAMBARASCI.txt", 60, 3);
        gotoxy(8, 5); printf("Kelompok 5");
        
        bentukframe(3, 29, 27, 10);
        gotoxy(5, 30); printf("=== MENU NAVIGASI ===");
        gotoxy(4, 32); printf("NAVIGASI [↑ ↓]");
        gotoxy(4, 34); printf("[ENTER] Pilih");
        gotoxy(4, 36); printf("[ESC] Keluar");
        
        // Input Bulan dan Tahun
        bentukframe(35, 12, 108, 8);
        gotoxy(70, 13); printf("=== LAPORAN BULANAN ===");
        gotoxy(37, 15); printf("Masukkan Bulan (1-12) : ");
        scanf("%d", &bulan);
        
        if (bulan < 1 || bulan > 12) {
            gotoxy(37, 17);
            printf("Bulan tidak valid! Tekan tombol apapun...");
            getch();
            continue;
        }
        
        gotoxy(37, 16); printf("Masukkan Tahun        : ");
        scanf("%d", &tahun);
        
        if (tahun < 2000 || tahun > 2100) {
            gotoxy(37, 17);
            printf("Tahun tidak valid! Tekan tombol apapun...");
            getch();
            continue;
        }
        
        // Nama bulan
        char* namaBulan[] = {"", "Januari", "Februari", "Maret", "April", "Mei", 
                             "Juni", "Juli", "Agustus", "September", "Oktober", 
                             "November", "Desember"};
        
        // ========== LAPORAN TIKET TERJUAL ==========
        system("cls");
        fillBackground(0x90);
        bentukframe(2, 1, 121, 45);
        
        gotoxy(50, 3);
        printf("LAPORAN TIKET TERJUAL - %s %d", namaBulan[bulan], tahun);
        
        FILE *fp_tiket = fopen("tiket.dat", "rb");
        tiket data_tiket;
        long totalPenjualan = 0;
        int jumlahTiket = 0;
        int baris = 7;
        
        // Header tabel tiket
        gotoxy(5, 5);
        printf("==============================================================================================");
        gotoxy(5, 6);
        printf("ID Tiket      Nama Penumpang         Rute                Tgl Berangkat  Harga");
        gotoxy(5, 7);
        printf("==============================================================================================");
        
        if (fp_tiket != NULL) {
            while (fread(&data_tiket, sizeof(tiket), 1, fp_tiket) == 1) {
                int tglBulan, tglTahun, tglHari;
                
                // Parse tanggal berangkat (format DD/MM/YYYY atau DD-MM-YYYY)
                if (sscanf(data_tiket.tanggal_berangkat, "%d/%d/%d", &tglHari, &tglBulan, &tglTahun) == 3 ||
                    sscanf(data_tiket.tanggal_berangkat, "%d-%d-%d", &tglHari, &tglBulan, &tglTahun) == 3) {
                    
                    // Filter berdasarkan bulan dan tahun
                    if (tglBulan == bulan && tglTahun == tahun) {
                        if (baris < 25) { // Batasi tampilan
                            gotoxy(5, baris);
                            printf("%-13s %-22s %-19s %-14s %12ld",
                                   data_tiket.id_tiket,
                                   data_tiket.nama_penumpang,
                                   data_tiket.rute_awal,
                                   data_tiket.tanggal_berangkat,
                                   data_tiket.harga);
                            baris++;
                        }
                        
                        totalPenjualan += data_tiket.harga;
                        jumlahTiket++;
                    }
                }
            }
            fclose(fp_tiket);
        }
        
        gotoxy(5, baris);
        printf("==============================================================================================");
        gotoxy(5, baris + 1);
        printf("Total Tiket Terjual   : %d tiket", jumlahTiket);
        gotoxy(5, baris + 2);
        printf("Total Penjualan       : Rp %ld", totalPenjualan);
        
        // ========== LAPORAN PEMBATALAN TIKET ==========
        baris += 5;
        gotoxy(50, baris);
        printf("LAPORAN PEMBATALAN TIKET - %s %d", namaBulan[bulan], tahun);
        baris += 2;
        
        FILE *fp_batal = fopen("pembatalan.dat", "rb");
        DataPembatalan data_batal;
        long totalPembatalan = 0;
        int jumlahBatal = 0;
        int barisBatal = baris + 2;
        
        // Header tabel pembatalan
        gotoxy(5, baris);
        printf("==============================================================================================");
        gotoxy(5, baris + 1);
        printf("ID Tiket      Nama Penumpang         Rute                Tgl Batal      Harga Refund");
        gotoxy(5, baris + 2);
        printf("==============================================================================================");
        
        if (fp_batal != NULL) {
            while (fread(&data_batal, sizeof(DataPembatalan), 1, fp_batal) == 1) {
                int tglBulan, tglTahun, tglHari;
                
                // Parse tanggal booking (format DD/MM/YYYY atau DD-MM-YYYY)
                if (sscanf(data_batal.tanggal_booking, "%d/%d/%d", &tglHari, &tglBulan, &tglTahun) == 3 ||
                    sscanf(data_batal.tanggal_booking, "%d-%d-%d", &tglHari, &tglBulan, &tglTahun) == 3) {
                    
                    // Filter berdasarkan bulan dan tahun
                    if (tglBulan == bulan && tglTahun == tahun) {
                        if (barisBatal < 42) { // Batasi tampilan
                            gotoxy(5, barisBatal);
                            printf("%-13s %-22s %-14s %12ld",
                                   data_batal.id_tiket,
                                   data_batal.nama_penumpang,
                                   data_batal.tanggal_booking,
                                   data_batal.hargaTbatal);
                            barisBatal++;
                        }
                        
                        totalPembatalan += data_batal.hargaTbatal;
                        jumlahBatal++;
                    }
                }
            }
            fclose(fp_batal);
        }
        
        gotoxy(5, barisBatal);
        printf("==============================================================================================");
        gotoxy(5, barisBatal + 1);
        printf("Total Pembatalan      : %d tiket", jumlahBatal);
        gotoxy(5, barisBatal + 2);
        printf("Total Refund          : Rp %ld", totalPembatalan);
        
        // ========== RINGKASAN ==========
        long pendapatanBersih = totalPenjualan - totalPembatalan;
        gotoxy(5, barisBatal + 4);
        printf("==============================================================================================");
        gotoxy(5, barisBatal + 5);
        printf("PENDAPATAN BERSIH     : Rp %ld", pendapatanBersih);
        gotoxy(5, barisBatal + 6);
        printf("==============================================================================================");
        
        gotoxy(5, barisBatal + 8);
        printf("Tekan [Y] untuk laporan bulan lain, [ESC] untuk kembali...");
        
        pilihan = getch();
        
        if (pilihan == 27) { // ESC
            break;
        }
        
    } while (pilihan == 'Y' || pilihan == 'y');
}