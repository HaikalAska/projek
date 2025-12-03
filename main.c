#include "login.h"
#include "Menu.h"
#include "FrameTabel.h"

int main() {
    system("color 91");
    trueFullscreen();
    Sleep(400);
    disableScroll();
    validLogin();
    tampilanMenu();
    return 0;
}
