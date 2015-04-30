#ifndef _MENUWINDOW_H__
#define _MENUWINDOW_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include <vector>
#include "Button.h"
#include "WindowMP.h"
#include "TableWindow.h"
#include "Symbol.h"
#include "BotsChoice.h"
#include "TypeChoice.h"
#include "FireAnimationWhist.h"
#include "SimpleAnimationWhist.h"

class MenuWindow
{
    public:
        MenuWindow(const char* pathBackground, const char* pathIcon,
                   unsigned int width, unsigned int height);
        virtual~ MenuWindow();
        void ShowMenuWindow();
        void Event();
        void SetBackground();
        void ClickExitButton();
        void LeftClick(int x, int y);
        void Select(SDL_Surface* screen);
        int MovingRight();
        int MovingDown();
        int MovingLeft();
        int MovingUp();
        int Draw();
        int Animation();
        int GetPosTableWindow(int id) const;
        int GetWindowID();

    private:
        bool TableWindowsOpened() const;
        bool Windows() const;
        bool closed = false, animationDone = false, activatePlay = false;
        bool activateBack = false, simpleAnimationWhistDone = false;
        int mouseX, mouseY, menuWindowID = -1, mode = 0, id = 2;
        SDL_Event event;
        SDL_sem *sem;
        SDL_Thread *threadAnimation, *threadMoving, *threadDraw, *threadMoving2;
        SDL_Window *menuWindow;
        FireAnimationWhist *fireAnimationWhist;
        SimpleAnimationWhist *simpleAnimationWhist;
        std::vector<Symbol*> symbols;
        SDL_Surface *icon, *background;
        int width, height;
        WindowMP* windowMP = NULL;
        std::vector<TableWindow*> tables;

        // for mode 1
        Button *start, *back;
        BotsChoice *botsChoice;
        TypeChoice *typeChoice;

        // for mode 0
        std::vector<Button*> buttons;
};

#endif

