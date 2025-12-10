//
// Created by Lenovo on 05/12/2025.
//

#ifndef PROJEK_CREATE_H
#define PROJEK_CREATE_H
#include "../FrameTabel.h"

int getStaffCount();
static void inputID(char *id);
int inputTglWithEsc(char *buffer, int maxLen);
int inputTelpWithEsc(char *buffer, int maxLen);
int pwESC(char *pw, int col, int row);
int inputRoleWithEsc(char *role);
static void inputGender(char *gender, int x, int y);
static void inputNoTelp(char *notlpn, int x, int y);

typedef struct {
    char username[50];
    char password[50];
    char id[100];
    char tgl[100];
    char gender[100];
    char Role[30];
    char notlpn[20];
}staff;

void create() {
    char n;

    do {
        clearLine(14, 3, 30);
        clearLine(15, 3, 30);
        clearLine(16, 3, 30);
        clearLine(17, 3, 30);
        clearLine(18, 3, 30);
        clearLine(19, 3, 30);
        clearLine(20, 3, 30);
        clearLine(22, 3, 30);
        clearLine(24, 3, 30);

        gotoxy(3,8);
        printf("[Esc] Keluar");

        FILE *fp = fopen("staff.dat", "ab");
        if (!fp) return;

        staff data;

        int count = getStaffCount() + 1;
        sprintf(data.id, "STF%03d", count);
        clearArea(3, 14, 20);
        gotoxy(3,14); printf("ID Otomatis  : %s", data.id);

        // Input Nama dengan deteksi ESC
        gotoxy(3,15); printf("Nama         : ");
        setPointer(16, 19);
        Nama(data.username);
        // Cek jika ESC ditekan (username kosong)
        if (strlen(data.username) == 0) {
            fclose(fp);
            return;
        }

        // Input Password dengan deteksi ESC
        gotoxy(3,16); printf("Kata Sandi   : ");
        PWesc(data.password, 18, 16);  // row=16, col=20 (posisi setelah label)
        // Cek jika ESC ditekan (password kosong)
        if (strlen(data.password) == 0) {
            fclose(fp);
            return;
        }

        // Input Tanggal Lahir dengan deteksi ESC
        gotoxy(3, 17); printf("Tanggal Lahir: ");
        setPointer(18, 19);
        inputTanggal(data.tgl);
        if (strlen(data.tgl) == 0) {  // Jika ESC ditekan
            fclose(fp);
            return;
        }

        // Input Kelamin dengan deteksi ESC
        gotoxy(3,18); printf("Kelamin      : ");
        inputGender(data.gender,12,18);
        if (strlen(data.gender) == 0) {  // Jika ESC ditekan
            fclose(fp);
            return;
        }

        // Input No Telepon dengan deteksi ESC
        gotoxy(3, 19); printf("No. Telepon  : ");
        inputNoTelp(data.notlpn, 18, 19);
        if (strlen(data.notlpn) == 0) {  // Jika ESC ditekan
            fclose(fp);
            return;
        }

        // Otomatis set Role = "Staff" karena ini di menu Staff
        strcpy(data.Role, "Staff");
        gotoxy(3,20); printf("Role         : Staff");

        fwrite(&data, sizeof(staff), 1, fp);
        fclose(fp);

        gotoxy(3,22);
        printf("Data berhasil dibuat!");
        gotoxy(3,24);
        printf("Tambah lagi? (y/n): ");

        while (1) {
            n = _getch();
            if (n == 27) return;
            if (n == 'y' || n == 'Y' || n == 'n' || n == 'N') {
                printf("%c", n);
                break;
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





//============================================//
//=========DATA DUMMY========================//
void buatdummy_ke_file() {
    FILE *fp;
    staff data;
    int max_data = 50;

    char *names[] = {"Budianto", "Ani_Yuniar", "Cahyo", "Dian_Sari", "Eko_Prabowo", "Fajar_Rizky", "Gita_S"};
    char *genders[] = {"Laki-laki", "Perempuan"};
    char *passwords[] = {"pass123", "rahasiaku", "admin", "qwert", "secure123", "testpw"};
    char *tgl_lahir[] = {"12/03/1995", "21/08/1998", "05/11/2000", "15/01/1990", "03/07/1985"};
    char *roles[] = {"Staff", "Manager", "Admin"};

    int num_names = sizeof(names) / sizeof(names[0]);
    int num_genders = sizeof(genders) / sizeof(genders[0]);
    int num_passwords = sizeof(passwords) / sizeof(passwords[0]);
    int num_tgl = sizeof(tgl_lahir) / sizeof(tgl_lahir[0]);
    int num_roles = sizeof(roles) / sizeof(roles[0]);

    fp = fopen("staff.dat", "wb");
    if (fp == NULL) {
        printf("ERROR: Gagal membuka atau membuat file staff.dat\n");
        return;
    }

    gotoxy(40,38);printf("Membuat data dummy dan menulis ke staff.dat...\n");

    for (int i = 0; i < max_data; i++) {
        int name_idx = i % num_names;
        int gender_idx = i % num_genders;
        int pw_idx = i % num_passwords;
        int tgl_idx = i % num_tgl;
        int role_idx = i % num_roles;

        sprintf(data.username, "%s_%02d", names[name_idx], i + 1);
        strcpy(data.password, passwords[pw_idx]);
        strcpy(data.gender, genders[gender_idx]);
        strcpy(data.tgl, tgl_lahir[tgl_idx]);
        strcpy(data.Role, roles[role_idx]);
        sprintf(data.notlpn, "0812%07d", 1000000 + i);

        if (fwrite(&data, sizeof(staff), 1, fp) != 1) {
            printf("Peringatan: Gagal menulis data dummy ke-%d.\n", i + 1);
        }
    }

    fclose(fp);
    gotoxy(40,39);printf("Selesai. %d entri data dummy berhasil disimpan di staff.dat.\n", max_data);
    getch();
}





//=====================================================//
//========================GENDER======================//
static void inputGender(char *gender, int x, int y) {
    char ch;

    gotoxy(x,y); printf("L/P : ");

    while (1) {
        ch = getch();

        if (ch == 27) {  // ESC
            gender[0] = '\0';
            break;
        }
        else if (ch == 'L' || ch == 'l') {  // Input L
            strcpy(gender, "Laki-laki");
            printf("L (Laki-laki)");

            // Tunggu Enter untuk confirm
            while (1) {
                ch = getch();
                if (ch == 13) {  // ENTER
                    return;
                }
                else if (ch == 8) {  // BACKSPACE - hapus pilihan
                    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b             \b\b\b\b\b\b\b\b\b\b\b\b\b");
                    break;
                }
                else if (ch == 27) {  // ESC
                    gender[0] = '\0';
                    return;
                }
            }
        }
        else if (ch == 'P' || ch == 'p') {  // Input P
            strcpy(gender, "Perempuan");
            printf("P (Perempuan)");

            // Tunggu Enter untuk confirm
            while (1) {
                ch = getch();
                if (ch == 13) {  // ENTER
                    return;
                }
                else if (ch == 8) {  // BACKSPACE - hapus pilihan
                    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b             \b\b\b\b\b\b\b\b\b\b\b\b\b");
                    break;
                }
                else if (ch == 27) {  // ESC
                    gender[0] = '\0';
                    return;
                }
            }
        }
        // Abaikan input selain L/P
    }
}
//===============================================================================================//



//===============================================================//
//==========================INPUT NO TELPON=====================//
static void inputNoTelp(char *notlpn, int x, int y) {
    int i = 0;
    char ch;
    char display[14] = "08"; // Awalan 08 + 11 digit + null terminator

    // Tampilkan awalan 08
    gotoxy(x,y);printf("08");
    i = 2;

    while (1) {
        ch = getch();

        if (ch == 13) {  // ENTER
            // Hanya bisa enter jika sudah 13 digit
            if (i == 12) {
                display[i] = '\0';
                strcpy(notlpn, display);
                break;
            }
        }
        else if (ch == 27) {  // ESC
            notlpn[0] = '\0';
            break;
        }
        else if (ch == 8) {  // BACKSPACE
            // Hanya bisa hapus setelah "08"
            if (i > 2) {
                i--;
                printf("\b \b");
            }
        }
        else if (ch >= '0' && ch <= '9') {  // Hanya terima angka
            if (i < 12) {  // Maksimal 13 digit
                display[i++] = ch;
                printf("%c", ch);
            }
        }
        // Abaikan input selain angka
    }
}

#endif