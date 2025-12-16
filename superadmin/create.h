//
// Created by Lenovo on 05/12/2025.
//

#ifndef PROJEK_CREATE_H
#define PROJEK_CREATE_H
#include "../FrameTabel.h"

int getStaffCount();
static void inputID(char *id);
int pwESC(char *pw, int col, int row);
static void inputUsername(char *username, int row, int col);

typedef struct {
    char nama[50];
    char username[50];
    char password[50];
    char id[100];
    char tgl[100];
    char gender[100];
    char Role[30];
    char notlpn[20];
    char status [10];
}staff;

void create() {
    char n;

    do {
        bentukframe(35, 27, 108, 16);
        gotoxy(80, 27);printf("=== BUAT STAFF ===");
        // Buka file untuk append
        FILE *fp = fopen("staff.dat", "ab");
        if (!fp) return;

        staff data;

        // Generate ID otomatis
        int count = getStaffCount() + 1;
        sprintf(data.id, "STF%03d", count);
        gotoxy(37, 28);
        printf("ID Otomatis  : %s", data.id);



        // input nama
        gotoxy(37, 29); printf("Nama         : ");
        setPointer(30, 53);
        INPUTNama(data.nama);  // Tambah parameter row dan col
        if (strlen(data.nama) == 0) {
            fclose(fp);
            break;
        }

        // Input username
        gotoxy(37, 30);
        printf("Username     : ");
        // Clear area input nama
        clearArea(53, 33, 30, 1);
        setPointer(31, 53);
        inputUsername(data.username,30,52);
        if (strlen(data.username) == 0) {
            fclose(fp);
            return;
        }

        // Input Password
        gotoxy(37, 31);
        printf("Kata Sandi   : ");
        // Clear area input password
        PWesc(data.password, 31, 52);
        if (strlen(data.password) == 0) {
            fclose(fp);
            return;
        }

        // Input Tanggal Lahir
        gotoxy(37, 32);
        printf("Tanggal Lahir: ");
        // Clear area input tanggal
        setPointer(33, 53);
        inputTanggal(data.tgl);
        if (strlen(data.tgl) == 0) {
            fclose(fp);
            return;
        }

        // Input Kelamin
        gotoxy(37, 33);
        printf("Kelamin      : ");
        // Clear area input gender
        inputGender(data.gender, 46, 33);
        if (strlen(data.gender) == 0) {
            fclose(fp);
            return;
        }

        // Input No Telepon
        gotoxy(37, 34);
        printf("No. Telepon  : ");
        // Clear area input telepon
        inputNoTelp(data.notlpn, 52, 34);
        if (strlen(data.notlpn) == 0) {
            fclose(fp);
            return;
        }

        // Set Role otomatis sebagai Staff
        gotoxy(37, 35);
        printf("Role         : ");
        // Clear area input gender
        inputRole(data.Role, 46, 35);
        if (strlen(data.gender) == 0) {
            fclose(fp);
            return;
        }



        strcpy(data.status, "Aktif");
        gotoxy(37, 36);
        printf("Status       : %s ", data.status);



        // Simpan data ke file
        fwrite(&data, sizeof(staff), 1, fp);
        fclose(fp);

        // Konfirmasi sukses
        gotoxy(37, 37);
        printf("Data berhasil dibuat!");

        // Clear area konfirmasi
        gotoxy(37, 38);
        printf("Tambah lagi? (y/n): ");


        // Input konfirmasi
        while (1) {
            n = _getch();
            if (n == 27) {
                clearArea(35, 28, 50, 12); // Clear semua sebelum keluar
                return;
            }
            if (n == 'y' || n == 'Y' || n == 'n' || n == 'N') {
                clearArea(35, 28, 50, 12); // Clear semua sebelum ulang
                if (n == 'n' || n == 'N') {
                    return;
                } else {
                    break;
                }
            }
        }

    } while (n == 'y' || n == 'Y');

}

int getStaffCount() {
    FILE *fp = fopen("staff.dat", "rb");
    if (!fp) return 0;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);

    return size / sizeof(staff);
}










