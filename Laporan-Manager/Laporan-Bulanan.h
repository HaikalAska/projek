#ifndef PROJEK_LAPORAN_BULANAN_H
#define PROJEK_LAPORAN_BULANAN_H
#include "../FrameTabel.h"



void Laporan();
void laporanBulanan() {
    FILE *fp;
    tiket all_data[1000];
    tiket filtered_data[1000];
    int total_all = 0;
    int total_filtered = 0;
    long total_pendapatan = 0;

    char bulan[3];
    int tahun;

    int startX = 33;
    int startY = 12;

    // ===== LEBAR KOLOM =====
    int wNo = 3, wID = 8, wNama = 20, wTelp = 13;
    int wRute = 17, wTgl = 12, wJam = 5, wStatus = 7, wHarga = 12;

    // Baca semua data dulu
    fp = fopen("tiket.dat", "rb");
    if (!fp) {
        bentukframe(34, 11, 80, 15);
        gotoxy(startX, startY);
        printf("File tiket.dat tidak ditemukan!");
        getch();
        return;
    }

    while (fread(&all_data[total_all], sizeof(tiket), 1, fp) == 1) {
        if (total_all < 1000) total_all++;
    }
    fclose(fp);

    if (total_all == 0) {
        bentukframe(34, 11, 80, 15);
        gotoxy(startX, startY);
        printf("Belum ada data tiket!");
        getch();
    }


    bentukframe(40, 27, 80, 18);
    gotoxy(69, 28);
    printf(" LAPORAN BULANAN ");


    //INPUT
    inputBulan(bulan, 41,30);
    TahunJadwal(&tahun, 41,31);



    // Array nama bulan
    char namaBulan[12][20] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni",
        "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };



    // Filter data berdasarkan bulan
    for (int i = 0; i < total_all; i++) {
        // Ambil bulan dari tanggal
        char bulan_tiket[3];
        bulan_tiket[0] = all_data[i].tanggal_berangkat[3];
        bulan_tiket[1] = all_data[i].tanggal_berangkat[4];
        bulan_tiket[2] = '\0';

        // Ambil tahun dari tanggal
        char tahun_tiket[5];
        tahun_tiket[0] = all_data[i].tanggal_berangkat[6];
        tahun_tiket[1] = all_data[i].tanggal_berangkat[7];
        tahun_tiket[2] = all_data[i].tanggal_berangkat[8];
        tahun_tiket[3] = all_data[i].tanggal_berangkat[9];
        tahun_tiket[4] = '\0';

        int thn = atoi(tahun_tiket);

        // Cek apakah sesuai bulan dan tahun
        if (strcmp(bulan_tiket, bulan) == 0 && thn == tahun) {
            filtered_data[total_filtered++] = all_data[i];
            total_pendapatan += all_data[i].harga;
        }
    }

    if (total_filtered == 0) {
        clearArea(startX, startY, 80, 20);
        gotoxy(startX, startY);
        printf("Tidak ada data untuk bulan tersebut!");
        getch();

    }


    int idx = atoi(bulan) - 1;


    clearArea(35,32,90,13);
    clearArea(3,8,27,18);
    // Tampilkan tabel
    int rowsPerPage = 10;
    int total_pages = (total_filtered + rowsPerPage - 1) / rowsPerPage;
    int current_page = 1;
    char key;

    int totalWidth =
        1 + (wNo+2)+(wID+2)+(wNama+2)+(wTelp+2)+
        (wRute+2)+(wTgl+2)+(wJam+2)+(wStatus+2)+(wHarga+3);

    char garis[300];
    memset(garis, '-', totalWidth);
    garis[totalWidth] = '\0';

    do {


        int start = (current_page - 1) * rowsPerPage;
        int end = start + rowsPerPage;
        if (end > total_filtered) end = total_filtered;

        clearArea(startX, startY + 1, totalWidth, 20);

        gotoxy(80, 13);
        printf("=== LAPORAN TIKET %s %d ===", namaBulan[idx], tahun);

        int row = startY + 2;

        // ===== HEADER TABEL =====
        gotoxy(startX, row++); printf("%s", garis);

        gotoxy(startX, row++);
        printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
               wNo+1,"No",
               wID+1,"ID Tiket",
               wNama+1,"Nama",
               wTelp+1,"Telepon",
               wRute+1,"Rute",
               wTgl+1,"Tanggal",
               wJam+1,"Jam",
               wStatus+1,"Status",
               wHarga+2,"Harga");

        gotoxy(startX, row++); printf("%s", garis);

        // ===== ISI DATA =====
        for (int i = start; i < end; i++) {
            char rute[60];
            sprintf(rute, "%s-%s",
                    filtered_data[i].rute_awal,
                    filtered_data[i].tujuan);

            gotoxy(startX, row++);

            // cetak kolom sebelum harga
            printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
                   wNo+1, i+1,
                   wID+1, filtered_data[i].id_tiket,
                   wNama+1, filtered_data[i].nama_penumpang,
                   wTelp+1, filtered_data[i].notlpn,
                   wRute+1, rute,
                   wTgl+1, filtered_data[i].tanggal_berangkat,
                   wJam+1, filtered_data[i].jam_berangkat,
                   wStatus+1, filtered_data[i].status);

            // cetak harga dengan format rupiah
            printf(" ");
            tampilanhargatiket(filtered_data[i].harga);

            // rapikan spasi kolom harga + tutup tabel
            printf("%*s|", wHarga - 13, "");
        }

        gotoxy(startX, row++); printf("%s", garis);

        // Total pendapatan
        gotoxy(startX, row + 1);
        printf("Total Tiket   : %d tiket", total_filtered);
        gotoxy(startX, row + 2);
        printf("Total Pendapatan : ");
        tampilanhargatiket(total_pendapatan);

        // ===== NAVIGASI =====
        bentukframe(3, 11, 27, 12);
        gotoxy(6, 13); printf("[SPASI] Lanjut");
        gotoxy(6, 15); printf("[BACKSPACE] Kembali");
        gotoxy(6, 17); printf("[ENTER] Keluar");
        gotoxy(6, 19); printf("Halaman: %d/%d", current_page, total_pages);
        gotoxy(6, 21); printf("Total  : %d data", total_filtered);



        key = getch();

        if (key == 13) {
            Laporan();
            break;
        }
        else if (key == ' ' && current_page < total_pages)
            current_page++;
        else if (key == 8 && current_page > 1)
            current_page--;

    } while (1);
    system("cls");
}




#endif //PROJEK_LAPORAN_BULANAN_H