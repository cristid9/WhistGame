#ifndef _TABLEWINDOW_H__
#define _TABLEWINDOW_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>
#include <libWhistGameAI.h>
#include "ScoreWindow.h"
#include "CardsFromTable.h"
#include "PlayerCards.h"
#include "Button.h"
#include "Bid.h"
#include "Players.h"
#include <string>
#include <thread>
#include <chrono>

class TableWindow
{
    public:
        TableWindow(int noOfBots, int type);
        virtual~ TableWindow();
        int GetWindowId();
        int Draw();
        void SetMouseX(int mouseX);
        void SetMouseY(int mouseY);
        void LeftClick(int x, int y);
        int GetScoreWindowID();
        void ExitScore();
        void DrawScore();
        void Exit();
        bool isClosed();

    private:
        void StartRound();
        void EndRound();
        void StartHand();
        int EndHand();
        int RobotsBeginToBid();
        int RobotsBeginToGiveCards();
        ScoreWindow *scoreWindow;
        PlayerCards *playerCards;
        Button *score, *start;
        Players *players;
        Bid *bid;
        bool started = false, showBid = false, userTurn = false;
        SDL_sem *sem;
        SDL_Thread *thread, *threadBots;
        SDL_Window *window;
        SDL_Surface *background, *screen, *table, *banner;
        SDL_Surface *imageTrump;
        struct Game *game;
        CardsFromTable *cardsFromTable;
        int windowID, width, height, mouseX, mouseY, idFirstRobot;
        int idFirstPlayerInHand, noOfHands;
};

#endif

