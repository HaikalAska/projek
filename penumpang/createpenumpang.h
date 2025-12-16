//
// Created by Lenovo on 05/12/2025.
//

#ifndef PROJEK_CREATEPENUMPANG_H
#define PROJEK_CREATEPENUMPANG_H

#include "../FrameTabel.h"

// ================= STRUKTUR DATA ================= //
typedef struct {
    char id[20];
    char nama[50];
    char no_hp[20];
    char email[50];
    char rute[10];
} penumpang;

// ================= DEKLARASI ================= //
int getPenumpangCount();
static int cekEmailDuplicate(char *email);
void inputEmail(char *email, int row, int col) {
    int i = 0;
    char ch;
    char temp[50];
    int auto_domain = 0;

    gotoxy(col, row);

    while (1) {
        ch = getch();

        // ================= ENTER =================
        if (ch == 13) {
            temp[i] = '\0';

            if (i == 0 || strchr(temp, '@') == NULL) {
                gotoxy(col, row);
                printf("Email tidak valid!");
                Sleep(800);
                clearArea(col, row, 40, 1);
                gotoxy(col, row);
                i = 0;
                auto_domain = 0;
                continue;
            }

            strcpy(email, temp);
            break;
        }

        // ================= ESC =================
        else if (ch == 27) {
            email[0] = '\0';
            break;
        }

        // ================= BACKSPACE =================
        else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");

                // Jika hapus @gmail.com
                if (auto_domain && i < strlen("@gmail.com")) {
                    auto_domain = 0;
                }
            }
        }

        // ================= AUTO GMAIL =================
        else if (ch == '@' && !auto_domain) {
            char domain[] = "@gmail.com";
            int len = strlen(domain);

            if (i + len < 49) {
                strcpy(&temp[i], domain);
                printf("%s", domain);
                i += len;
                auto_domain = 1;

                // ⛔ Langsung hentikan input
                temp[i] = '\0';
                strcpy(email, temp);
                break;
            }
        }


        // ================= INPUT NORMAL =================
        else if ((ch >= 'a' && ch <= 'z') ||
                 (ch >= 'A' && ch <= 'Z') ||
                 (ch >= '0' && ch <= '9') ||
                 ch == '.' || ch == '_') {

            if (i < 49) {
                temp[i++] = ch;
                printf("%c", ch);
            }
                 }
    }
}
void inputRute(char *rute, int row, int col) {
    int i = 0;
    char ch;

    gotoxy(col, row);

    while (1) {
        ch = getch();

        // ENTER
        if (ch == 13) {
            if (i == 0) {
                gotoxy(col, row);
                printf("Rute tidak boleh kosong!");
                Sleep(800);
                clearArea(col, row, 30, 1);
                gotoxy(col, row);
                i = 0;
                continue;
            }
            rute[i] = '\0';
            break;
        }

        // ESC
        else if (ch == 27) {
            rute[0] = '\0';
            break;
        }

        // BACKSPACE
        else if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        }

        // HANYA ANGKA
        else if (ch >= '0' && ch <= '9') {
            if (i < 9) {
                rute[i++] = ch;
                printf("%c", ch);
            }
        }
    }
}



// ================= CREATE PENUMPANG ================= //
void createPenumpang() {
    char n;

    do {
        bentukframe(35, 27, 108, 12);
        gotoxy(78, 27); printf("=== BUAT PENUMPANG ===");

        FILE *fp = fopen("penumpang.dat", "ab");
        if (!fp) return;

        penumpang data;

        // ID otomatis
        int count = getPenumpangCount() + 1;
        sprintf(data.id, "PNP%03d", count);

        gotoxy(37, 28);
        printf("ID Penumpang : %s", data.id);

        // ================= NAMA ================= //
        gotoxy(37, 29); printf("Nama         : ");
        setPointer(30, 53);
        INPUTNama(data.nama);
        if (strlen(data.nama) == 0) {
            fclose(fp);
            return;
        }

        // ================= NO HP ================= //
        gotoxy(37, 30); printf("No HP        : ");
        inputNoTelp(data.no_hp, 31, 52);
        if (strlen(data.no_hp) == 0) {
            fclose(fp);
            return;
        }
        // ================= RUTE ================= //
        gotoxy(37, 31); printf("Rute         : ");
        inputRute(data.rute, 31, 52);
        if (strlen(data.rute) == 0) {
            fclose(fp);
            return;
        }
        // ================= EMAIL ================= //
        gotoxy(37, 32); printf("Email        : ");
        setPointer(31, 52);
        inputEmail(data.email, 32, 52);
        if (strlen(data.email) == 0) {
            fclose(fp);
            return;
        }

        // ================= SIMPAN ================= //
        fwrite(&data, sizeof(penumpang), 1, fp);
        fclose(fp);

        gotoxy(37, 33);
        printf("Data penumpang berhasil dibuat!");

        gotoxy(37, 34);
        printf("Tambah lagi? (y/n): ");

        while (1) {
            n = _getch();
            if (n == 27) {
                clearArea(35, 27, 80, 12);
                return;
            }
            if (n == 'y' || n == 'Y' || n == 'n' || n == 'N') {
                clearArea(35, 27, 80, 12);
                if (n == 'n' || n == 'N') return;
                break;
            }
        }

    } while (n == 'y' || n == 'Y');
}

