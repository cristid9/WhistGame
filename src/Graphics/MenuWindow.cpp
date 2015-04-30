#include "MenuWindow.h"

MenuWindow::MenuWindow(const char* pathBackground, const char* pathIcon,
                       unsigned int width, unsigned int height)
{
    menuWindow = NULL;
    fireAnimationWhist = new FireAnimationWhist(50, 0);
    simpleAnimationWhist = NULL;
    sem = SDL_CreateSemaphore(1);
    this->width = width;
    this->height = height;
    background = IMG_Load(pathBackground);
    icon = IMG_Load(pathIcon);
}

MenuWindow::~MenuWindow()
{
    SDL_SemWait(sem);
    for (int i = 0; i < 4; i++)
        delete buttons[i];
    delete start;
    delete back;
    delete botsChoice;
    delete typeChoice;
    delete fireAnimationWhist;
    SDL_FreeSurface(icon);
    SDL_FreeSurface(background);
    for (auto symbol : symbols)
        delete symbol;
    for (auto table : tables)
        delete table;
    if (menuWindow != NULL)
    {
        SDL_DestroyWindow(menuWindow);
        menuWindow = NULL;
    }
    SDL_SemPost(sem);
    SDL_DestroySemaphore(sem);
}

int MenuWindow::Animation()
{
    SDL_Surface *screen = SDL_GetWindowSurface(menuWindow);
    int h = (height - 312) / 2 + 312;
    for (int i = 0; i < h; i += 5)
    {
        SDL_SemWait(sem);
        if (closed)
        {
            SDL_SemPost(sem);
            return 1;
        }
        for (int j = 0; j < 4; j++)
            buttons[j]->SetY(-292 + i + j * 73);
        SDL_SemPost(sem);
        SDL_Delay(10);
    }    

    animationDone = true;
    h = -120;
    simpleAnimationWhist = new SimpleAnimationWhist(screen, 50, h);
    while (h < 0)
    {
        SDL_SemWait(sem);
        if (closed)
        {
            SDL_SemPost(sem);
            return 1;
        }
        simpleAnimationWhist->SetY(h);
        h += 5;
        SDL_SemPost(sem);
        SDL_Delay(25);
    }

    delete simpleAnimationWhist;
    simpleAnimationWhistDone = true;

    symbols.push_back(new Symbol("images/trefla.png", 50, 50, menuWindow));
    symbols.push_back(new Symbol("images/diamonds.png", 50, 50, menuWindow));
    symbols.push_back(new Symbol("images/spades.png", 50, 50, menuWindow));
    symbols.push_back(new Symbol("images/hearts.png", 50, 50, menuWindow)); 

    int size = symbols.size();
    while (1)
    {
        SDL_SemWait(sem);
        if (closed)
        {
            SDL_SemPost(sem);
            return 1;
        }
        for (int i = 0; i < size; i++)
            symbols[i]->Move();
        SDL_SemPost(sem);
        SDL_Delay(75);
   }

    return 1;
}

int MenuWindow::MovingUp()
{
    int h = height + 1, h2 = (height - 272) / 2;
    while (h > h2)
    {
        SDL_SemWait(sem);
        if (closed || activatePlay)
        {
            SDL_SemPost(sem);
            return 1;
        }
        for (int i = 0; i < 4; i++)
            buttons[i]->SetY(h + i * 73);
        h -= 5;
        SDL_SemPost(sem);
        SDL_Delay(10);
    }

    return 1;
}

int MenuWindow::MovingLeft()
{
    int w = start->GetX();
    while (w > -205)
    {
        SDL_SemWait(sem);
        if (closed)
        {
            SDL_SemPost(sem);
            return 1;
        }
        start->SetX(w);
        back->SetX(w);
        botsChoice->SetX(w);
        typeChoice->SetX(w);
        w -= 5;
        SDL_SemPost(sem);
        SDL_Delay(10);
    }

    activateBack = false;
    mode = 0;
    MovingUp();

    return 1;
}

int MenuWindow::MovingRight()
{
    int w = (width - 198) / 2;
    int w2 = -199;
    while (w2 < w)
    {
        SDL_SemWait(sem);
        if (closed || activateBack)
        {
            SDL_SemPost(sem);
            return 1;
        }
        start->SetX(w2);
        back->SetX(w2);
        botsChoice->SetX(w2);
        typeChoice->SetX(w2);
        w2 += 5;
        SDL_SemPost(sem);
        SDL_Delay(10);
    }

    return 1;
}

