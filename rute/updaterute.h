//
// Created by ASUS on 12/14/2025.
//

#ifndef PROJEK_UPDATERUTE_H
#define PROJEK_UPDATERUTE_H

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "../FrameTabel.h"
#include "createrute.h"


// ================= RENDER DATA BARU =================
void renderDataBaru(Rute data) {
    bentukframe(85, 29, 55, 15);
    gotoxy(109, 30); printf("DATA BARU");

    gotoxy(90, 32); printf("Kota Asal    : ");
    gotoxy(90, 33); printf("Kota Tujuan  : ");
    gotoxy(90, 34); printf("Harga        : ");
    gotoxy(90, 35); printf("Berangkat    : ");
    gotoxy(90, 36); printf("Tiba         : ");
    gotoxy(90, 37); printf("status       : ");
    gotoxy(90, 38); printf("Durasi       : ");
    gotoxy(90, 40); printf("[ SIMPAN ]");
}

// Tambahkan di atas fungsi updaterute()
static void inputStatusrute(char *status, int x, int y) {
    char ch;
    int inputX = x + 6;

    gotoxy(x, y);
    printf("A/N : ");
    gotoxy(inputX, y);

    while (1) {
        ch = getch();

        if (ch == 27) {
            status[0] = '\0';
            return;
        }
        else if (ch == 'A' || ch == 'a') {
            strcpy(status, "Aktif");
            printf("A (Aktif)");

            while (1) {
                ch = getch();
                if (ch == 13) return;
                else if (ch == 8) {
                    clearArea(inputX, y, 20, 1);
                    gotoxy(inputX, y);
                    break;
                }
                else if (ch == 27) {
                    status[0] = '\0';
                    return;
                }
            }
        }
        else if (ch == 'N' || ch == 'n') {
            strcpy(status, "Nonaktif");
            printf("N (Nonaktif)");

            while (1) {
                ch = getch();
                if (ch == 13) return;
                else if (ch == 8) {
                    clearArea(inputX, y, 20, 1);
                    gotoxy(inputX, y);
                    break;
                }
                else if (ch == 27) {
                    status[0] = '\0';
                    return;
                }
            }
        }
    }
}
// ================= UPDATE RUTE =================
void updaterute() {
    FILE *fp, *temp;
    Rute data;
    Rute list[1000];  // ← TAMBAH untuk validasi
    int count = 0;     // ← TAMBAH untuk validasi
    int targetNo = 0, currentNo = 1, found = 0;

    // ===== BUKA FILE DAN BACA SEMUA DATA =====
    fp = fopen("rute.dat", "rb");
    if (!fp) {
        gotoxy(3, 27);
        printf("File rute.dat tidak ditemukan!");
        getch();
        return;
    }

    // Baca semua data untuk validasi
    while (fread(&list[count], sizeof(Rute), 1, fp) == 1) {
        if (count < 1000) count++;
    }
    fclose(fp);

    if (count == 0) {
        gotoxy(3, 27);
        printf("Tidak ada data rute!");
        getch();
        return;
    }

    // ===== INPUT NOMOR URUT DENGAN VALIDASI (SAMA DENGAN DELETERUTE) =====
    while (1) {
        char buffer[10] = "";
        int idx = 0;
        char ch;

        gotoxy(3, 25);
        printf("Pilih No Urut : ");
        gotoxy(20, 25);
        printf("          ");  // Bersihkan area input
        gotoxy(20, 25);

        // Loop input angka
        while (1) {
            ch = getch();

            // ESC → Batal
            if (ch == 27) {
                gotoxy(3, 26);
                printf("Dibatalkan!               ");
                getch();
                return;
            }

            // ENTER
            if (ch == 13) {
                // Validasi: cek apakah kosong
                if (idx == 0) {
                    gotoxy(3, 26);
                    printf("Angka tidak boleh kosong!");
                    Sleep(1500);
                    gotoxy(3, 26);
                    printf("                          ");
                    break;  // Keluar inner loop, ulangi input
                }

                buffer[idx] = '\0';
                targetNo = atoi(buffer);
                break;  // Keluar inner loop dengan nilai valid
            }

            // BACKSPACE
            if (ch == 8 && idx > 0) {
                idx--;
                buffer[idx] = '\0';
                gotoxy(20, 25);
                printf("          ");  // Hapus tampilan
                gotoxy(20, 25);
                printf("%s", buffer);  // Tampil ulang
            }

            // ANGKA 0-9
            if (ch >= '0' && ch <= '9') {
                if (idx < 9) {
                    buffer[idx++] = ch;
                    buffer[idx] = '\0';
                    printf("%c", ch);
                }
            }
        }

        // Jika input kosong, continue (ulangi dari awal)
        if (idx == 0) continue;

        // Validasi: nomor harus dalam range
        if (targetNo >= 1 && targetNo <= count) break;

        // Jika nomor tidak valid
        gotoxy(3, 26);
        printf("Nomor Urut %d Tidak Ditemukan", targetNo);
        Sleep(1500);
        gotoxy(3, 26);
        printf("                                ");
    }

    // ===== BUKA FILE UNTUK UPDATE =====
    fp   = fopen("rute.dat", "rb");
    temp = fopen("temp.dat", "wb");
    if (!fp || !temp) return;

    // ================= PROSES UPDATE =================
    while (fread(&data, sizeof(Rute), 1, fp)) {

        if (currentNo == targetNo) {
            found = 1;

            // Simpan data asli untuk fallback
            Rute dataAsli = data;

            // ========= DATA LAMA =========
            bentukframe(37, 29, 45, 15);
            gotoxy(55, 30); printf("DATA LAMA");

            gotoxy(39, 32); printf("Kota Asal    : %s", data.kotaAsal);
            gotoxy(39, 33); printf("Kota Tujuan  : %s", data.kotaTujuan);

            char hargaStr[30];
            formatHarga(data.harga, hargaStr);
            gotoxy(39, 34); printf("Harga        : %s", hargaStr);
            gotoxy(39, 35); printf("Berangkat    : %s", data.jamBerangkat);
            gotoxy(39, 36); printf("Tiba         : %s", data.jamTiba);
            gotoxy(39, 37); printf("status       : %s", data.status);
            gotoxy(39, 38); printf("durasi       : %s", data.durasi);

            // ========= DATA BARU =========
            renderDataBaru(data);

            int selectedField = 0;
            int totalFields = 6;
            int editing = 1;

            while (editing) {

                // Penanda >>
                for (int i = 0; i <= totalFields; i++) {
                    int row = 32 + i;
                    if (i == 6) row = 40;

                    gotoxy(88, row);
                    printf(i == selectedField ? ">>" : "  ");
                }

                int ch = _getch();

                // ESC → batal
                if (ch == 27) {
                    fclose(fp);
                    fclose(temp);
                    remove("temp.dat");
                    return;
                }

                // Arrow key
                if (ch == 0 || ch == 224) {
                    ch = _getch();
                    if (ch == 72)
                        selectedField = (selectedField - 1 + totalFields + 1) % (totalFields + 1);
                    if (ch == 80)
                        selectedField = (selectedField + 1) % (totalFields + 1);
                }
                // ENTER
    else if (ch == 13) {
    int inputX = 105;

    switch (selectedField) {
case 0: // Kota Asal
    clearArea(85, 29, 55, 15);

    char tempKotaAsal[50] = ""; // Inisialisasi kosong agar tidak bawa data lama
    // Jangan di-copy dari data.kotaAsal jika tujuannya input baru murni

    pilihKota(tempKotaAsal);

    if (strlen(tempKotaAsal) > 0) {
        strcpy(data.kotaAsal, tempKotaAsal);

        // Render sisa informasi (Harga, Jam, dll)
        renderDataBaru(data);

        // Tampilkan hanya kota yang sudah terisi
        clearArea(105, 32, 30, 2);
        gotoxy(105, 32);
        printf("%s", data.kotaAsal);

        // Kota Tujuan HANYA tampil jika sudah diisi (bukan data lama)
        if (strlen(data.kotaTujuan) > 0) {
            gotoxy(105, 33);
            printf("%s", data.kotaTujuan);
        }
    }
    break;

case 1: // Kota Tujuan
    clearArea(85, 29, 55, 15);

    char tempKotaTujuan[50] = ""; // Inisialisasi kosong
    int validTujuan = 0;

    do {
        pilihKota(tempKotaTujuan);

        if (strlen(tempKotaTujuan) == 0) {
            validTujuan = 1;
            break;
        }

        // Validasi agar tidak sama dengan kota asal
        if (strlen(data.kotaAsal) > 0 && strcmp(data.kotaAsal, tempKotaTujuan) == 0) {
            bentukframe(85, 29, 55, 6);
            gotoxy(95, 32);
            printf("Kota tujuan tidak boleh sama");
            gotoxy(95, 33);
            printf("dengan kota asal!");
            Sleep(1500);
            clearArea(85, 29, 55, 6);
            tempKotaTujuan[0] = '\0'; // Reset temp
            continue;
        }

        validTujuan = 1;
        break;
    } while (1);

    if (validTujuan && strlen(tempKotaTujuan) > 0) {
        strcpy(data.kotaTujuan, tempKotaTujuan);

        renderDataBaru(data);

        clearArea(105, 32, 30, 2);
        if (strlen(data.kotaAsal) > 0) {
            gotoxy(105, 32);
            printf("%s", data.kotaAsal);
        }
        gotoxy(105, 33);
        printf("%s", data.kotaTujuan);
    }
    break;

    case 2: // Harga
        long tempHarga = data.harga;
        int hargaBerubah = 0;

        do {
            clearArea(inputX, 34, 25, 1);
            gotoxy(inputX, 34);

            int escPressed = 0;
            tempHarga = inputangka7digit(inputX, 34, &escPressed);

            if (escPressed) {
                // Jika ESC ditekan, batalkan dan jangan ubah data
                tempHarga = data.harga;
                hargaBerubah = 0;
                break;
            }

            if (tempHarga == 0) {
                gotoxy(inputX, 41);
                printf("Harga tidak boleh 0!");
                Sleep(1500);
                gotoxy(inputX, 41);
                printf("                      ");

                tempHarga = data.harga;
                continue;
            }

            hargaBerubah = 1;
            break;
        } while (1);

        // Hanya update dan tampilkan jika ada perubahan
        if (hargaBerubah) {
            data.harga = tempHarga;

            clearArea(inputX, 34, 25, 1);
            gotoxy(inputX, 34);
            tampilanhargatiket(data.harga);
        } else {
            // Jika dibatalkan, clear area tapi jangan tampilkan apa-apa
            clearArea(inputX, 34, 25, 1);
        }
        break;

    case 3: // Jam Berangkat
        clearArea(inputX, 35, 15, 1);
        gotoxy(inputX, 35);

        char tempJamBerangkat[10];
        strcpy(tempJamBerangkat, data.jamBerangkat);

        inputJam(tempJamBerangkat);

        if (strlen(tempJamBerangkat) > 0) {
            strcpy(data.jamBerangkat, tempJamBerangkat);

            if (strlen(data.jamBerangkat) > 0 && strlen(data.jamTiba) > 0) {
                hitungDurasi(data.jamBerangkat, data.jamTiba, data.durasi);
                clearArea(105, 37, 20, 1);
                gotoxy(105, 38);
                printf("%s", data.durasi);
            }

            clearArea(inputX, 35, 15, 1);
            gotoxy(inputX, 35);
            printf("%s", data.jamBerangkat);
        }
        // TIDAK ADA tampilan ulang jika dibatalkan
        break;

    case 4: // Jam Tiba
        clearArea(inputX, 36, 15, 1);
        gotoxy(inputX, 36);

        char tempJamTiba[10];
        strcpy(tempJamTiba, data.jamTiba);

        inputJam(tempJamTiba);

        if (strlen(tempJamTiba) > 0) {
            strcpy(data.jamTiba, tempJamTiba);

            if (strlen(data.jamBerangkat) > 0 && strlen(data.jamTiba) > 0) {
                hitungDurasi(data.jamBerangkat, data.jamTiba, data.durasi);
                clearArea(105, 37, 20, 1);
                gotoxy(105, 38);
                printf("%s", data.durasi);
            }

            clearArea(inputX, 36, 15, 1);
            gotoxy(inputX, 36);
            printf("%s", data.jamTiba);
        }
        // TIDAK ADA tampilan ulang jika dibatalkan
        break;

    case 5: // Status
        clearArea(inputX, 37, 20, 1);

        char tempStatus[10];
        strcpy(tempStatus, data.status);

        inputStatus(tempStatus, 99, 37);

        if (strlen(tempStatus) > 0) {
            strcpy(data.status, tempStatus);
            clearArea(inputX, 37, 20, 1);
            gotoxy(inputX, 37);
            printf("%s", data.status);
        }
        break;

    case 6: // SIMPAN (sebelumnya case 5)
        editing = 0;
        break;
    }
    }
            }

            fwrite(&data, sizeof(Rute), 1, temp);
        }
        else {
            fwrite(&data, sizeof(Rute), 1, temp);
        }

        currentNo++;
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("rute.dat");
        rename("temp.dat", "rute.dat");
        gotoxy(40, 42); printf("Rute berhasil diperbarui!");
    } else {
        remove("temp.dat");
        gotoxy(3, 27); printf("Nomor rute tidak ditemukan!");
    }

    getch();
}

#endif // PROJEK_UPDATERUTE_