#ifndef PROJEK_READ_H
#define PROJEK_READ_H
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "../FrameTabel.h"
#include "create.h"


void baca() {

    FILE *fp;
    staff all_staff[1000];
    int total_staff = 0;

    int startX = 37;
    int startY = 12;

    // Lebar kolom
    int wNo = 3;
    int wUsr = 12;      // Username
    int wNama = 17;     // Nama
    int wPw = 10;
    int wGen = 10;
    int wTgl = 11;
    int wTelp = 11;
    int wStatus = 10;
    int wRole = 10;

    int rowsPerPage = 8;
    int current_page = 1;
    int total_pages = 1;
    char key;

    bentukframe(34, 11, 121, 35);

    fp = fopen("staff.dat", "rb");
    if (!fp) {
        gotoxy(startX, startY);
        printf("File staff.dat tidak ditemukan!");
        getch();
        return;
    }

    staff data;
    while (fread(&data, sizeof(staff), 1, fp) == 1) {
        if (total_staff < 1000) {
            all_staff[total_staff++] = data;
        }
    }
    fclose(fp);


    for (int i = 0; i < total_staff - 1; i++) {
        for (int j = i + 1; j < total_staff; j++) {
            if (strcmp(all_staff[i].id, all_staff[j].id) < 0) {
                staff temp = all_staff[i];
                all_staff[i] = all_staff[j];
                all_staff[j] = temp;
            }
        }
    }

    if (total_staff > 0) {
        total_pages = (total_staff + rowsPerPage - 1) / rowsPerPage;
    }

    int totalWidth = 1 + (wNo+2) + (wUsr+2) + (wNama+2) + (wPw+2) +
                 (wGen+2) + (wTgl+2) + (wTelp+2) + (wRole+2) + (wStatus+1);

    char line[200];
    memset(line, '-', totalWidth);
    line[totalWidth] = '\0';

    do {
        clearArea(startX, startY, totalWidth + 5, rowsPerPage + 10);

        gotoxy(80, 13);
        printf("=== DAFTAR STAFF ===");

        int row = startY + 2;

        gotoxy(startX, row++);
        printf("%s", line);

        gotoxy(startX, row++);
        printf("|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
               wNo+1,    "No",
               wUsr+1,   "Nama Pengguna",
               wNama+1,  "Nama",
               wPw+1,    "Kata Sandi",
               wGen+1,   "Kelamin",
               wTgl+1,   "Tgl Lahir",
               wTelp+1,  "Telepon",
               wRole+1,  "Jabatan",
               wStatus+1,"Status"
        );

        gotoxy(startX, row++);
        printf("%s", line);

        int start_index = (current_page - 1) * rowsPerPage;
        int end_index = start_index + rowsPerPage;
        if (end_index > total_staff) end_index = total_staff;

        for (int i = start_index; i < end_index; i++) {
            staff current_staff = all_staff[i];

            // Mask password
            char maskedPw[12];
            int pwLen = strlen(current_staff.password);
            int showLen = (pwLen > 5) ? 5 : pwLen;
            memset(maskedPw, '*', showLen);
            maskedPw[showLen] = '\0';

            // Truncate nama kalau kepanjangan
            char nama[20];
            snprintf(nama, wNama+1, "%s", current_staff.nama);
            if (strlen(current_staff.nama) > wNama) {
                nama[wNama-2] = '.';
                nama[wNama-1] = '.';
                nama[wNama] = '\0';
            }

            // Truncate username kalau kepanjangan
            char username[15];
            snprintf(username, wUsr+1, "%s", current_staff.username);
            if (strlen(current_staff.username) > wUsr) {
                username[wUsr-2] = '.';
                username[wUsr-1] = '.';
                username[wUsr] = '\0';
            }

            // Truncate field lainnya
            char gender[12];
            snprintf(gender, wGen+1, "%s", current_staff.gender);
            if (strlen(current_staff.gender) > wGen) {
                gender[wGen-2] = '.';
                gender[wGen-1] = '.';
                gender[wGen] = '\0';
            }

            char tgl[13];
            snprintf(tgl, wTgl+1, "%s", current_staff.tgl);
            if (strlen(current_staff.tgl) > wTgl) {
                tgl[wTgl-2] = '.';
                tgl[wTgl-1] = '.';
                tgl[wTgl] = '\0';
            }

            char notlpn[13];
            snprintf(notlpn, wTelp+1, "%s", current_staff.notlpn);


            char role[12];
            snprintf(role, wRole+1, "%s", current_staff.Role);
            if (strlen(current_staff.Role) > wRole) {
                role[wRole-2] = '.';
                role[wRole-1] = '.';
                role[wRole] = '\0';
            }

            char status[12];
            snprintf(status, wStatus+1, "%s", current_staff.status);
            if (strlen(current_staff.status) > wStatus) {
                status[wStatus-2] = '.';
                status[wStatus-1] = '.';
                status[wStatus] = '\0';
            }

            gotoxy(startX, row++);
            printf("|%-*d|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|%-*s|",
                   wNo+1,    i + 1,
                   wUsr+1,   username,
                   wNama+1,  nama,
                   wPw+1,    maskedPw,
                   wGen+1,   gender,
                   wTgl+1,   tgl,
                   wTelp+1,  notlpn,
                   wRole+1,  role,
                   wStatus+1, status
            );
        }

        gotoxy(startX, row++);
        printf("%s", line);

        bentukframe(3, 11, 27, 12);
        gotoxy(6, 13);
        printf("[SPASI] Lanjut");
        gotoxy(6, 15);
        printf("[BACKSPACE] Kembali");
        gotoxy(6, 17);
        printf("[ENTER] Menu Berikutnya");
        gotoxy(6, 19);
        printf("Halaman: %d/%d", current_page, total_pages);
        gotoxy(6, 21);
        printf("Total  : %d data", total_staff);

        key = getch();

        if (key == ' ') {
            if (current_page < total_pages) current_page++;
        } else if (key == 8) {
            if (current_page > 1) current_page--;
        }

    } while (key != 13);

}

void totalStaff(int x, int y) {
    FILE *fp_staff = fopen("staff.dat", "rb");
    if (!fp_staff) {
        gotoxy(x, y);
        printf("0");
        return;
    }

    staff data;
    int total = 0;

    while (fread(&data, sizeof(staff), 1, fp_staff)) {
        total++;
    }

    fclose(fp_staff);

    gotoxy(x, y);
    printf("%d", total);
}

#endif