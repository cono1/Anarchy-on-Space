#include <iostream>

#include "raylib.h"

#include "Ship/ship.h"
#include "Asteriods/asteroids.h"
#include "Bullets/bullets.h"

using namespace game;

enum Screens{MENU, INGAME};

int main()
{
    InitWindow(1024, 768, "Asteroids");

    const int maxBullets = 5;

    Bullet bullet[maxBullets];
    Ship ship;
    Asteroid bigAsteroid;

    Screens screen = INGAME;

    //Init-------
    initShip(ship);
    for (int i = 0; i < maxBullets; i++)
        initBullet(bullet[i], ship.pos, ship.texture.width, ship.texture.height);   
    initAsteroid(bigAsteroid, BIG);
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
            
            //------

            //Drawing----
            BeginDrawing();
            ClearBackground(WHITE);

            drawAsteroid(bigAsteroid, BIG);
            drawShip(ship);
            for (int i = 0; i < maxBullets; i++)
                drawBullet(bullet[i]);
            

            EndDrawing();
            //-----
            break;
        default:
            break;
        }

    }

    deInitAsteroid(bigAsteroid);
    deInitShip(ship);
    CloseWindow();
}