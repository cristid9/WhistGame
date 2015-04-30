#include "MenuWindow.h"

using namespace std;

#ifdef WIN32
#include <windows.h>
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char** argv)
#endif
{
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    MenuWindow menu("images/background.png", "images/logo_game.png", 400, 600);
    menu.ShowMenuWindow();

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}

