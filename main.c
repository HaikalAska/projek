#include "login.h"
#include "FrameTabel.h"


int main() {
    system("color 91");
    trueFullscreen();
    Sleep(100);
        FrameYangHider(1,9,153);
        tampilanlogin("GAMBARASCI.txt", 60, 3);
        gotoxy(8,5); printf("Kelompok 5");
        gotoxy(3, 10);printf("NAVIGASI \xE2\x86\x91 \xE2\x86\x93");

    disableScroll();
    forceHideScrollbar();
    validLogin();
    return 0;
}