int MenuWindow::MovingDown()
{
    int h = buttons[0]->GetY();
    while (h < height)
    {
        if (animationDone)
        {
            SDL_SemWait(sem);
            if (closed)
            {
                SDL_SemPost(sem);
                return 1;
            }
            for (int j = 0; j < 4; j++)
                buttons[j]->SetY(h + j * 73);
            h += 5;
            SDL_SemPost(sem);
        }
        SDL_Delay(10);
    }

    activatePlay = false;
    mode = 1;
    MovingRight();

    return 1;
}

void MenuWindow::ShowMenuWindow()
{
    menuWindow = SDL_CreateWindow("Whist", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_OPENGL);
    fireAnimationWhist->ChangeScreen(SDL_GetWindowSurface(menuWindow));
    SDL_SetWindowIcon(menuWindow, icon);
    menuWindowID = SDL_GetWindowID(menuWindow);
    int w = (width - 198) / 2;

    // for mode 0
    buttons.push_back(new Button("images/play.png", "images/playS.png",
                                 198, 53, w, -100));
    buttons.push_back(new Button("images/mp.png", "images/mpS.png",
                                 198, 53, w, -100));
    buttons.push_back(new Button("images/rules.png", "images/rulesS.png",
                                 198, 53, w, -100));
    buttons.push_back(new Button("images/exit.png", "images/exitS.png",
                                 198, 53, w, -100));

    // for mode 1
    int h = (height - 222) / 2;
    botsChoice = new BotsChoice(SDL_GetWindowSurface(menuWindow), -199, h);
    typeChoice = new TypeChoice(SDL_GetWindowSurface(menuWindow), -199, h + 48);
    start = new Button("images/start.png", "images/startS.png",
                       198, 53, -199, h + 96);
    back = new Button("images/back.png", "images/backS.png",
                      198, 53, -199, h + 169);

    threadDraw = SDL_CreateThread([] (void* menu) { return ((MenuWindow*)menu)->Draw();}, NULL, this);
    threadAnimation = SDL_CreateThread([] (void* menu) { return ((MenuWindow*)menu)->Animation();}, NULL, this);
    Event();
}

void MenuWindow::SetBackground()
{
    SDL_SemWait(sem);
    SDL_Surface *screen = SDL_GetWindowSurface(menuWindow);
    SDL_BlitSurface(background, 0, screen, 0);
    SDL_UpdateWindowSurface(menuWindow);
    SDL_SemPost(sem);
}

void MenuWindow::LeftClick(int x, int y)
{
    if (mode == 0)
    {
        if (buttons[0]->Clicked(x, y) && !activatePlay)
        {
            activatePlay = true;
            SDL_SemPost(sem);
            threadMoving = SDL_CreateThread([] (void* menu) { return ((MenuWindow*)menu)->MovingDown();}, NULL, this);
            SDL_SemWait(sem);
            return;
        }
    }

    if (mode == 1)
    {
        if (botsChoice->Clicked(x, y))
        {
            typeChoice->Clicked(-1, -1);
            return;
        }

        if (typeChoice->Clicked(x, y))
            return;

        if (start->Clicked(x, y))
        {
            tables.push_back(new TableWindow(botsChoice->GetBots(),
                                             typeChoice->GetType()));
            id = tables[tables.size() - 1]->GetWindowId();
        }

        if (back->Clicked(x, y))
        {
            activateBack = true;
            SDL_SemPost(sem);
            threadMoving2 = SDL_CreateThread([] (void* menu) { return ((MenuWindow*)menu)->MovingLeft();}, NULL, this);
            SDL_SemWait(sem);
            return;
        }
    }
}

bool MenuWindow::TableWindowsOpened() const
{
    for (auto i = 0u; i <tables.size(); i++)
        if (!tables[i]->isClosed())
            return true;

    return false;
}

bool MenuWindow::Windows() const
{
    bool result = TableWindowsOpened();
    if (menuWindow == NULL && windowMP == NULL && !result)
        return false;

    return true;
}

int MenuWindow::GetPosTableWindow(int id) const
{
    for (auto i = 0u; i < tables.size(); i++)
        if (tables[i]->GetWindowId() == id)
            return i;

    return -1;
}

int MenuWindow::GetWindowID()
{
    return menuWindowID;
}

void MenuWindow::ClickExitButton()
{
    if (menuWindow != NULL)
    {
        SDL_DestroyWindow(SDL_GetWindowFromID(event.window.windowID));
        menuWindow = NULL;
        menuWindowID = -1;
        closed = true;
    }
}

