// #ifndef PROJEK_READTIKETPENUMPANG_H
// #define PROJEK_READTIKETPENUMPANG_H
//
// #include "../FrameTabel.h"
// #include "../Pemesanan/Pesantiket.h"
// #include <stdio.h>
// #include <string.h>
//
// #define MAX_ROWS_PER_PAGE 8
//
// void readTiketPenumpang() {
//
//     FILE *fp;
//     tiket data[1000];
//     int total = 0;
//
//     int startX = 37;
//     int startY = 12;
//
//     // ===== LEBAR KOLOM =====
//     int wNo = 3, wID = 10, wNama = 20, wTelp = 15;
//     int wRute = 25, wTgl = 12, wStatus = 10;
//
//     fp = fopen("tiket.dat", "rb");
//     if (!fp) {
//         gotoxy(startX, startY);
//         printf("Belum ada data tiket.");
//         getch();
//         return;
//     }
//
//     while (fread(&data[total], sizeof(tiket), 1, fp) == 1) {
//         if (total < 1000) total++;
//     }
//     fclose(fp);
//
//     int total_pages = (total + MAX_ROWS_PER_PAGE - 1) / MAX_ROWS_PER_PAGE;
//     int current_page = 1;
//     char key;
//
//     int totalWidth =
//         1 + (wNo+2)+(wID+2)+(wNama+2)+(wTelp+2)+
//         (wRute+2)+(wTgl+2)+(wStatus+2);
//
//     char garis[300];
//     memset(garis, '-', totalWidth);
//     garis[totalWidth] = '\0';
//
//     do {
//         int start = (current_page - 1) * MAX_ROWS_PER_PAGE;
//         int end = start + MAX_ROWS_PER_PAGE;
//         if (end > total) end = total;
//
//         clearArea(startX, startY + 1, totalWidth, 18);
//
//         gotoxy(80, 13);
//         printf("=== DAFTAR TIKET PENUMPANG ===");
//
//         int row = startY + 2;
//
//         // ===== TABEL =====
//         gotoxy(startX, row++); printf("%s", garis);
//
//         gotoxy(startX, row++);
//         printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
//                wNo+1,"No",
//                wID+1,"ID Tiket",
//                wNama+1,"Nama",
//                wTelp+1,"Telepon",
//                wRute+1,"Rute",
//                wTgl+1,"Tanggal",
//                wStatus+1,"Status");
//
//         gotoxy(startX, row++); printf("%s", garis);
//
//         for (int i = start; i < end; i++) {
//             char rute[40];
//             sprintf(rute, "%s-%s",
//                     data[i].rute_awal,
//                     data[i].tujuan);
//
//             gotoxy(startX, row++);
//             printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
//                    wNo+1, i+1,
//                    wID+1, data[i].id_tiket,
//                    wNama+1, data[i].nama_penumpang,
//                    wTelp+1, data[i].notlpn,
//                    wRute+1, rute,
//                    wTgl+1, data[i].tanggal_berangkat,
//                    wStatus+1, data[i].status);
//         }
//
//         gotoxy(startX, row++); printf("%s", garis);
//
//         // ===== NAVIGASI (SESUIAI PERMINTAANMU) =====
//         bentukframe(3, 11, 27, 12);
//         gotoxy(6, 13); printf("[SPASI] Lanjut");
//         gotoxy(6, 15); printf("[BACKSPACE] Kembali");
//         gotoxy(6, 17); printf("[ENTER] Keluar");
//         gotoxy(6, 19); printf("Halaman: %d/%d", current_page, total_pages);
//         gotoxy(6, 21); printf("Total  : %d data", total);
//
//         key = getch();
//
//         if (key == ' ' && current_page < total_pages)
//             current_page++;
//         else if (key == 8 && current_page > 1)
//             current_page--;
//
//     } while (key != 13);
// }
//
// #endif