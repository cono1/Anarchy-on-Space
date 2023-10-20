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
void updateAsteroidsStatus(Asteroid asteroid[], const int maxAsteroids, int& baseAsteroidsActive, Asteroid nextAsteroid[], int nextAsteroidsMax, int& nextAsteroidsActive);
void updateAsteroidsStatus(Asteroid asteroids[], const int maxAsteroids, int& asteroidsActive);
void drawGame();
void drawMenu(std::string title);
void deinit();

static int titleSize = 90;
static int optionsSize = 50;
static int pauseSize = 25;

static const int maxBullets = 5;
static const int bigAsteroidsMax = 5;
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

static CurrentScreen currentScreen = MENU;
        
void loop()
{
    init();
    loopScreens();
    deinit();
}

void init()
{
    InitWindow(1024, 768, "Asteroids");

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
    while (!WindowShouldClose())
    {
        switch (currentScreen)
        {
        case EXIT:
            return;
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
            drawMenu("ANARCHY ON SPACE");
            break;
        case PAUSE:
            updateMenu(currentScreen);
            drawMenu("PAUSED");
            break;
        default:
            break;
        }
    }
}

void updateGame()
{
    if (isPausePressed() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        currentScreen = PAUSE;
    }

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

    updateAsteroidsStatus(bigAsteroids, bigAsteroidsMax, bigAsteroidsActive, medAsteroids, medAsteroidsMax, medAsteroidsActive);
    updateAsteroidsStatus(medAsteroids, medAsteroidsMax, medAsteroidsActive, smallAsteroids, smallAsteroidsMax, smallAsteroidsActive);
    updateAsteroidsStatus(smallAsteroids, smallAsteroidsMax, smallAsteroidsActive);
}

void updateAsteroidsStatus(Asteroid asteroid[], const int maxAsteroids, int& baseAsteroidsActive, Asteroid nextAsteroid[], int nextAsteroidsMax, int& nextAsteroidsActive)
{
    for (int i = 0; i < maxAsteroids; i++)
    {
        updateAsteroid(asteroid[i]);

        if (checkShipToAsteroidCollision(ship, asteroid[i]))
        {
            removeShipLives(ship, 1);
            restartShip(ship);

            for (int j = 0; j < maxAsteroids; j++)
                restartAsteroids(asteroid[j]);
        }

        for (int j = 0; j < maxBullets; j++)
        {
            if (checkBulletToAsteroidCollision(bullet[j], asteroid[i]))
            {
                deActivateBullet(bullet[j]);
                baseAsteroidsActive--;

                if (nextAsteroidsActive > nextAsteroidsMax)
                {
                    nextAsteroidsActive = 0;
                }

                activateAsteroid(nextAsteroid[nextAsteroidsActive], asteroid[i], 1);
                nextAsteroidsActive++;
                activateAsteroid(nextAsteroid[nextAsteroidsActive], asteroid[i], -1);
                nextAsteroidsActive++;

                asteroid[i].active = false;
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
                asteroids[i].active = false;
            }
        }
    }
}

void drawGame()
{
    BeginDrawing();
    ClearBackground(BLACK);

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

    EndDrawing();
}

void drawMenu(std::string title)
{
    BeginDrawing();
    ClearBackground(BLACK);
    printMenu(title, titleSize, optionsSize);
    EndDrawing();
}

void deinit()
{
    for (int i = 0; i < bigAsteroidsMax; i++)
        deInitAsteroid(bigAsteroids[i]);

    deInitShip(ship);
    CloseWindow();
}
}