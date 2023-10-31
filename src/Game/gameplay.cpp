#include "gameplay.h"

#include <iostream>
#include <ctime>

#include <raylib.h>

#include "Asteroids/asteroids.h"
#include "Player/player.h"
#include "Ship/ship.h"
#include "Bullets/bullets.h"
#include "collisionManager.h"
#include "printer.h"
#include "menu.h"

namespace game
{
static const int maxBullets = 5;
static const int bigAsteroidsMax = 4;
static const int medAsteroidsMax = bigAsteroidsMax * 2;
static const int smallAsteroidsMax = medAsteroidsMax * 2;

static int bigAsteroidsActive = 0;
static int medAsteroidsActive = 0;
static int smallAsteroidsActive = 0;

static Bullet bullet[maxBullets];
static Ship ship;
static Ship enemyShip;
static Asteroid bigAsteroids[bigAsteroidsMax];
static Asteroid medAsteroids[medAsteroidsMax];
static Asteroid smallAsteroids[smallAsteroidsMax];
static Player player;

extern CurrentScreen currentScreen;
extern bool shouldRunGame;

void updateGame();
void drawGame();
void updateAsteroidsStatus(Asteroid baseAsteroids[], int baseAsteroidsMax, int& baseAsteroidsActive,
    Asteroid nextAsteroids[], int nextAsteroidsMax, int& nextAsteroidsActive);
void updateAsteroidsStatus(Asteroid asteroids[], const int maxAsteroids, int& asteroidsActive);
void updatePlayerStatus();

void initGame()
{
    SetRandomSeed(static_cast<unsigned int>(time(NULL)));
    initPlayer(player);
    initShip(ship);
    initEnemyShip(enemyShip);

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
}

void runGame()
{
    updateGame();
    drawGame();
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
        updateEnemyShip(enemyShip, ship);

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
            shouldRunGame = true;
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
            std::cout << ship.lives << ": hp";
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
        drawShip(enemyShip);

        printBackButton(true, getPauseSize());
    }

    printScore(player.score);
    printLives(ship.lives);

    if (!ship.isAlive || player.won)
    {
        if (player.won)
            printMenu("Congrats!! You won", "PLAY AGAIN", getTitleSize(), getOptionsSize());

        else
            printMenu("You lost :c", "PLAY AGAIN", getTitleSize(), getOptionsSize());
    }

    EndDrawing();
}

void deinitGame()
{
    for (int i = 0; i < bigAsteroidsMax; i++)
        deInitAsteroid(bigAsteroids[i]);

    deInitShip(ship);
    deInitShip(enemyShip);
}
}