#include "game.h"

#include <iostream>

#include <raylib.h>

#include "gameplay.h"
#include "credits.h"
#include "rules.h"
#include "menu.h"
#include "printer.h"
#include "Sound/sound.h"

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
  
    initAudio();
    SetMusicVolume(getMenuMusic(), 0.2f);
    SetMusicVolume(getGameMusic(), 0.2f);
    SetSoundVolume(getLooseHpSound(), 1.0f);
    SetSoundVolume(getButtonSound(), 0.9f);

    initPrinter();
    initMenu(GetScreenWidth());

    initGame();
}

void loopScreens()
{
    while (!WindowShouldClose() && shouldRunGame)
    {
        playMenuSound();
        UpdateMusicStream(getMenuMusic());
        switch (currentScreen)
        {
        case EXIT:
            shouldRunGame = false;
            break;
        case CREDITS:
            printCredits();
            break;
        case RULES:
            printHowToPlay();
            break;
        case PLAY:
            PauseMusicStream(getMenuMusic());
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
    deinitAudio();
    CloseWindow();
}
}