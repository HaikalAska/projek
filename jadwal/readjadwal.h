#ifndef PROJEK_READJADWAL_H
#define PROJEK_READJADWAL_H

#include "createjadwal.h"

void buatdummyjadwal() {
    FILE *fp;
    jadwal data;
    int max_data = 50;

    char *tanggal[] = {
        "01/01/2025","02/01/2025","03/01/2025","04/01/2025","05/01/2025",
        "06/01/2025","07/01/2025","08/01/2025","09/01/2025","10/01/2025"
    };

    char *jam[] = {
        "06:00","07:30","09:00","10:30","12:00",
        "13:30","15:00","16:30","18:00","20:00"
    };

    char *kota_asal[] = {
        "Jakarta","Bekasi","Depok","Bogor","Bandung"
    };

    char *kota_tujuan[] = {
        "Cirebon","Semarang","Yogyakarta","Solo","Surabaya"
    };

    char *armada[] = {
        "Agramas","Rosalia Indah","Blue Star","Blue Bird"
    };

    char *kategori[] = {
        "Ekonomi","Bisnis", "eksekutif"
    };

    int harga[] = {
        100000,120000,150000,175000,200000
    };

    int n_tgl = sizeof(tanggal) / sizeof(tanggal[0]);
    int n_jam = sizeof(jam) / sizeof(jam[0]);
    int n_asal = sizeof(kota_asal) / sizeof(kota_asal[0]);
    int n_tujuan = sizeof(kota_tujuan) / sizeof(kota_tujuan[0]);
    int n_armada = sizeof(armada) / sizeof(armada[0]);
    int n_kategori = sizeof(kategori) / sizeof(kategori[0]);
    int n_harga = sizeof(harga) / sizeof(harga[0]);

    fp = fopen("jadwal.dat", "wb");
    if (fp == NULL) {
        printf("ERROR: Gagal membuat file jadwal.dat");
        getch();
        return;
    }

    // printf("       MEMBUAT DATA DUMMY JADWAL\n");

    for (int i = 0; i < max_data; i++) {

        strcpy(data.tanggal, tanggal[i % n_tgl]);
        strcpy(data.jamBerangkat, jam[i % n_jam]);
        strcpy(data.kotaAsal, kota_asal[i % n_asal]);
        strcpy(data.kotaTujuan, kota_tujuan[i % n_tujuan]);
        strcpy(data.nama_armada, armada[i % n_armada]);
        strcpy(data.kategori, kategori[i % n_kategori]);

        data.harga = harga[i % n_harga] + (i * 5000);

        fwrite(&data, sizeof(jadwal), 1, fp);
    }

    fclose(fp);

    // printf("\n[✓] Berhasil membuat %d data dummy jadwal", max_data);
    // printf("\nTekan tombol apapun untuk kembali...");
    getch();
}



//=====================================//
//Fungsi untuk menampilkan tabel jadwal//
//=====================================//
void bacajadwal() {

    FILE *fp;
    jadwal all_jadwal[1000];
    int total = 0;

    // buatdummyjadwal();

    int startX = 37;
    int startY = 12;

    // Lebar kolom (disesuaikan)
    int wNo = 3;
    int wTgl = 12;
    int wJam = 7;
    int wAsal = 7;
    int wTujuan = 9;
    int wArmada = 20;
    int wKategori = 12;
    int wHarga = 10;
    int wtiba = 7;

    int current_page = 1;
    int total_pages = 1;
    char key;

    bentukframe(34, 11, 121, 35);

    fp = fopen("jadwal.dat", "rb");
    if (!fp) {

        gotoxy(startX, startY);
        printf("File jadwal.dat tidak ditemukan!");
        getch();
        return;
    }

    while (fread(&all_jadwal[total], sizeof(jadwal), 1, fp) == 1) {
        if (total < 1000) total++;
    }
    fclose(fp);

    if (total > 0)
        total_pages = (total + 3 - 1) / 3;

    int totalWidth = 1 + (wNo+2) + (wTgl+2) + (wJam+2) + (wAsal+2) +
                     (wTujuan+2) + (wArmada+2) + (wKategori+2) + (wHarga+2) + (wtiba +2);

    char line[200];
    memset(line, '-', totalWidth);
    line[totalWidth] = '\0';

    do {
        clearArea(startX, startY, totalWidth + 2, MAX_ROWS_PER_PAGE + 2);

        gotoxy(80, 13);
        printf("=== DAFTAR JADWAL ===");

        int row = startY + 2;

        gotoxy(startX, row++);
        printf("%s", line);

        gotoxy(startX, row++);
        printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
               wNo+1,"No",
               wTgl+1,"Tanggal",
               wJam+1,"Berangkat",
               wtiba +1,"Jam Tiba",
               wAsal+1,"Kota Asal",
               wTujuan+1,"Kota Tujuan",
               wArmada+1,"Armada",
               wKategori+1,"Kategori",
               wHarga+1,"Harga");

        gotoxy(startX, row++);
        printf("%s", line);

        int start = (current_page - 1) * 3;
        int end = start + 3;
        if (end > total) end = total;

        for (int i = start; i < end; i++) {

            char harga[25];
            // formatHarga(atoi(all_jadwal[i].harga), harga); // jika harga string
            formatHarga(all_jadwal[i].harga, harga);

            gotoxy(startX, row++);
            printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
                   wNo+1, i+1,
                   wTgl+1, all_jadwal[i].tanggal,
                   wJam+1, all_jadwal[i].jamBerangkat,
                   wAsal+1, all_jadwal[i].jamTiba,
                   wtiba+1, all_jadwal[i].kotaAsal,
                   wTujuan+1, all_jadwal[i].kotaTujuan,
                   wArmada+1, all_jadwal[i].nama_armada,
                   wKategori+1, all_jadwal[i].kategori,
                   wHarga+1, harga);
        }

        gotoxy(startX, row++);
        printf("%s", line);

        bentukframe(3, 11, 27, 12);
        gotoxy(6, 13); printf("[SPASI] Lanjut");
        gotoxy(6, 15); printf("[BACKSPACE] Kembali");
        gotoxy(6, 17); printf("[ENTER] Keluar");
        gotoxy(6, 19); printf("Halaman: %d/%d", current_page, total_pages);
        gotoxy(6, 21); printf("Total  : %d data", total);

        key = getch();

        if (key == ' ' && current_page < total_pages)
            current_page++;
        else if (key == 8 && current_page > 1)
            current_page--;

    } while (key != 13);
}

#endif // PROJEK_READJADWAL_H