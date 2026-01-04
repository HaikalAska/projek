#ifndef PROJEK_FRAMETABEL_H
#define PROJEK_FRAMETABEL_H

//==================================================================//
//=====================buat nampilin ASCI nya======================//
static void tampilanlogin(char *filename, int startX, int startY) {
    FILE *f = fopen(filename, "r");
    if (!f) return;

    char line[300];
    int currentRow = 0;

    while (fgets(line, sizeof(line), f)) {
        gotoxy(startX, startY + currentRow);

        printf("%s", line);
        currentRow++;
    }

    fclose(f);
}
//===================================================================//




//==============================================//
//=============BUAT CLEARSCREEN===============//
static void clearscreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clearArea(int x, int y, int width, int height) {
    for (int i = 0; i < height; i++) {
        gotoxy(x, y + i);
        for (int j = 0; j < width; j++) {
            printf(" ");
        }
    }
}


//=========================================================//
//==============CLEAR BAGIAN BEBERAPA TEKS DOANG=========//
void clearLine(int row, int startCol, int endCol) {
    int length = endCol - startCol + 1;
    gotoxy(startCol, row);

    for (int i = 0; i < length; i++) {
        printf(" ");
    }
}





//============================================//





//======================================================================//
//==============BIAR TIAP PRINT GA HARUS (\N DAN \t)  =================//
void gotoxy(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//===================================================================//





//=================================================================//
//==============BIAR GA ADA BLANK HITAM SAAT DI RUN===============//
void fillBackground(int colorPair) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(h, &csbi);

    int width  = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    SetConsoleTextAttribute(h, colorPair);

    COORD pos = {0, 0};
    SetConsoleCursorPosition(h, pos);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf(" ");
        }
    }
    (h, pos);
}
//===============================================================//




//===============================================================================//
//==============================BIAR AUTO FULLSCREEN============================//
void trueFullscreen() {
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1C, 0, 0);
    keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}
//=============================================================================//





