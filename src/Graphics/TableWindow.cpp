#include "TableWindow.h"

using namespace std;

#define WAIT SDL_SemPost(sem); \
             SDL_Delay(1000); \
             SDL_SemWait(sem);

#define CLOSE if (game == NULL) \
              { \
                  SDL_SemPost(sem); \
                  return 0; \
              }

TableWindow::TableWindow(int noOfBots, int type)
{
    window = SDL_CreateWindow("Whist", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 954, 686,
                              SDL_WINDOW_OPENGL);
    SDL_SetWindowIcon(window, IMG_Load("images/logo_game.png"));

    windowID = SDL_GetWindowID(window);
    screen = SDL_GetWindowSurface(window);
    sem = SDL_CreateSemaphore(1);

    start = new Button("images/Start.png", "images/StartS.png",
                       191, 47, 381, 214);
    score = new Button("images/score.png", "images/scoreS.png",
                       191, 47, 750, 20);

    background = IMG_Load("images/backgroundTable.png");
    table = IMG_Load("images/table.png");
    banner = IMG_Load("images/banner.png");

    game = game_createGame(type);

    struct Player *player = player_createPlayer("User", 1);
    playerCards = new PlayerCards(screen, player, game);
    game_addPlayer(game, &player);

    char name[8] = "Robot\0\0";
    for (int i = 0; i < noOfBots; i++)
    {
        name[5] = '0' + i + 1;
        player = player_createPlayer(name, 0);
        game_addPlayer(game, &player);
    }

    game_createAndAddRounds(game);
    game_addPlayersInAllRounds(game);

    scoreWindow = new ScoreWindow(game);
    players = new Players(window, game);
    bid = new Bid(window, game, game->players[0], 325, 150);
    cardsFromTable = new CardsFromTable(SDL_GetWindowSurface(window), game);

    thread = SDL_CreateThread([] (void *table) {return ((TableWindow*)table)->Draw();}, NULL, this);
}

TableWindow::~TableWindow()
{
    /*
    SDL_SemWait(sem);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(background);
    SDL_FreeSurface(table);
    SDL_FreeSurface(banner);
    delete scoreWindow;
    delete playerCards;
    delete score;
    delete start;
    delete players;
    delete bid;
    delete cardsFromTable;
    game_deleteGame(&game);
    SDL_SemPost(sem);
    SDL_DestroySemaphore(sem); */
}

void TableWindow::Exit()
{
    SDL_SemWait(sem);
    scoreWindow->Exit();
    SDL_DestroyWindow(window);
    SDL_FreeSurface(background);
    SDL_FreeSurface(table);
    SDL_FreeSurface(banner);
    delete scoreWindow;
    delete playerCards;
    delete score;
    delete start;
    delete players;
    delete bid;
    delete cardsFromTable;
    game_deleteGame(&game);
    SDL_SemPost(sem);
}

void TableWindow::StartRound()
{
    game->currentRound += 1;
    if (game->currentRound >= MAX_GAME_ROUNDS)
        return;
    else
        if (game->rounds[game->currentRound] == NULL)
            return;

    SDL_SemWait(sem);
    int roundId = game->currentRound;
    if (roundId > 0)
        round_copyScore(game->rounds[roundId - 1], game->rounds[roundId]);

    idFirstPlayerInHand = 0;
    noOfHands = 0;

    deck_deleteDeck(&(game->deck));
    game->deck = deck_createDeck(game->playersNumber);
    deck_shuffleDeck(game->deck);
    round_distributeDeck(game->rounds[roundId], game->deck);
    
    qsort(game->players[0]->hand, game->rounds[roundId]->roundType,
          sizeof(struct Card*), player_compareCards);

    players->UpdateScore();
    SDL_SemPost(sem);

    if (game->rounds[roundId]->players[0] == game->players[0])
    {
        players->SelectPlayer(game->players[0]);
        showBid = true;
    }
    else
    {
        idFirstRobot = 0;
        RobotsBeginToBid();
    }
}

void TableWindow::StartHand()
{
    for (int i = 0; i < MAX_GAME_PLAYERS; i++)
        players->UpdateTook(game->players[i]);

    if (noOfHands == game->rounds[game->currentRound]->roundType)
    {
        EndRound();
        return;
    }

    noOfHands++;
    struct Round *round = game->rounds[game->currentRound];
    SDL_SemWait(sem);
    round->hand = hand_createHand();
    round_addPlayersInHand(round, idFirstPlayerInHand);
    SDL_SemPost(sem);

    if (round->hand->players[0] == game->players[0])
    {
        players->SelectPlayer(game->players[0]);
        userTurn = true;
    }
    else
    {
        idFirstRobot = 0;
        RobotsBeginToGiveCards();
    }

}

int TableWindow::EndHand()
{
    players->DeselectPlayer();
    SDL_Delay(1000);
    SDL_SemWait(sem);
    if (game == NULL)
        return 0;
    struct Round *round = game->rounds[game->currentRound];
    idFirstPlayerInHand = round_getPlayerId(round, round_getPlayerWhichWonHand(round));
    round->handsNumber[idFirstPlayerInHand] += 1;
    hand_deleteHand(&(round->hand));
    SDL_SemPost(sem);
    StartHand();

    return 0;
}

