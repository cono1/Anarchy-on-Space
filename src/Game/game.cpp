#include "game.h"

#include <iostream>

#include <raylib.h>

#include "gameplay.h"
#include "menu.h"
#include "printer.h"

namespace game
{
void init();
void loopScreens();
void drawMenu(std::string title, std::string firstOption);
void deinit();

bool shouldRunGame = true;

CurrentScreen currentScreen = MENU;
        
void loop()
{
    init();
    loopScreens();
    deinit();
}

void init()
{
    InitWindow(1024, 768, "Anarchy on space");
  
    initPrinter();
    initMenu(GetScreenWidth());

    initGame();
}

void loopScreens()
{
    while (!WindowShouldClose() && shouldRunGame)
    {
        switch (currentScreen)
        {
        case EXIT:
            shouldRunGame = false;
            break;
        case CREDITS:
            break;
        case RULES:
            break;
        case PLAY:
            runGame();
            break;
        case MENU:
            updateMenu(currentScreen);
            drawMenu("ANARCHY ON SPACE", "PLAY");
            break;
        case PAUSE:
            updateMenu(currentScreen);
            drawMenu("PAUSED", "RESUME");
            break;
        default:
            break;
        }
    }
}

void drawMenu(std::string title, std::string firstOption)
{
    BeginDrawing();
    ClearBackground(BLACK);
    printMenu(title, firstOption, getTitleSize(), getOptionsSize());
    EndDrawing();
}

void deinit()
{
    deinitPrinter();
    deinitGame();
    CloseWindow();
}
}