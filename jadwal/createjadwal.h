#ifndef PROJEK_CREATEJADWAL_H
#define PROJEK_CREATEJADWAL_H

#include "../FrameTabel.h"
#include "../rute/createrute.h"
#include <conio.h>

typedef struct {
    char id[10];
    int rute;
    int kendaraan;
    char tanggal[50];

    long harga;
    char jamBerangkat[50];
    char kotaAsal[50];
    char kotaTujuan[50];
    char nama_armada[50];
    char kategori[50];
} jadwal;

void liatjadwal() {

    FILE *fp;
    jadwal all_jadwal[1000];
    int total = 0;

    int startX = 37;
    int startY = 12;

    int wNo = 3;
    int wTgl = 12;
    int wJam = 7;
    int wAsal = 12;
    int wTujuan = 12;
    int wArmada = 15;
    int wKategori = 12;
    int wHarga = 15;

    int current_page = 1;
    int total_pages = 1;

    // bentukframe(34, 11, 121, 35);

    fp = fopen("jadwal.dat", "rb");
    if (!fp) {
        gotoxy(startX, startY);
        printf("File jadwal.dat tidak ditemukan!");
        return;
    }

    while (fread(&all_jadwal[total], sizeof(jadwal), 1, fp) == 1) {
        if (total < 1000) total++;
    }
    fclose(fp);

    if (total > 0)
        total_pages = (total + MAX_ROWS_PER_PAGE - 1) / MAX_ROWS_PER_PAGE;

    int totalWidth = 1 + (wNo+2) + (wTgl+2) + (wJam+2) + (wAsal+2) +
                     (wTujuan+2) + (wArmada+2) + (wKategori+2) + (wHarga+2);

    char line[200];
    memset(line, '-', totalWidth);
    line[totalWidth] = '\0';

    // ===== TAMPILKAN SEKALI SAJA =====
    clearArea(startX, startY,115, 13);

    gotoxy(80, 13);
    printf("=== DAFTAR JADWAL ===");

    int row = startY + 2;

    gotoxy(startX, row++);
    printf("%s", line);

    gotoxy(startX, row++);
    printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
           wNo+1,"No",
           wTgl+1,"Tanggal",
           wJam+1,"Jam",
           wAsal+1,"Kota Asal",
           wTujuan+1,"Kota Tujuan",
           wArmada+1,"Armada",
           wKategori+1,"Kategori",
           wHarga+1,"Harga");

    gotoxy(startX, row++);
    printf("%s", line);

    int start = 0;
    int end = total;
    if (end > MAX_ROWS_PER_PAGE) end = MAX_ROWS_PER_PAGE;

    for (int i = start; i < end; i++) {
        char harga[25];
        formatHarga(all_jadwal[i].harga, harga);

        gotoxy(startX, row++);
        printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
               wNo+1, i+1,
               wTgl+1, all_jadwal[i].tanggal,
               wJam+1, all_jadwal[i].jamBerangkat,
               wAsal+1, all_jadwal[i].kotaAsal,
               wTujuan+1, all_jadwal[i].kotaTujuan,
               wArmada+1, all_jadwal[i].nama_armada,
               wKategori+1, all_jadwal[i].kategori,
               wHarga+1, harga);
    }

    gotoxy(startX, row++);
    printf("%s", line);
}


//==============================================================//
//Fungsi untuk menampilkan tabel kendaraan untuk pilih kendaraan//
//==============================================================//
int liatkendaraan() {

    FILE *fp;
    Kendaraan all[1000];
    int total = 0;

    int startX = 37;
    int startY = 14;

    int wNo = 3, wKat = 15, wKap = 10, wFas = 25, wNama = 18;
    int current_page = 1, total_pages = 1;
    char key;

    fp = fopen("kendaraan.dat", "rb");
    if (!fp) return -1;

    while (fread(&all[total], sizeof(Kendaraan), 1, fp) == 1) {
        total++;
    }
    fclose(fp);

    if (total == 0) return -1;

    total_pages = (total + MAX_ROWS_PER_PAGE - 1) / MAX_ROWS_PER_PAGE;

    int width = 1+(wNo+2)+(wKat+2)+(wKap+2)+(wFas+2)+(wNama+2);
    char line[200];
    memset(line, '-', width);
    line[width] = '\0';

    do {
        clearArea(startX, startY, 115, 13);

        gotoxy(80, 13);
        printf("=== DAFTAR KENDARAAN ===");

        int row = startY;

        gotoxy(startX, row++); printf("%s", line);
        gotoxy(startX, row++);
        printf("|%-*s|%-*s|%-*s|%-*s|%-*s|",
               wNo+1,"No", wKat+1,"Kategori",
               wKap+1,"Kapasitas", wFas+1,"Fasilitas",
               wNama+1,"Armada");
        gotoxy(startX, row++); printf("%s", line);

        int s = (current_page-1)*MAX_ROWS_PER_PAGE;
        int e = s + MAX_ROWS_PER_PAGE;
        if (e > total) e = total;

        for (int i=s;i<e;i++) {
            gotoxy(startX, row++);
            printf("|%-*d|%-*s|%-*s|%-*s|%-*s|",
                   wNo+1,i+1,
                   wKat+1,all[i].kategori,
                   wKap+1,all[i].kapasitas,
                   wFas+1,all[i].fasilitas,
                   wNama+1,all[i].nama_armada);
        }

        gotoxy(startX, row++); printf("%s", line);
        gotoxy(startX, row+1);
        // printf("[SPASI] Next  [BACKSPACE] Prev  [ENTER] Pilih  [ESC] Batal");

        key = _getch();

        if (key==' ' && current_page<total_pages) current_page++;
        else if (key==8 && current_page>1) current_page--;
        else if (key==27) return -1;

    } while (key!=13);

    // clearArea(startX, startY, width+2, MAX_ROWS_PER_PAGE+6);
    return 1;
}


