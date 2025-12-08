#include "login.h"
#include "FrameTabel.h"

int main() {
    system("color 91");
    trueFullscreen();
    Sleep(100);
    disableScroll();
    forceHideScrollbar();
    validLogin();
    return 0;
}
