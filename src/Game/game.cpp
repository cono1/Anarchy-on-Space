#include "game.h"

#include <iostream>

#include <raylib.h>

#include "Ship/ship.h"
#include "Asteriods/asteroids.h"
#include "Bullets/bullets.h"
#include "Game/collisionManager.h"
#include "Game/menu.h"
#include "Player/player.h"

namespace game
{
void init();
void loopScreens();
void updateGame();
void updateAsteroidsStatus(Asteroid baseAsteroids[], int baseAsteroidsMax, int& baseAsteroidsActive,                                                  
                           Asteroid nextAsteroids[], int nextAsteroidsMax, int& nextAsteroidsActive);
void updateAsteroidsStatus(Asteroid asteroids[], const int maxAsteroids, int& asteroidsActive);
void updatePlayerStatus();
void drawGame();
void drawMenu(std::string title, std::string firstOption);
void deinit();

bool runGame = true;

static int titleSize = 90;
static int optionsSize = 50;
static int pauseSize = 25;
static float textSize = 50;
static Color textColor = MAGENTA;
static Vector2 scoreTextPos;
static Vector2 hpTextPos;

static const int maxBullets = 5;
static const int bigAsteroidsMax = 4;
static const int medAsteroidsMax = bigAsteroidsMax * 2;
static const int smallAsteroidsMax = medAsteroidsMax * 2;

static int bigAsteroidsActive = 0;
static int medAsteroidsActive = 0;
static int smallAsteroidsActive = 0;

static Bullet bullet[maxBullets];
static Ship ship;
static Asteroid bigAsteroids[bigAsteroidsMax];
static Asteroid medAsteroids[medAsteroidsMax];
static Asteroid smallAsteroids[smallAsteroidsMax];
static Player player;
static CurrentScreen currentScreen = MENU;

Font font;
        
void loop()
{
    init();
    loopScreens();
    deinit();
}

void init()
{
    InitWindow(1024, 768, "Anarchy on space");

    font = LoadFontEx("res/BebasNeue-Regular.ttf", 150, 0, 550);
    scoreTextPos.x = static_cast<float>(GetScreenWidth()) - (MeasureTextEx(font, "SCORE: 00000", textSize, 0).x);
    scoreTextPos.y = 10;
    hpTextPos.x = static_cast<float>(GetScreenWidth()) - (MeasureTextEx(font, "LIVES: 00", textSize, 0).x);
    hpTextPos.y = scoreTextPos.y + MeasureTextEx(font, "LIVES: 00", textSize, 0).y;

    initPlayer(player);
    initShip(ship);

    for (int i = 0; i < maxBullets; i++)
        initBullet(bullet[i], ship.pos, ship.texture.width, ship.texture.height);

    for (int i = 0; i < bigAsteroidsMax; i++)
    {
        initAsteroid(bigAsteroids[i], BIG);
        bigAsteroidsActive++;
    }

    for (int i = 0; i < medAsteroidsMax; i++)
        initAsteroid(medAsteroids[i], MEDIUM);

    for (int i = 0; i < smallAsteroidsMax; i++)
        initAsteroid(smallAsteroids[i], SMALL);

    initMenu(GetScreenWidth());

    SetRandomSeed(static_cast<unsigned int>(time(NULL)));
}

void loopScreens()
{
    while (!WindowShouldClose() && runGame)
    {
        switch (currentScreen)
        {
        case EXIT:
            runGame = false;
            break;
        case CREDITS:
            break;
        case RULES:
            break;
        case PLAY:
            updateGame();
            drawGame();
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

void updateGame()
{
    bool playAgain = false;

    if (ship.isAlive && !player.won)
    {
        if (isPausePressed() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentScreen = PAUSE;
        }

        updatePlayerStatus();

        updateShip(ship);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !isPausePressed())
        {
            for (int i = 0; i < maxBullets; i++)
            {
                if (!bullet[i].active)
                {
                    activateBullet(bullet[i], ship.pos, ship.texture.width, ship.texture.height);
                    break;
                }
            }
        }

        for (int i = 0; i < maxBullets; i++)
            updateBullet(bullet[i]);

        updateAsteroidsStatus(bigAsteroids, bigAsteroidsMax, bigAsteroidsActive,
            medAsteroids, medAsteroidsMax, medAsteroidsActive);
        updateAsteroidsStatus(medAsteroids, medAsteroidsMax, medAsteroidsActive,
            smallAsteroids, smallAsteroidsMax, smallAsteroidsActive);
        updateAsteroidsStatus(smallAsteroids, smallAsteroidsMax, smallAsteroidsActive);
    }
    
    if (!ship.isAlive || player.won)
    {
        updateMenu(currentScreen, playAgain);
        if (playAgain)
        {
            runGame = true;
            for (int i = 0; i < bigAsteroidsMax; i++)
            {
                bigAsteroids[i].active = true;
                restartAsteroids(bigAsteroids[i]);
            }

            for (int i = 0; i < medAsteroidsMax; i++)
            {
                medAsteroids[i].active = false;

            }

            for (int i = 0; i < smallAsteroidsMax; i++)
            {
                smallAsteroids[i].active = false;

            }

            for (int j = 0; j < maxBullets; j++)
            {
                deActivateBullet(bullet[j]);
            }

            restartShip(ship);
            ship.lives = ship.maxLives;
            resetPlayer(player);
        }
        playAgain = false;
    }  
}

void updateAsteroidsStatus(Asteroid baseAsteroids[], int baseAsteroidsMax, int& baseAsteroidsActive,
                           Asteroid nextAsteroids[], int nextAsteroidsMax, int& nextAsteroidsActive)
{
    for (int i = 0; i < baseAsteroidsMax; i++)
    {
        updateAsteroid(baseAsteroids[i]);

        if (checkShipToAsteroidCollision(ship, baseAsteroids[i]))
        {
            removeShipLives(ship, 1);
            std::cout << ship.lives << ": vidas";
            restartShip(ship);

            for (int j = 0; j < baseAsteroidsMax; j++)
                restartAsteroids(baseAsteroids[j]);
        }

        for (int j = 0; j < maxBullets; j++)
        {
            if (checkBulletToAsteroidCollision(bullet[j], baseAsteroids[i]))
            {
                deActivateBullet(bullet[j]);
                baseAsteroidsActive--;

                if (nextAsteroidsActive > nextAsteroidsMax)               
                    nextAsteroidsActive = 0;
                
                activateAsteroid(nextAsteroids[nextAsteroidsActive], baseAsteroids[i], 1);
                nextAsteroidsActive++;
                activateAsteroid(nextAsteroids[nextAsteroidsActive], baseAsteroids[i], -1);
                nextAsteroidsActive++;

                addScore(player, baseAsteroids[i].points);
                baseAsteroids[i].active = false;
            }
        }
    }
}

void updateAsteroidsStatus(Asteroid asteroids[], const int maxAsteroids, int& asteroidsActive)
{
    for (int i = 0; i < maxAsteroids; i++)
    {
        updateAsteroid(asteroids[i]);

        if (checkShipToAsteroidCollision(ship, asteroids[i]))
        {
            removeShipLives(ship, 1);
            restartShip(ship);

            for (int j = 0; j < maxAsteroids; j++)
                restartAsteroids(asteroids[j]);
        }

        for (int j = 0; j < maxBullets; j++)
        {
            if (checkBulletToAsteroidCollision(bullet[j], asteroids[i]))
            {
                deActivateBullet(bullet[j]);
                asteroidsActive--;
                addScore(player, asteroids[i].points);
                asteroids[i].active = false;
            }
        }
    }
}

void updatePlayerStatus()
{
    if (player.score >= player.maxScore)
        player.won = true;

    if (ship.lives <= 0)
        player.won = false;
}

void drawGame()
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (ship.isAlive && !player.won)
    {
        for (int i = 0; i < bigAsteroidsMax; i++)
            drawAsteroid(bigAsteroids[i]);

        for (int i = 0; i < medAsteroidsMax; i++)
            drawAsteroid(medAsteroids[i]);

        for (int i = 0; i < smallAsteroidsMax; i++)
            drawAsteroid(smallAsteroids[i]);

        for (int i = 0; i < maxBullets; i++)
            drawBullet(bullet[i]);

        drawShip(ship);

        printBackButton(true, pauseSize);
    }

    DrawTextEx(font, TextFormat("SCORE: %i", player.score), scoreTextPos, textSize, 0, textColor);
    DrawTextEx(font, TextFormat("LIVES: %i", ship.lives), hpTextPos, textSize, 0, textColor);

    if (!ship.isAlive || player.won)
    {
        if (player.won)      
            printMenu("Congrats!! You won", "PLAY AGAIN", titleSize, optionsSize);
        
        else
            printMenu("You lost :c", "PLAY AGAIN", titleSize, optionsSize);
    }

    EndDrawing();
}

void drawMenu(std::string title, std::string firstOption)
{
    BeginDrawing();
    ClearBackground(BLACK);
    printMenu(title, firstOption, titleSize, optionsSize);
    EndDrawing();
}

void deinit()
{
    UnloadFont(font);
    for (int i = 0; i < bigAsteroidsMax; i++)
        deInitAsteroid(bigAsteroids[i]);

    deInitShip(ship);
    CloseWindow();
}
}