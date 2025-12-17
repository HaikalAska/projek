//
// Created by ASUS on 12/16/2025.
//

#ifndef PROJEK_UPDATEJADWAL_H
#define PROJEK_UPDATEJADWAL_H

void updatejadwal() {
    FILE *fp, *temp;
    jadwal j;
    int targetNo = 0, currentNo = 1, found = 0;
    char strNo[10];
    int idx = 0;

    // ================= INPUT NOMOR URUT =================
    gotoxy(3, 25);
    printf("Pilih No Urut Jadwal: ");

    while (1) {
        char ch = _getch();
        if (ch == 27) return;
        if (ch == 13) {
            strNo[idx] = '\0';
            targetNo = atoi(strNo);
            break;
        }
        if (ch == 8 && idx > 0) {
            idx--;
            printf("\b \b");
        }
        if (ch >= '0' && ch <= '9' && idx < 9) {
            strNo[idx++] = ch;
            printf("%c", ch);
        }
    }

    fp   = fopen("jadwal.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (fp == NULL || temp == NULL) {
        return;
    }


    // ================= PROSES UPDATE =================
    while (fread(&j, sizeof(jadwal), 1, fp)) {

        if (currentNo == targetNo) {
            found = 1;

            // ========= DATA LAMA =========
            bentukframe(35, 27, 50, 14);
            gotoxy(55, 28); printf("DATA LAMA");

            gotoxy(37,30); printf("Tanggal      : %s", j.tanggal);
            gotoxy(37,31); printf("Kota Asal    : %s", j.kotaAsal);
            gotoxy(37,32); printf("Kota Tujuan  : %s", j.kotaTujuan);
            gotoxy(37,33); printf("Jam Berangkat: %s", j.jamBerangkat);
            gotoxy(37,34); printf("Harga        : %.0f", j.harga);
            gotoxy(37,35); printf("Kategori     : %s", j.kategori);
            gotoxy(37,36); printf("Armada       : %s", j.armada);

            // ========= DATA BARU =========
            bentukframe(90, 27, 60, 16);
            gotoxy(115, 28); printf("DATA BARU");

            // TANGGAL
            gotoxy(92,30); printf("Tanggal      : ");
            inputTanggals(j.tanggal, 108, 30);

            // PILIH RUTE
            Rute r;
            gotoxy(92,31); printf("Pilih Rute   : ");
            _getch();
            if (!pilihRuteDanTampil(&r)) goto batal;

            // TAMPILKAN HASIL RUTE
            char hargaStr[25];
            formatHarga((int)r.harga, hargaStr);

            gotoxy(92,32); printf("Kota Awal    : %-20s", r.kotaAsal);
            gotoxy(92,33); printf("Kota Tujuan  : %-20s", r.kotaTujuan);
            gotoxy(92,34); printf("Jam Berangkat: %-10s", r.jamBerangkat);
            gotoxy(92,35); printf("Harga        : %-15s", hargaStr);

            // SIMPAN DARI RUTE
            strcpy(j.kotaAsal, r.kotaAsal);
            strcpy(j.kotaTujuan, r.kotaTujuan);
            strcpy(j.jamBerangkat, r.jamBerangkat);
            j.harga = r.harga;

            // KATEGORI
            gotoxy(92,36); printf("Kategori     : ");
            inputKategori(j.kategori, 107, 36);

            // ARMADA
            gotoxy(92,37); printf("Nama Armada  : ");
            gotoxy(107,37);
            scanf(" %[^\n]", j.armada);

            fwrite(&j, sizeof(jadwal), 1, temp);
        }
        else {
            fwrite(&j, sizeof(jadwal), 1, temp);
        }

        currentNo++;
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("jadwal.dat");
        rename("temp.dat", "jadwal.dat");
        gotoxy(40, 45); printf("Jadwal berhasil diperbarui!");
    } else {
        remove("temp.dat");
        gotoxy(40, 45); printf("Nomor jadwal tidak ditemukan!");
    }

    getch();
    return;

batal:
    fclose(fp);
    fclose(temp);
    remove("temp.dat");
}


#endif //PROJEK_UPDATEJADWAL_H