int TableWindow::RobotsBeginToGiveCards()
{
    struct Round *round = game->rounds[game->currentRound];
    for (int i = idFirstRobot; i < MAX_GAME_PLAYERS; i++)
    {
        SDL_SemWait(sem);
        if (round->hand->players[i] == NULL)
        {
            SDL_SemPost(sem);
            continue;
        }
        players->SelectPlayer(round->hand->players[i]);
        if (round->hand->players[i] == game->players[0])
        {
            userTurn = true;
            SDL_SemPost(sem);
            return 0;
        }
        else
        {
            WAIT
            CLOSE
            int id = robot_getCardId(round->hand->players[i], round);
            hand_addCard(round->hand, round->hand->players[i],
                         &(round->hand->players[i]->hand[id]));
        }
        SDL_SemPost(sem);
        players->DeselectPlayer();
    }

    EndHand();

    return 0;
}

int TableWindow::RobotsBeginToBid()
{
    for (int i = idFirstRobot; i < MAX_GAME_PLAYERS; i++)
    {
        SDL_SemWait(sem);
        if (game->rounds[game->currentRound]->players[i] == NULL)
        {
            SDL_SemPost(sem);
            continue;
        }
        players->SelectPlayer(game->rounds[game->currentRound]->players[i]);
        if (game->rounds[game->currentRound]->players[i] == game->players[0])
        {
            showBid = true;
            SDL_SemPost(sem);
            return 0;
        }
        else
        {
            WAIT
            CLOSE
            int bid = robot_getBid(game->rounds[game->currentRound]->players[i],
                                   game->rounds[game->currentRound]);
            round_placeBid(game->rounds[game->currentRound],
                           game->rounds[game->currentRound]->players[i], bid);
            players->UpdateBid(game->rounds[game->currentRound]->players[i]);
            scoreWindow->DrawBid(game->rounds[game->currentRound]->players[i],
                                 game->currentRound, bid);
        }
        SDL_SemPost(sem);
        players->DeselectPlayer();
    }

    StartHand();

    return 0;
}

void TableWindow::EndRound()
{
    SDL_Delay(1000);
    SDL_SemWait(sem);
    if (game == NULL)
        return;
    struct Round *round = game->rounds[game->currentRound];
    if (round_repeatRound(round) == 1)
    {
        round_reinitializeRound(round);
        scoreWindow->DeleteBids(game->currentRound);
        players->UpdateScore();
        game->currentRound -= 1;
    }
    else
    {
        round_determinesScore(round);
        game_rewardsPlayersFromGame(game, game->currentRound);
        scoreWindow->UpdateScore(game->currentRound);
        players->UpdateScore();
    }
    SDL_SemPost(sem);
    StartRound();
}

void TableWindow::LeftClick(int x, int y)
{
    if (!started && start->Clicked(x, y))
    {
        started = true;
        StartRound();
        return;
    }

    if (started && score->Clicked(x, y) && scoreWindow->IsClosed())
    {
        scoreWindow->Show();
        return;
    }

    if (showBid)
    {
        if (!bid->Clicked(x, y))
            return;
        showBid = false;
        players->UpdateBid(game->players[0]);
        int id = round_getPlayerId(game->rounds[game->currentRound],
                                   game->players[0]);
        scoreWindow->DrawBid(game->players[0], game->currentRound,
                             game->rounds[game->currentRound]->bids[id]);
        idFirstRobot = id + 1;
        if (idFirstRobot == game->playersNumber)
        {
            StartHand();
            return;
        }

        threadBots = SDL_CreateThread([] (void *table){ return ((TableWindow*)table)->RobotsBeginToBid();}, NULL, this);
        return;
    }

    if (userTurn)
    {
        if (!playerCards->Clicked(x, y))
            return;
        userTurn = false;
        idFirstRobot = hand_getPlayerId(game->rounds[game->currentRound]->hand,
                                        game->players[0]) + 1;
        if (idFirstRobot == game->playersNumber)
        {
            threadBots = SDL_CreateThread([] (void *table){ return ((TableWindow*)table)->EndHand();}, NULL, this);
            return;
        }

        threadBots = SDL_CreateThread([] (void *table){ return ((TableWindow*)table)->RobotsBeginToGiveCards();}, NULL, this);
        return;
    }
}

int TableWindow::GetWindowId()
{
    return windowID;
}

int TableWindow::Draw()
{
    SDL_Rect dest;

    while (1)
    {
        SDL_SemWait(sem);
        CLOSE
        SDL_BlitSurface(background, 0, screen, 0);

        dest.x = 195;
        dest.y = 125;
        SDL_BlitSurface(table, 0, screen, &dest);

        dest.x = 0;
        dest.y = 536;
        SDL_BlitSurface(banner, 0, screen, &dest);

        playerCards->ShowCards();
        if (userTurn)
            playerCards->Select(mouseX, mouseY);

        if (!started)
        {
            start->Selected(screen, mouseX, mouseY);
            start->ShowButton(screen);
        }
        else if (game->currentRound < MAX_GAME_ROUNDS &&
                 game->rounds[game->currentRound] != NULL)
            cardsFromTable->DrawCards(game->rounds[game->currentRound]);

        score->Selected(screen, mouseX, mouseY);
        score->ShowButton(screen);

        players->Show();

        if (showBid)
            bid->ShowBid(mouseX, mouseY);

        SDL_UpdateWindowSurface(window);
        SDL_SemPost(sem);
        SDL_Delay(25);
    }

    return 1;
}

void TableWindow::SetMouseX(int mouseX)
{
    this->mouseX = mouseX;
}

void TableWindow::SetMouseY(int mouseY)
{
    this->mouseY = mouseY;
}

int TableWindow::GetScoreWindowID()
{
    if (scoreWindow != NULL)
        return scoreWindow->GetWindowID();

    return -1;
}

void TableWindow::ExitScore()
{
    scoreWindow->Exit();
}

void TableWindow::DrawScore()
{
    scoreWindow->Draw();
}

bool TableWindow::isClosed()
{
    return (game == NULL);
}

