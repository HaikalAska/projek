void deleteKendaraan() {
    FILE *fp;
    Kendaraan data;
    Kendaraan kendaraanList[100];
    int count = 0;
    int pilihan = 0;
    char konfirmasi = '\0';

    // ===== BACA DATA =====
    fp = fopen("kendaraan.dat", "rb");
    if (!fp) {
        gotoxy(3, 13);
        printf("File kendaraan.dat tidak ditemukan!");
        getch();
        return;
    }

    while (fread(&data, sizeof(Kendaraan), 1, fp) == 1) {
        kendaraanList[count++] = data;
    }
    fclose(fp);

    // ===== BUBBLE SORT BERDASARKAN ID (CHAR) =====
    // DESCENDING (ID terbesar di atas, SAMA DENGAN TAMPILAN)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(kendaraanList[j].id_kendaraan,
                       kendaraanList[j + 1].id_kendaraan) < 0) {

                Kendaraan tmp = kendaraanList[j];
                kendaraanList[j] = kendaraanList[j + 1];
                kendaraanList[j + 1] = tmp;
            }
        }
    }

    if (count == 0) {
        gotoxy(3, 13);
        printf("Tidak ada data kendaraan!");
        getch();
        return;
    }

    // ===== INPUT PILIHAN =====
    while (1) {
        char buffer[10] = "";
        int idx = 0;
        char ch;

        gotoxy(3, 25);
        printf("Pilih No Urut : ");
        gotoxy(20, 25);
        printf("          ");
        gotoxy(20, 25);

        while (1) {
            ch = getch();

            if (ch == 27) return; // ESC batal

            if (ch == 13) {
                if (idx == 0) {
                    gotoxy(3, 26);
                    printf("Pilih no terlebih dahulu!");
                    Sleep(1500);
                    gotoxy(3, 26);
                    printf("                         ");
                    break;
                }

                buffer[idx] = '\0';
                pilihan = atoi(buffer);
                break;
            }

            if (ch == 8 && idx > 0) {
                idx--;
                buffer[idx] = '\0';
                gotoxy(20, 25);
                printf("          ");
                gotoxy(20, 25);
                printf("%s", buffer);
            }

            if (isdigit(ch) && idx < 9) {
                buffer[idx++] = ch;
                buffer[idx] = '\0';
                printf("%c", ch);
            }
        }

        if (idx == 0) continue;

        if (pilihan < 1 || pilihan > count) {
            gotoxy(3, 26);
            printf("Pilihan tidak valid!");
            Sleep(1200);
            gotoxy(3, 26);
            printf("                    ");
            continue;
        }

        if (strcmp(kendaraanList[pilihan - 1].status, "Nonaktif") == 0) {
            gotoxy(3, 26);
            printf("Kendaraan sudah nonaktif!");
            Sleep(1500);
            gotoxy(3, 26);
            printf("                          ");
            continue;
        }

        break;
    }

    Kendaraan terpilih = kendaraanList[pilihan - 1];

    // ===== TAMPIL DETAIL =====
    bentukframe(35, 27, 60, 15);
    gotoxy(55, 27); printf("=== DATA KENDARAAN ===");

    gotoxy(37, 29); printf("ID Kendaraan : %s", terpilih.id_kendaraan);
    gotoxy(37, 30); printf("Kategori     : %s", terpilih.kategori);
    gotoxy(37, 31); printf("Kapasitas    : %s", terpilih.kapasitas);
    gotoxy(37, 32); printf("Fasilitas    : %s", terpilih.fasilitas);
    gotoxy(37, 33); printf("Nama Armada  : %s", terpilih.nama_armada);
    gotoxy(37, 34); printf("No plat      : %s", terpilih.plat_nomor);
    gotoxy(37, 35); printf("Tahun        : %s", terpilih.tahun);
    gotoxy(37, 36); printf("Status       : %s", terpilih.status);

    // ===== KONFIRMASI =====
    gotoxy(37, 37);
    printf("Nonaktifkan kendaraan ini? (y/n): ");

    while (1) {
        char ch = tolower(getch());

        if (ch == 27) return;

        if (ch == 'y' || ch == 'n') {
            konfirmasi = ch;
            printf("%c", ch);
            break;
        }
    }

    if (konfirmasi != 'y') {
        gotoxy(37, 38);
        printf("Dibatalkan!");
        getch();
        return;
    }

    // ===== SOFT DELETE =====
    fp = fopen("kendaraan.dat", "rb+");
    if (!fp) return;

    while (fread(&data, sizeof(Kendaraan), 1, fp) == 1) {
        if (strcmp(data.id_kendaraan, terpilih.id_kendaraan) == 0) {

            strcpy(data.status, "Nonaktif");

            fseek(fp, -sizeof(Kendaraan), SEEK_CUR);
            fwrite(&data, sizeof(Kendaraan), 1, fp);

            gotoxy(37, 38);
            printf("Kendaraan berhasil dinonaktifkan!");
            break;
        }
    }

    fclose(fp);
    getch();
}