//========================================================================//
//===================CEK JIKA ADA DUPLIKAT USERNAME======================//
static int cekUsernameDuplicate(char *username) {
    FILE *fp = fopen("staff.dat", "rb");
    if (!fp) return 0;

    staff temp;
    while (fread(&temp, sizeof(staff), 1, fp)) {
        if (strcmp(temp.username, username) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
//=====================================================================//





//=====================================================//
//===================USERNAME======================//
static void inputUsername(char *username, int row, int col) {
    int i = 0;
    char ch;
    char temp[50];

    while (1) {
        ch = getch();

        if (ch == 13) {  // ENTER
            temp[i] = '\0';

            if (i == 0) {
                printf(" [Username tidak boleh kosong!]");
                Sleep(800);

                // Kembali ke posisi awal
                gotoxy(col, row);
                printf("                               ");
                gotoxy(col, row);

                i = 0;
                continue;
            }

            // Cek duplicate
            if (cekUsernameDuplicate(temp)) {
                printf(" [Username sudah ada! Gunakan yang lain]");
                Sleep(800);

                // Kembali ke posisi awal
                gotoxy(col, row);
                printf("                                                ");
                gotoxy(col, row);

                // Tampilkan kembali text yang sudah diketik
                for (int k = 0; k < i; k++) {
                    printf("%c", temp[k]);
                }

                // Reset
                i = 0;
                temp[0] = '\0';

                // Clear lagi
                gotoxy(col, row);
                printf("                                                ");
                gotoxy(col, row);
                continue;
            }


            strcpy(username, temp);
            break;
        }
        else if (ch == 27) {  // ESC
            username[0] = '\0';
            break;
        }
        else if (ch == 8) {  // BACKSPACE
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if (ch == 32) {  // BLOKIR SPASI
            continue;
        }
        else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
                 (ch >= '0' && ch <= '9') || ch == '.' || ch == '_') {
            if (i < 49) {
                temp[i++] = ch;
                printf("%c", ch);
            }
        }
    }
}
//==============================================================================//








//============================================//
//=========DATA DUMMY========================//
void buatdummy_ke_file() {
    FILE *fp;
    staff data;
    int max_data = 50;

    char *names[] = {"Budi Santoso", "Ani Yulianti", "Cahyo Pratama", "Dian Permatasari",
                     "Eko Wijaya", "Fajar Rizki", "Gita Ayu", "Hendra Gunawan",
                     "Indah Lestari", "Joko Susilo", "Kartika Dewi", "Lukman Hakim",
                     "Maya Sari", "Nur Hidayat", "Oki Setiawan", "Putri Amanda",
                     "Rizky Ramadhan", "Sari Indah", "Tono Wibowo", "Utari Puspita",
                     "Wahyu Nugroho", "Yuni Astuti", "Zainal Arifin", "Agus Supriyadi",
                     "Bayu Aji", "Citra Ningrum", "Dedi Hartono", "Evi Marlina",
                     "Fandi Ahmad", "Gusti Ayu"};
    char *genders[] = {"Laki-laki", "Perempuan"};
    char *passwords[] = {"pass123", "rahasiaku", "admin", "qwert",
                         "secure123", "testpw", "password123", "staff2024",
                         "admin123", "user123"};
    char *tgl_lahir[] = {"12/03/1995", "21/08/1998", "05/11/2000",
                         "15/01/1990", "03/07/1985", "19/09/1992",
                         "28/04/1997", "14/12/1989", "23/06/1994",
                         "08/10/1987"};

    int num_names = sizeof(names) / sizeof(names[0]);
    int num_genders = sizeof(genders) / sizeof(genders[0]);
    int num_passwords = sizeof(passwords) / sizeof(passwords[0]);
    int num_tgl = sizeof(tgl_lahir) / sizeof(tgl_lahir[0]);

    fp = fopen("staff.dat", "wb");
    if (fp == NULL) {
        printf("ERROR: Gagal membuka atau membuat file staff.dat\n");
        return;
    }

    printf("         MEMBUAT DATA DUMMY STAFF\n");

    for (int i = 0; i < max_data; i++) {
        int name_idx = i % num_names;
        int gender_idx = i % num_genders;
        int pw_idx = i % num_passwords;
        int tgl_idx = i % num_tgl;

        // Generate ID otomatis
        sprintf(data.id, "STF%03d", i + 1);

        // ISI NAMA LENGKAP
        strcpy(data.nama, names[name_idx]);

        // Jika nama sudah terpakai, tambahkan angka
        if (i >= num_names) {
            char temp[100];
            sprintf(temp, "%s %d", names[name_idx], (i/num_names) + 1);
            strcpy(data.nama, temp);
        }

        // GENERATE USERNAME dari nama (lowercase, tanpa spasi)
        char temp_username[100];
        strcpy(temp_username, names[name_idx]);

        // Lowercase
        for (int j = 0; temp_username[j]; j++) {
            temp_username[j] = tolower(temp_username[j]);
        }

        // Hapus spasi - ambil kata pertama aja
        char *space = strchr(temp_username, ' ');
        if (space) *space = '\0';

        // Tambah angka biar unik
        sprintf(data.username, "%s%d", temp_username, i + 1);


        int role_dist = i % 10;
        if (role_dist < 7) {
            strcpy(data.Role, "Staff");
        } else if (role_dist < 9) {
            strcpy(data.Role, "Manager");
        } else {
            strcpy(data.Role, "Admin");
        }

        // Data lainnya
        strcpy(data.password, passwords[pw_idx]);
        strcpy(data.gender, genders[gender_idx]);
        strcpy(data.tgl, tgl_lahir[tgl_idx]);
        sprintf(data.notlpn, "08%d%07d", 12 + (i % 8), 1000000 + i);


        strcpy(data.status, (i % 5 == 0) ? "Nonaktif" : "Aktif");


        fwrite(&data, sizeof(staff), 1, fp);
    }

    fclose(fp);

    printf("\n[✓] Berhasil membuat %d data dummy staff\n", max_data);
    printf("Tekan tombol apapun untuk kembali...");
    getch();
}
//==============================================================================//




#endif