//====================================================//
//Fungsi untuk menampilkan tabel rute untuk pilih rute//
//====================================================//
int liatrute() {

    FILE *fp;
    Rute all_rute[1000];
    int total_rute = 0;

    int startX = 37;
    int startY = 14;

    int wNo = 3, wAsal = 18, wTujuan = 18;
    int wHarga = 18, wBerangkat = 12, wTiba = 12;

    int current_page = 1;
    int total_pages = 1;
    char key;

    // ===== BUKA FILE =====
    fp = fopen("rute.dat", "rb");
    if (!fp) return -1;

    while (fread(&all_rute[total_rute], sizeof(Rute), 1, fp) == 1) {
        total_rute++;
    }
    fclose(fp);

    if (total_rute == 0) return -1;

    total_pages = (total_rute + MAX_ROWS_PER_PAGE - 1) / MAX_ROWS_PER_PAGE;

    int totalWidth = 1 + (wNo+2) + (wAsal+2) + (wTujuan+2)
                   + (wHarga+2) + (wBerangkat+2) + (wTiba+2);

    char line[200];
    memset(line, '-', totalWidth);
    line[totalWidth] = '\0';

    do {
        clearArea(startX, startY, 115, 13);

        gotoxy(80, 13);
        printf("=== DAFTAR RUTE ===");

        int row = startY;

        gotoxy(startX, row++);
        printf("%s", line);

        gotoxy(startX, row++);
        printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
               wNo+1, "No",
               wAsal+1, "Kota Asal",
               wTujuan+1, "Kota Tujuan",
               wHarga+1, "Harga",
               wBerangkat+1, "Berangkat",
               wTiba+1, "Tiba");

        gotoxy(startX, row++);
        printf("%s", line);

        int start = (current_page - 1) * MAX_ROWS_PER_PAGE;
        int end = start + MAX_ROWS_PER_PAGE;
        if (end > total_rute) end = total_rute;

        for (int i = start; i < end; i++) {
            char hargaStr[25];
            formatHarga((int)all_rute[i].harga, hargaStr);

            gotoxy(startX, row++);
            printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*s|",
                   wNo+1, i + 1,
                   wAsal+1, all_rute[i].kotaAsal,
                   wTujuan+1, all_rute[i].kotaTujuan,
                   wHarga+1, hargaStr,
                   wBerangkat+1, all_rute[i].jamBerangkat,
                   wTiba+1, all_rute[i].jamTiba);
        }

        gotoxy(startX, row++);
        printf("%s", line);

        gotoxy(startX, row + 1);
        // printf("[SPASI] Next  [BACKSPACE] Prev  [ENTER] Pilih  [ESC] Batal");

        key = _getch();

        if (key == ' ' && current_page < total_pages) current_page++;
        else if (key == 8 && current_page > 1) current_page--;
        else if (key == 27) return -1;

    } while (key != 13);

    return 1;
}