int MenuWindow::Draw()
{
    SDL_Surface* screen = SDL_GetWindowSurface(menuWindow);

    while (1)
    {
        SDL_SemWait(sem);
        if (closed)
        {
            SDL_SemPost(sem);
            return 1;
        }
        SDL_BlitSurface(background, 0, screen, 0);
        for (auto symbol : symbols)
            symbol->Show(screen);
        Select(screen);
        typeChoice->Show();
        botsChoice->Show();
        if (simpleAnimationWhistDone)
            fireAnimationWhist->ShowFireAnimation();
        else
            if (simpleAnimationWhist != NULL)
                simpleAnimationWhist->ShowSimpleAnimation();
        SDL_UpdateWindowSurface(menuWindow);
        SDL_SemPost(sem);
        SDL_Delay(25);
    }

    return 1;
}

void MenuWindow::Select(SDL_Surface* screen)
{
    if (mode == 0)
        for (int i = 0; i < 4; i++)
        {
            buttons[i]->Selected(screen, mouseX, mouseY);
            buttons[i]->ShowButton(screen);
        }
    else
    {
        if (botsChoice->Selected(mouseX, mouseY) ||
            typeChoice->Selected(mouseX, mouseY))
        {
            
            start->Selected(screen, -1, -1);
            back->Selected(screen, -1, -1);
        }
        else
        {
            start->Selected(screen, mouseX, mouseY);
            back->Selected(screen, mouseX, mouseY);
        }
        start->ShowButton(screen);
        back->ShowButton(screen);
    }
}

void MenuWindow::Event()
{
    while (SDL_WaitEvent(&event) >= 0)
    {
        SDL_SemWait(sem);
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
            {
                id = event.window.windowID;
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (id == menuWindowID)
                    {
                        if (buttons[3]->Clicked(event.button.x, event.button.y))
                        {
                            ClickExitButton();
                            if (!Windows())
                            {
                                SDL_SemPost(sem);
                                return;
                            }
                            break;
                        }
                        LeftClick(event.button.x, event.button.y);
                        break;
                    }
                    int pos = GetPosTableWindow(id);
                    if (pos != -1)
                    {
                        tables[pos]->LeftClick(event.button.x, event.button.y);
                        break;
                    }
                }
                break;
            }
            case SDL_MOUSEMOTION:
            {
                id = event.window.windowID;
                if (id == menuWindowID)
                {
                    mouseX = event.motion.x;
                    mouseY = event.motion.y;
                    break;
                }
                int pos = GetPosTableWindow(id);
                if (pos != -1)
                {
                    tables[pos]->SetMouseX(event.motion.x);
                    tables[pos]->SetMouseY(event.motion.y);
                    break;
                }
                break;
            }
            case SDL_KEYDOWN:
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    if (id == menuWindowID)
                    {
                        ClickExitButton();
                        break;
                    }
                    if (windowMP != NULL)
                        if (id == windowMP->windowID)
                        {
                            delete windowMP;
                            break;
                        }
                    int pos = GetPosTableWindow(id);
                    if (pos != -1)
                    {
                        delete tables[pos];
                        tables.erase(tables.begin() + pos);
                        break;
                    }
                    if (!Windows())
                    {
                        SDL_SemPost(sem);
                        return;
                    }
                    break;
                }
                break;
            }
            case SDL_WINDOWEVENT:
            {
                id = event.window.windowID;
                if (event.window.event == SDL_WINDOWEVENT_SHOWN)
                {
                    for (unsigned int i = 0; i < tables.size(); i++)
                        if (id == tables[i]->GetScoreWindowID())
                            tables[i]->DrawScore();
                }

                if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
                {
                    id = event.window.windowID;
                    break;
                }
                if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    if (id == menuWindowID)
                        ClickExitButton();
                    if (windowMP != NULL)
                        if (id == windowMP->windowID)
                            delete windowMP;
                    int pos = GetPosTableWindow(id);
                    if (pos != -1)
                    {
                        tables[pos]->Exit();
                        //delete tables[pos];
                        //tables.erase(tables.begin() + pos);
                    }
                    for (unsigned int i = 0; i < tables.size(); i++)
                        if (id == tables[i]->GetScoreWindowID())
                            tables[i]->ExitScore();
                    if (!Windows())
                    {
                        SDL_SemPost(sem);
                        return;
                    }
                    break;
                }
                break;
            }
        }
        SDL_SemPost(sem);
    }
}

