#include <iostream>

#include <raylib.h>

#include "Ship/ship.h"
#include "Asteriods/asteroids.h"
#include "Bullets/bullets.h"
#include "Game/collisionManager.h"
#include "Game/menu.h"

using namespace game;

int main()
{
    InitWindow(1024, 768, "Asteroids");

    int titleSize = 90;
    int optionsSize = 50;
    int pauseSize = 25;

    const int maxBullets = 5;
    const int bigAsteroidsMax = 5;
    const int medAsteroidsMax = bigAsteroidsMax * 2;
    const int smallAsteroidsMax = medAsteroidsMax * 2;

    int bigAsteroidsActive = 0;
    int medAsteroidsActive = 0;
    int smallAsteroidsActive = 0;

    Bullet bullet[maxBullets];
    Ship ship;
    Asteroid bigAsteroids[bigAsteroidsMax];
    Asteroid medAsteroids[medAsteroidsMax];
    Asteroid smallAsteroids[smallAsteroidsMax];

    SetRandomSeed(static_cast<unsigned int>(time(NULL)));

    //Init-------------------------------------------------------------------------------------------------
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
    CurrentScreen currentScreen = MENU;
    //-----------

    // Loop
    while (!WindowShouldClose())
    {
        switch (currentScreen)
        {
        case EXIT:
            return 0;
            break;
        case CREDITS:
            break;
        case RULES:
            break;
        case PLAY:
            //Update---------------------------------------------------------------------------------------
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

            for (int i = 0; i < bigAsteroidsMax; i++)
            {
                updateAsteroid(bigAsteroids[i]);

                if (checkShipToAsteroidCollision(ship, bigAsteroids[i]))
                {
                    removeShipLives(ship, 1);
                    restartShip(ship);

                    for (int j = 0; j < bigAsteroidsMax; j++)
                        restartAsteroids(bigAsteroids[j]);
                }

                for (int j = 0; j < maxBullets; j++)
                {
                    if (checkBulletToAsteroidCollision(bullet[j], bigAsteroids[i]))
                    {
                        deActivateBullet(bullet[j]);
                        bigAsteroidsActive--;

                        if (medAsteroidsActive > medAsteroidsMax)
                        {
                            medAsteroidsActive = 0;
                        }

                        activateAsteroid(medAsteroids[medAsteroidsActive], bigAsteroids[i], 1);
                        medAsteroidsActive++;
                        activateAsteroid(medAsteroids[medAsteroidsActive], bigAsteroids[i], -1);
                        medAsteroidsActive++;

                        bigAsteroids[i].active = false;

                        break;
                    }
                }

            }

            for (int i = 0; i < medAsteroidsMax; i++)
            {
                updateAsteroid(medAsteroids[i]);

                for (int j = 0; j < maxBullets; j++)
                {
                    if (checkBulletToAsteroidCollision(bullet[j], medAsteroids[i]))
                    {
                        deActivateBullet(bullet[j]);

                        if (smallAsteroidsActive > smallAsteroidsMax)
                        {
                            smallAsteroidsActive = 0;
                        }

                        activateAsteroid(smallAsteroids[smallAsteroidsActive], medAsteroids[i], 1);
                        smallAsteroidsActive++;
                        activateAsteroid(smallAsteroids[smallAsteroidsActive], medAsteroids[i], -1);
                        smallAsteroidsActive++;

                        medAsteroids[i].active = false;
                    }
                }
            }

            for (int i = 0; i < smallAsteroidsMax; i++)
            {
                updateAsteroid(smallAsteroids[i]);

                for (int j = 0; j < maxBullets; j++)
                {
                    if (checkBulletToAsteroidCollision(bullet[j], smallAsteroids[i]))
                    {
                        deActivateBullet(bullet[j]);
                        smallAsteroids[i].active = false;
                    }
                }
            }
            //------

            //Drawing--------------------------------------------------------------------------------------
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
            //-----
            break;
        case MENU:
            updateMenu(currentScreen);

            BeginDrawing();
            ClearBackground(BLACK);
            printMenu("ANARCHY ON SPACE", titleSize, optionsSize);
            EndDrawing();
            break;
        case PAUSE:
            updateMenu(currentScreen);

            BeginDrawing();
            ClearBackground(BLACK);
            printMenu("PAUSED", titleSize, optionsSize);
            EndDrawing();
            break;
        default:
            break;
        }
    }

    for (int i = 0; i < bigAsteroidsMax; i++)
        deInitAsteroid(bigAsteroids[i]);

    deInitShip(ship);
    CloseWindow();
}