//======================================//
//Fungsi untuk input tanggal pada jadwal//
//======================================//
int inputtanggaljadwal(char *tanggal) {
    int idx = 0;
    char ch;
    int selesai = 0; // penanda sudah input tahun

    while (1) {
        ch = _getch();

        // ESC
        if (ch == 27) {
            tanggal[0] = '\0';
            return -1;
        }

        // ENTER (hanya boleh kalau sudah lengkap)
        if (ch == 13 && selesai) {
            tanggal[idx] = '\0';
            return 1;
        }

        // BACKSPACE
        if (ch == 8 && idx > 0) {
            if (tanggal[idx - 1] == '/') {
                printf("\b \b");
                idx--;
            }
            printf("\b \b");
            idx--;
            tanggal[idx] = '\0';
            selesai = 0;   // batal selesai kalau dihapus
            continue;
        }

        // ===== DIGIT 1 (hari puluhan) =====
        if (idx == 0 && ch >= '0' && ch <= '3') {
            tanggal[idx++] = ch;
            printf("%c", ch);
        }

        // ===== DIGIT 2 (hari satuan) =====
        else if (idx == 1) {
            char d1 = tanggal[0];
            if (
                (d1 == '0' && ch >= '1' && ch <= '9') ||
                ((d1 == '1' || d1 == '2') && ch >= '0' && ch <= '9') ||
                (d1 == '3' && ch >= '0' && ch <= '1')
            ) {
                tanggal[idx++] = ch;
                printf("%c", ch);
                tanggal[idx++] = '/';
                printf("/");
            }
        }

        // ===== DIGIT 3 (bulan puluhan) =====
        else if (idx == 3 && ch >= '0' && ch <= '1') {
            tanggal[idx++] = ch;
            printf("%c", ch);
        }

        // ===== DIGIT 4 (bulan satuan) =====
        else if (idx == 4) {
            char m1 = tanggal[3];
            if (
                (m1 == '0' && ch >= '1' && ch <= '9') ||
                (m1 == '1' && ch >= '0' && ch <= '2')
            ) {
                tanggal[idx++] = ch;
                printf("%c", ch);
                tanggal[idx++] = '/';
                printf("/");
            }
        }

        // ===== DIGIT 5 (tahun selector) =====
        else if (idx == 6 && (ch == '5' || ch == '6')) {
            if (ch == '5') {
                strcpy(&tanggal[idx], "2025");
                printf("2025");
            } else {
                strcpy(&tanggal[idx], "2026");
                printf("2026");
            }
            idx += 4;
            selesai = 1;
        }
    }
}

//==================================//
//Format tampilan harga untuk jadwal//
//==================================//
void tampilanhargajadwal(long harga) {
    if (harga >= 1000000) {
        // 7 digit atau lebih → x.xxx.xxx
        printf("Rp%ld.%03ld.%03ld,00",
               harga / 1000000,
               (harga / 1000) % 1000,
               harga % 1000);
    }
    else if (harga >= 100000) {
        // 6 digit → xxx.xxx
        printf("Rp%ld.%03ld,00",
               harga / 1000,
               harga % 1000);
    }
    else if (harga >= 10000) {
        // 5 digit → xx.xxx
        printf("Rp%ld.%03ld,00",
               harga / 1000,
               harga % 1000);
    }
    else {
        // cadangan (di bawah 5 digit)
        printf("Rp%ld,00", harga);
    }
}

//====================================================================//
//Fungsi untuk mengambil data dari kendaraan.dat untuk pilih kendaraan//
//====================================================================//
int pilihkendaraan(Kendaraan *hasil) {

    if (liatkendaraan() == -1)
        return -1;

    FILE *fp = fopen("kendaraan.dat", "rb");
    if (!fp) return -1;

    Kendaraan list[100];
    int total = 0;

    while (fread(&list[total], sizeof(Kendaraan), 1, fp)) {
        total++;
    }
    fclose(fp);

    if (total == 0) return -1;

    int x = 37, y = 33;

    gotoxy(x, y);
    printf("Pilih Kendaraan : ");

    char ch, input[4] = "";
    int idx = 0, pilihan = 0;

    while (1) {
        ch = _getch();

        // ===== ESC =====
        if (ch == 27) {
            return -1;
        }

        // ===== ENTER =====
            if (ch == 13) {
                 pilihan = atoi(input);

            if (pilihan >= 1 && pilihan <= total) {
                *hasil = list[pilihan - 1];
                return 1;
            } else {
                // tampilkan pesan error
                gotoxy(55, 33);
                printf("Kendaraan tidak ditemukan!");

                Sleep(1000); // 1.5 detik
                clearArea(55,33,26,1);

                // hapus pesan error & reset input
                gotoxy(x, y);
                printf("Pilih Kendaraan : ");

                idx = 0;
                input[0] = '\0';
            }
            continue;
        }

        // ===== BACKSPACE =====
        if (ch == 8 && idx > 0) {
            idx--;
            input[idx] = '\0';
            printf("\b \b");
            continue;
        }

        // ===== ANGKA SAJA =====
        if (ch >= '0' && ch <= '9' && idx < 3) {
            input[idx++] = ch;
            input[idx] = '\0';
            printf("%c", ch);
        }
    }
}

