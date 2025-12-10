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

void clearArea(int x, int yStart, int yEnd) {
    for (int y = yStart; y <= yEnd; y++) {
        gotoxy(x, y);
        printf("                   ");

    }
}


//=========================================================//
//==============CLEAR BAGIAN BEBERAPA TEKS DOANG=========//
void clearLine(int row, int startCol, int endCol) {
    gotoxy(startCol, row);
    for (int i = startCol; i <= endCol; i++) {
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

    while (1) {
        ch = getch();

        //ENTER
        if (ch == 13) {
            pw[i] = '\0';
            printf("\n");
            break;
        }

        //ESC
        else if (ch == 27) {  // ESC
            pw[0] = '\0';
            return;
        }

        //BACKSPACE
        else if (ch == 9) {             // TAB = toggle show/hide
            showPw = !showPw;

            // refresh tampilan
            gotoxy(row, col);
            for (int j = 0; j < i; j++) {
                printf(showPw ? "%c" : "*", pw[j]);
            }
        }
        else if (ch == 8) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if (ch == 32) {
            continue;
        }
        else {
            pw[i++] = ch;

            if (showPw)
                printf("%c", ch);
            else
                printf("*");
        }
    }
}
//=============================================//










//=====================================================//
//===================USERNAME======================//
static void Nama(char *id) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();

        if (ch == 13) {                 // ENTER
            id[i] = '\0';
            break;
        }
        else if (ch == 27) {  // ESC
            id[0] = '\0';
            return;
        }
        else if (ch == 8) {             // BACKSPACE
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if (ch == 32) {
            continue;
        }
        else {                          // INPUT NORMAL
            id[i++] = ch;
            printf("%c", ch);
        }
    }
}

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
                    display[i++] = '-';
                    printf("-");
                }
                // Auto tambah '-' setelah 2 digit kedua (MM)
                else if (i == 5) {
                    display[i++] = '-';
                    printf("-");
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
void BentukFrame(int x, int y, int width, int height) {
    gotoxy(x, y);
    printf("╔");
    for (int i = 0; i < width - 2; i++)
        printf("═");
    printf("╗");

    for (int i = 1; i < height - 1; i++) {
        gotoxy(x, y + i);
        printf("║");
        for (int j = 0; j < width - 2; j++)
            printf(" ");
        printf("║");
    }

    gotoxy(x, y + height - 1);
    printf("╚");
    for (int i = 0; i < width - 2; i++)
        printf("═");
    printf("╝");
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
static int menuNavigasi(int jumlahMenu, int startRow, int startCol) {
    int pilihan = 0;
    char ch;

    while (1) {
        for (int i = 0; i < jumlahMenu; i++) {
            gotoxy(startCol, startRow + (i * 2));

            if (i == pilihan)
                printf(">> ");
            else
                printf("   ");
        }

        ch = getch();

        if (ch == 72) {
            pilihan--;
            if (pilihan < 0)
                pilihan = jumlahMenu - 1;
        }
        else if (ch == 80) {
            pilihan++;
            if (pilihan >= jumlahMenu)
                pilihan = 0;
        }
        else if (ch == 13) {
            return pilihan + 1;
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

#endif