// ================= HITUNG DATA ================= //
int getPenumpangCount() {
    FILE *fp = fopen("penumpang.dat", "rb");
    if (!fp) return 0;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fclose(fp);

    return size / sizeof(penumpang);
}

// ================= CEK EMAIL DUPLIKAT ================= //
static int cekEmailDuplicate(char *email) {
    FILE *fp = fopen("penumpang.dat", "rb");
    if (!fp) return 0;

    penumpang temp;
    while (fread(&temp, sizeof(penumpang), 1, fp)) {
        if (strcmp(temp.email, email) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void buatdummy_penumpang_ke_file() {
    FILE *fp;
    penumpang data;
    int max_data = 50;

    char *names[] = {
        "Budi Santoso", "Ani Yulianti", "Cahyo Pratama", "Dian Permatasari",
        "Eko Wijaya", "Fajar Rizki", "Gita Ayu", "Hendra Gunawan",
        "Indah Lestari", "Joko Susilo", "Kartika Dewi", "Lukman Hakim",
        "Maya Sari", "Nur Hidayat", "Oki Setiawan", "Putri Amanda",
        "Rizky Ramadhan", "Sari Indah", "Tono Wibowo", "Utari Puspita",
        "Wahyu Nugroho", "Yuni Astuti", "Zainal Arifin", "Agus Supriyadi",
        "Bayu Aji", "Citra Ningrum", "Dedi Hartono", "Evi Marlina",
        "Fandi Ahmad", "Gusti Ayu"
    };

    int num_names = sizeof(names) / sizeof(names[0]);

    fp = fopen("penumpang.dat", "wb");
    if (!fp) {
        printf("ERROR: Gagal membuat penumpang.dat\n");
        getch();
        return;
    }

    printf("        MEMBUAT DATA DUMMY PENUMPANG\n\n");

    for (int i = 0; i < max_data; i++) {

        // ================= ID =================
        sprintf(data.id, "PNP%03d", i + 1);

        // ================= NAMA =================
        strcpy(data.nama, names[i % num_names]);
        if (i >= num_names) {
            char temp[60];
            sprintf(temp, "%s %d", names[i % num_names], (i / num_names) + 1);
            strcpy(data.nama, temp);
        }

        // ================= NO HP =================
        sprintf(data.no_hp, "08%d%07d",
                12 + (i % 8),
                1000000 + i);

        // ================= RUTE (ANGKA SAJA) =================
        // Contoh rute: 101, 102, 103, dst
        sprintf(data.rute, "%03d", (i % 5) + 101);

        // ================= EMAIL =================
        char email_temp[50];
        char nama_lower[50];
        strcpy(nama_lower, data.nama);

        // lowercase
        for (int j = 0; nama_lower[j]; j++) {
            nama_lower[j] = tolower(nama_lower[j]);
        }

        // ganti spasi jadi titik
        for (int j = 0; nama_lower[j]; j++) {
            if (nama_lower[j] == ' ')
                nama_lower[j] = '.';
        }

        sprintf(email_temp, "%s%d@gmail.com", nama_lower, i + 1);
        strcpy(data.email, email_temp);

        // ================= SIMPAN =================
        fwrite(&data, sizeof(penumpang), 1, fp);
    }

    fclose(fp);

    printf("[✓] Berhasil membuat %d data dummy penumpang\n", max_data);
    printf("Tekan tombol apapun untuk kembali...");
    getch();
}



#endif