//==========================================================//
//Fungsi untuk mengambil data dari rute.dat untuk pilih rute//
//==========================================================//
int pilihrute(Rute *hasil) {

if (liatrute() == -1)
        return -1;

    FILE *fp = fopen("rute.dat", "rb");
    if (!fp) return 0;

    Rute daftar[100];
    int total = 0;

    while (fread(&daftar[total], sizeof(Rute), 1, fp)) {
        total++;
    }
    fclose(fp);

    int x = 37, y = 29;

    gotoxy(x, y);
    printf("Pilih rute      : ");

    char ch, input[4] = "";
    int idx = 0, pilihan = 0;

    while (1) {
        ch = _getch();

        // ===== ESC =====
        if (ch == 27) {
            return -1;
        }

        // ===== ENTER =====
        if (ch == 13) {
            pilihan = atoi(input);

            if (pilihan >= 1 && pilihan <= total) {
                *hasil = daftar[pilihan - 1];
                return pilihan;
            } else {
                // tampilkan pesan error
                gotoxy(55, 29);
                printf("Rute tidak ditemukan!");

                Sleep(1000); // 1.5 detik
                clearArea(55,29,22,1);
                // hapus pesan error
                gotoxy(x, y);
                printf("Pilih rute      : ");

                // reset input
                idx = 0;
                input[0] = '\0';
            }
            continue;
        }

        // ===== BACKSPACE =====
        if (ch == 8 && idx > 0) {
            idx--;
            input[idx] = '\0';
            printf("\b \b");
            continue;
        }

        // ===== ANGKA SAJA =====
        if (ch >= '0' && ch <= '9' && idx < 3) {
            input[idx++] = ch;
            input[idx] = '\0';
            printf("%c", ch);
        }
    }
}

//================================//
//Fungsi untuk membuat id otomatis//
//================================//
void jadwalid(char *id) {
    FILE *fp = fopen("jadwal.dat", "rb");
    jadwal j;
    int lastID = 0;

    if (fp) {
        while (fread(&j, sizeof(jadwal), 1, fp)) {
            sscanf(j.id, "JD%d", &lastID);
        }
        fclose(fp);
    }

    sprintf(id, "JD%03d", lastID + 1);
}

//===========================//
//Fungsi untuk membuat jadwal//
//===========================//
void buatjadwal() {
    char x;

    do {
        bentukframe(36,27,108,16);
        gotoxy(80,27); printf("=== BUAT JADWAL ===");

        FILE *fp = fopen("jadwal.dat", "ab");
        if (!fp) {
            gotoxy(37,36);
            printf("Gagal membuka file!");
            getch();
            return;
        }

        jadwal j;

        // ID otomatis
        jadwalid(j.id);
        gotoxy(37,28);
        printf("ID Jadwal       : %s", j.id);

        Rute r;
        int hasil = pilihrute(&r);

        if (hasil == -1) {
            clearArea(35,28,80,25);
            return;
        }

        j.rute = hasil;

        gotoxy(37,29);
        printf("Kota Asal       : %s", r.kotaAsal);

        gotoxy(37,30);
        printf("Kota Tujuan     : %s", r.kotaTujuan);

        gotoxy(37,31);
        printf("Jam Berangkat   : %s", r.jamBerangkat);

        gotoxy(37,32);
        printf("Harga           : ");
        tampilanhargajadwal(r.harga);

        strcpy(j.kotaAsal, r.kotaAsal);
        strcpy(j.kotaTujuan, r.kotaTujuan);
        strcpy(j.jamBerangkat, r.jamBerangkat);
        j.harga = r.harga;

        Kendaraan k;
        int kendaraan = pilihkendaraan(&k);
        if (kendaraan == -1) return;

        j.kendaraan = kendaraan;


        gotoxy(37,33);
        printf("Armada          : %s", k.nama_armada);

        gotoxy(37,34);
        printf("Kategori        : %s", k.kategori);

        gotoxy(37,35);
        printf("Tanggal         : ");
        if (inputtanggaljadwal(j.tanggal) == -1) return;

        strcpy(j.nama_armada, k.nama_armada);
        strcpy(j.kategori, k.kategori);

        fwrite(&j, sizeof(jadwal), 1, fp);
        fclose(fp);

        gotoxy(37,36);
        printf("Data berhasil dibuat!");

        gotoxy(37,37);
        printf("Tambah lagi? (y/n): ");

        // dari rute


        // dari kendaraan



        while (1) {
            x = _getch();
            if (x == 27) {
                clearArea(35,28,50,12);
                return;
            }
            if (x == 'y' || x == 'Y' || x == 'n' || x == 'N') {
                clearArea(35,28,50,12);
                break;
            }
        }

    } while (x == 'y' || x == 'Y');
}

#endif // PROJEK_CREATEJADWAL_H