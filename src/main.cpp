#include <iostream>

#include "raylib.h"

#include "Ship/ship.h"
#include "Asteriods/asteroids.h"

using namespace game;

enum Screens{MENU, INGAME};

int main()
{
    // Inicialización
    InitWindow(1024, 768, "Asteroids");

    Ship ship;
    Asteroid bigAsteroid;

    Screens screen = INGAME;

    initAsteroid(bigAsteroid, BIG);
    initShip(ship);

    // Loop
    while (!WindowShouldClose())
    {
        switch (screen)
        {
        case MENU:
            break;
        case INGAME:
            BeginDrawing();
            ClearBackground(WHITE);

            drawAsteroid(bigAsteroid, BIG);
            drawShip(ship);

            EndDrawing();
            break;
        default:
            break;
        }

    }

    deInitAsteroid(bigAsteroid);
    deInitShip(ship);
    CloseWindow();
}