//=================================================//
//================BUAT DISABLE SCROLL=============//
static void disableScroll()
{
    HWND console = GetConsoleWindow();

    LONG style = GetWindowLong(console, GWL_STYLE);
    style &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
    SetWindowLong(console, GWL_STYLE, style);

    HMONITOR monitor = MonitorFromWindow(console, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = { sizeof(mi) };
    GetMonitorInfo(monitor, &mi);

    SetWindowPos(console, HWND_TOP,
        mi.rcMonitor.left,
        mi.rcMonitor.top,
        mi.rcMonitor.right - mi.rcMonitor.left,
        mi.rcMonitor.bottom - mi.rcMonitor.top,
        SWP_FRAMECHANGED | SWP_SHOWWINDOW);
}
//==================================================//




//================================================================//
//=========================SCROLLBAR GA ADA====================//
void forceHideScrollbar() {
    HWND consoleWindow = GetConsoleWindow();
    ShowScrollBar(consoleWindow, SB_BOTH, FALSE);
}
//======================================================//




void waitEsc() {
    int n;
    int ch = getch();
    if (ch == 27) return;
    else ungetc(ch, stdin);
    scanf("%d", &n);

}



//=============================================//
//==============Bagian Password===============//
    static void PWesc(char *pw, int row, int col) {
        int i = 0;
        char ch;
        int showPw = 0;

        gotoxy(col, row);

        while (1) {
            ch = getch();

            if (ch == 13) {
                pw[i] = '\0';

                if (i == 0) {
                    printf(" [Password tidak boleh kosong!]");
                    Sleep(800);

                    gotoxy(col, row);
                    printf("                               ");
                    gotoxy(col, row);
                    continue;
                }

                if (i < 5) {
                    printf(" [Minimal 5 karakter!]");
                    Sleep(800);

                    gotoxy(col, row);
                    printf("                               ");
                    gotoxy(col, row);

                    for (int j = 0; j < i; j++) {
                        if (showPw) {
                            printf("%c", pw[j]);
                        } else {
                            printf("*");
                        }
                    }

                    continue;
                }

                return;
            }
            else if (ch == 27) {
                pw[0] = '\0';
                return;
            }
            else if (ch == 9) {
                showPw = !showPw;

                int currentCol = col + i;

                gotoxy(col, row);

                for (int j = 0; j < i; j++) {
                    if (showPw) {
                        printf("%c", pw[j]);
                    } else {
                        printf("*");
                    }
                }

                for (int j = i; j < 20; j++) {
                    printf(" ");
                }

                gotoxy(currentCol, row);
                continue;
            }
            else if (ch == 8) {
                if (i > 0) {
                    i--;
                    printf("\b \b");
                }
            }
            else if (ch >= 33 && ch <= 126) {
                if (i < 49) {
                    pw[i] = ch;

                    if (showPw) {
                        printf("%c", ch);
                    } else {
                        printf("*");
                    }
                    i++;
                }
            }
        }
    }
//=============================================//



//=============================================//
//==========INPUT 7 DIGIT ANGKA================//
float inputangka7digit(int x, int y, int *isEsc) {
    char buffer[8] = ""; // 7 digit + '\0'
    int len = 0;
    char ch;

    *isEsc = 0;

    while (1) {
        ch = getch();

        // ESC ditekan
        if (ch == 27) {
            *isEsc = 1;
            return 0;
        }

        // ENTER
        if (ch == 13 && len > 0) {
            buffer[len] = '\0';
            return atof(buffer);
        }

        // BACKSPACE
        if (ch == 8 && len > 0) {
            len--;
            buffer[len] = '\0';

            gotoxy(x, y);
            printf("       "); // hapus tampilan
            gotoxy(x, y);
            printf("%s", buffer);
        }

        // ANGKA 0–9 (maks 7 digit)
        if (ch >= '0' && ch <= '9' && len < 7) {
            buffer[len++] = ch;
            buffer[len] = '\0';

            gotoxy(x, y);
            printf("%s", buffer);
        }
    }
}
//=============================================//

//=============================================//
//========TAMPILAN HARGA TIKET=================//
void tampilanhargatiket(float harga) {
    if (harga >= 1000000) {
        // 7 digit atau lebih → x.xxx.xxx
        printf("Rp%.0f.%03.0f.%03.0f,00",
               harga / 1000000,
               ((long)(harga / 1000)) % 1000,
               (long)harga % 1000);
    }
    else if (harga >= 100000) {
        // 6 digit → xxx.xxx
        printf("Rp%.0f.%03.0f,00",
               harga / 1000,
               (long)harga % 1000);
    }
    else if (harga >= 10000) {
        // 5 digit → xx.xxx
        printf("Rp%.0f.%03.0f,00",
               harga / 1000,
               (long)harga % 1000);
    }
    else {
        // cadangan (di bawah 5 digit)
        printf("Rp%.0f,00", harga);
    }
}
//=====================================================//



//===============================================================//
//==========================INPUT NO TELPON=====================//
static void inputNoTelp(char *notlpn, int x, int y) {
    int i = 0;
    char ch;
    char display[14] = "08"; // Awalan 08 + 11 digit + null terminator

    // Tampilkan awalan 08
    gotoxy(x, y);
    printf("08");
    i = 2;

    while (1) {
        ch = getch();

        if (ch == 13) {  // ENTER - Konfirmasi
            if (i == 12) {  // Hanya bisa enter jika sudah 13 digit
                display[i] = '\0';
                strcpy(notlpn, display);
                break;
            }
        }
        else if (ch == 27) {  // ESC - Batal
            notlpn[0] = '\0';
            break;
        }
        else if (ch == 8) {  // BACKSPACE - Hapus
            if (i > 2) {  // Hanya bisa hapus setelah "08"
                i--;
                printf("\b \b");
            }
        }
        else if (ch >= '0' && ch <= '9') {  // Input angka
            if (i < 12) {  // Maksimal 13 digit total
                display[i++] = ch;
                printf("%c", ch);
            }
        }
        // Abaikan input selain angka
    }
}



//=====================================================//
//========================GENDER======================//
static void inputGender(char *gender, int x, int y) {
    char ch;

    gotoxy(x, y);
    printf("L/P : ");

    while (1) {
        ch = getch();

        if (ch == 27) {  // ESC - Batal
            gender[0] = '\0';
            break;
        }
        else if (ch == 'L' || ch == 'l') {  // Input Laki-laki
            strcpy(gender, "Laki-laki");
            printf("L (Laki-laki)");

            // Tunggu konfirmasi
            while (1) {
                ch = getch();
                if (ch == 13) {  // ENTER - Konfirmasi
                    return;
                }
                else if (ch == 8) {  // BACKSPACE - Hapus dan input ulang
                    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b             ");
                    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b");
                    break;
                }
                else if (ch == 27) {  // ESC - Batal
                    gender[0] = '\0';
                    return;
                }
            }
        }
        else if (ch == 'P' || ch == 'p') {  // Input Perempuan
            strcpy(gender, "Perempuan");
            printf("P (Perempuan)");

            // Tunggu konfirmasi
            while (1) {
                ch = getch();
                if (ch == 13) {  // ENTER - Konfirmasi
                    return;
                }
                else if (ch == 8) {  // BACKSPACE - Hapus dan input ulang
                    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b             ");
                    printf("\b\b\b\b\b\b\b\b\b\b\b\b\b");
                    break;
                }
                else if (ch == 27) {  // ESC - Batal
                    gender[0] = '\0';
                    return;
                }
            }
        }
        // Abaikan input selain L/P
    }
}
//===============================================================================================//





//==============================================================================================//
//========================VALIDASI ROLE======================================================//
static void inputRole(char *role, int x, int y) {
    char ch;

    gotoxy(x, y);
    printf("S/M : ");

    while (1) {
        ch = getch();

        if (ch == 27) {  // ESC - Batal
            role[0] = '\0';
            break;
        }
        else if (ch == 'S' || ch == 's') {  // Input Staff
            strcpy(role, "Staff");
            printf("S (Staff)");

            // Tunggu konfirmasi
            while (1) {
                ch = getch();
                if (ch == 13) {  // ENTER - Konfirmasi
                    return;
                }
                else if (ch == 8) {  // BACKSPACE - Hapus dan input ulang
                    // Hapus "S (Staff)" = 9 karakter
                    for (int i = 0; i < 9; i++) printf("\b \b");
                    break;
                }
                else if (ch == 27) {  // ESC - Batal
                    role[0] = '\0';
                    return;
                }
            }
        }
        else if (ch == 'M' || ch == 'm') {  // Input Manager
            strcpy(role, "Manager");
            printf("M (Manager)");

            // Tunggu konfirmasi
            while (1) {
                ch = getch();
                if (ch == 13) {  // ENTER - Konfirmasi
                    return;
                }
                else if (ch == 8) {  // BACKSPACE - Hapus dan input ulang
                    // Hapus "M (Manager)" = 11 karakter
                    for (int i = 0; i < 11; i++) printf("\b \b");
                    break;
                }
                else if (ch == 27) {  // ESC - Batal
                    role[0] = '\0';
                    return;
                }
            }
        }
        // Abaikan input selain S/M
    }
}
//========================================================//

static void inputStatus(char *status, int x, int y) {
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








//===================================================//
//=================NAMA=============================//
static void INPUTNama(char *nama) {
    int i = 0;
    char ch;

    // Simpan posisi awal kursor
    int startX, startY;

    // Dapatkan posisi kursor saat ini (jika punya fungsi getCursorPos)
    // Jika tidak punya, kita simpan secara manual

    while (1) {
        ch = getch();

        if (ch == 13) {  // ENTER
            nama[i] = '\0';

            // Validasi: harus ada minimal 1 huruf
            int hasLetter = 0;
            for (int j = 0; j < i; j++) {
                if ((nama[j] >= 'a' && nama[j] <= 'z') ||
                    (nama[j] >= 'A' && nama[j] <= 'Z')) {
                    hasLetter = 1;
                    break;
                }
            }

            if (hasLetter && i > 0) {
                break;
            } else {

                int cursorPos = i;

                // Tampilkan peringatan
                printf(" [Nama harus mengandung huruf!]");

                Sleep(800);
                for (int k = 0; k < 31; k++) {
                    printf("\b \b");
                }
                for (int k = 0; k < cursorPos; k++) {
                    printf("%c", nama[k]);
                }
                for (int k = 0; k < cursorPos; k++) {
                }
            }
        }
        else if (ch == 27) {  // ESC
            nama[0] = '\0';
            break;
        }
        else if (ch == 8) {  // BACKSPACE
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if (ch == 32) {  // SPASI - BOLEH
            if (i < 49 && i > 0) {  // Spasi tidak boleh di awal
                // Cek karakter sebelumnya bukan spasi
                if (nama[i-1] != ' ') {
                    nama[i++] = ch;
                    printf("%c", ch);
                }
            }
        }
        else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
                 ch == '.' || ch == '-' || ch == '\'') {  // Tambah karakter valid
            if (i < 49) {
                nama[i++] = ch;
                printf("%c", ch);
            }
        }
    }
    nama[i] = '\0';
}
//======================================================================//










//POINTER
static void setPointer(int row, int col){
    printf("\033[%d;%dH", row, col);
}
//===========================================================//
//=====================TANGGAL==============================//
static void inputTanggal(char *tanggal) {
    int i = 0;
    char ch;
    char display[12] = ""; // DD-MM-YYYY + null terminator

    while (1) {
        ch = getch();

        if (ch == 13) {  // ENTER
            // Hanya bisa enter jika sudah 10 karakter (DD-MM-YYYY)
            if (i == 10) {
                display[i] = '\0';
                strcpy(tanggal, display);
                break;
            }
        }
        else if (ch == 27) {  // ESC
            tanggal[0] = '\0';
            break;
        }
        else if (ch == 8) {  // BACKSPACE
            if (i > 0) {
                i--;
                printf("\b \b");

                // Hapus tanda '-' otomatis jika backspace dari posisi setelah '-'
                if (i == 2 || i == 5) {
                    i--;
                    printf("\b \b");
                }
            }
        }
        else if (ch >= '0' && ch <= '9') {  // Hanya terima angka
            if (i < 10) {  // Maksimal 10 karakter
                // Validasi digit pertama hari (0-3)
                if (i == 0 && ch > '3') {
                    continue;  // Abaikan jika > 3
                }
                // Validasi digit kedua hari (jika digit pertama 3, hanya boleh 0-1)
                if (i == 1) {
                    int digit1 = display[0] - '0';
                    int digit2 = ch - '0';
                    int hari = digit1 * 10 + digit2;
                    if (hari < 1 || hari > 31) {
                        continue;  // Abaikan jika hari tidak valid
                    }
                }
                // Validasi digit pertama bulan (0-1)
                if (i == 3 && ch > '1') {
                    continue;  // Abaikan jika > 1
                }
                // Validasi digit kedua bulan (jika digit pertama 1, hanya boleh 0-2)
                if (i == 4) {
                    int digit1 = display[3] - '0';
                    int digit2 = ch - '0';
                    int bulan = digit1 * 10 + digit2;
                    if (bulan < 1 || bulan > 12) {
                        continue;  // Abaikan jika bulan tidak valid
                    }
                }

                display[i++] = ch;
                printf("%c", ch);

                // Auto tambah '-' setelah 2 digit pertama (DD)
                if (i == 2) {
                    display[i++] = '/';
                    printf("/");
                }
                // Auto tambah '-' setelah 2 digit kedua (MM)
                else if (i == 5) {
                    display[i++] = '/';
                    printf("/");
                }
            }
        }
        // Abaikan input selain angka
    }
}






//===============================================================//



//***********************************************************************//
//***************** INI BAGIAN FRAME HITAM NYA DOANG*********************//
//**********************************************************************//





//==================================================================//
//===========================BUAT FRAME============================//
void MoveCursor(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//==================================================================//






//==================================================================//
//================BIAR GA HARUS UTF8 (BORDER)=========================//
void printBlock(wchar_t wc) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    WriteConsoleW(h, &wc, 1, &written, NULL);
}
//===========================================================================//






//===================================================================//
//============================BENTUK FRAME============================//
void bentukframe(int posX, int posY, int width, int height) {
    SetConsoleOutputCP(65001);

    gotoxy(posX, posY);
    printf("╭");
    for (int i = 0; i < width - 2; i++)
        printf("─");
    printf("╮");

    for (int y = 1; y < height - 1; y++) {
        gotoxy(posX, posY + y);
        printf("│");
        for (int x = 0; x < width - 2; x++)
            printf(" ");
        printf("│");
    }

    gotoxy(posX, posY + height - 1);
    printf("╰");
    for (int i = 0; i < width - 2; i++)
        printf("─");
    printf("╯");
}
//===================================================================//






//====================================================================//
//=======================PRINT BORDER================================//
void printBorder(int posX, int posY, int width, int height) {
    SetConsoleOutputCP(65001);
    gotoxy(posX, posY);
    for (int i = 0; i < width; i++)
        printf("█");
    for (int y = 1; y < height - 1; y++) {
        gotoxy(posX, posY + y);
        printf("█");
        for (int x = 0; x < width - 2; x++)
            printf(" ");
        printf("█");
    }

    gotoxy(posX, posY + height - 1);
    for (int i = 0; i < width; i++)
        printf("█");
}
//===========================================================//





//=======================================================//
//======================FRAME TENGAH=====================//
void FrameYangTengah(int x, int y, int height) {
    for (int i = 0; i < height; i++) {
        MoveCursor(x, y + i);
        printBlock(L'█');
    }
}
//======================================================//




//======================================================//
//=====================FRAME HIDER=====================//
void FrameYangHider(int x, int y, int width) {
    MoveCursor(x, y);
    for (int i = 0; i < width; i++) {
        printBlock(L'█');
    }
}
//====================================================//


//============================================================//
//================ NAVIGASI ================================//
int menuNavigasi(int jumlahMenu, int startY, int spacing) {
    int pilih = 1;
    int key;

    while (1) {
        // Tampilkan highlight
        for (int i = 1; i <= jumlahMenu; i++) {
            gotoxy(3, startY + (i-1) * spacing);
            if (i == pilih) {
                printf(">> ");  // Highlight
            } else {
                printf("│ ");
            }
        }

        key = getch();

        if (key == 27) {  // ESC
            return 0;  // Return 0 untuk signal ESC
        }
        else if (key == 224) {  // Arrow keys
            key = getch();
            if (key == 72) {  // UP
                pilih--;
                if (pilih < 1) pilih = jumlahMenu;
            }
            else if (key == 80) {  // DOWN
                pilih++;
                if (pilih > jumlahMenu) pilih = 1;
            }
        }
        else if (key == 13) {  // ENTER
            return pilih;
        }
    }
}
//============================================================//



//==================================================================//
//=====================NAVIGASI KANAN KIRI=========================//
static int KAKINavigasi(int jumlahMenu, int startRow, int startCol, int spacing) {
    int pilihan = 0;
    char ch;

    while (1) {

        for (int i = 0; i < jumlahMenu; i++) {
            gotoxy(startCol + i * spacing, startRow);

            if (i == pilihan)
                printf(">>");
            else
                printf("  ");
        }

        ch = getch();
        if (ch == 0 || ch == 224) ch = getch();

        if (ch == 75) {     // kiri
            pilihan--;
            if (pilihan < 0)
                pilihan = jumlahMenu - 1;
        }
        else if (ch == 77) { // kanan
            pilihan++;
            if (pilihan >= jumlahMenu)
                pilihan = 0;
        }
        else if (ch == 13) { // enter
            return pilihan + 1;
        }
    }
}


//border show data
void tabelData(int startX, int startY, int maxId, int maxUsr, int maxPw, int rows) {

    int totalW = 4 + maxId + maxUsr + maxPw + 10;

    char line[300];
    memset(line, '=', totalW);
    line[totalW] = '\0';

    int row = startY;

    // ========== HEADER ==============
    gotoxy(startX, row); printf("%s", line); row++;

    gotoxy(startX, row);
    printf("| %-3s | %-*s | %-*s | %-*s |",
           "No",
           maxId,  "ID",
           maxUsr, "Username",
           maxPw,  "Password");
    row++;

    gotoxy(startX, row); printf("%s", line);
    row++;

    // ========== SIAPIN KOTAK ISI DATA =============
    for (int i = 0; i < rows; i++) {
        gotoxy(startX, row);
        printf("| %-3s | %-*s | %-*s | %-*s |",
               "", maxId, "", maxUsr, "", maxPw, "");
        row++;
    }

    // =========== FOOTER =============
    gotoxy(startX, row);
    printf("%s", line);
}





///////////////////////////////////////////////////////////////
//                QR CODE                                   //
//////////////////////////////////////////////////////////////
void printQRCodeFromFile(char* filename, int startX, int startY) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: File tidak ditemukan!\n");
        return;
    }

    char line[256];
    int y = 0;

    while (fgets(line, sizeof(line), file)) {
        // Hapus newline di akhir baris
        line[strcspn(line, "\n")] = 0;

        gotoxy(startX, startY + y);
        printf("%s", line);
        y++;
    }

    fclose(file);
}

#endif