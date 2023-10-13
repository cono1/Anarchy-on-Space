#include <iostream>

#include <raylib.h>

#include "Ship/ship.h"
#include "Asteriods/asteroids.h"
#include "Bullets/bullets.h"

using namespace game;

enum Screens{MENU, INGAME};

int main()
{
    InitWindow(1024, 768, "Asteroids");

    const int maxBullets = 5;
    const int bigAsteroidsMax = 5;

    Bullet bullet[maxBullets];
    Ship ship;
    Asteroid bigAsteroids[bigAsteroidsMax];

    Screens screen = INGAME;

    SetRandomSeed(static_cast<unsigned int>(time(NULL)));

    //Init-------
    initShip(ship);

    for (int i = 0; i < maxBullets; i++)
        initBullet(bullet[i], ship.pos, ship.texture.width, ship.texture.height);   

    for (int i = 0; i < bigAsteroidsMax; i++)
        initAsteroid(bigAsteroids[i], BIG);
    //-----------
   

    // Loop
    while (!WindowShouldClose())
    {
        switch (screen)
        {
        case MENU:
            break;
        case INGAME:
            //Update----
            updateShip(ship);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
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
            }
            
            //------

            //Drawing----
            BeginDrawing();
            ClearBackground(WHITE);

            for (int i = 0; i < bigAsteroidsMax; i++)
                drawAsteroid(bigAsteroids[i]);

            for (int i = 0; i < maxBullets; i++)
                drawBullet(bullet[i]);
            
            drawShip(ship);
            
            EndDrawing();
            //-----
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