#include <iostream>

#include "raylib.h"

#include "Ship/ship.h"

using namespace game;

enum Screens{MENU, INGAME};

int main()
{
    // Inicialización
    InitWindow(1024, 768, "Asteroids");

    Ship ship;
    Screens screen = INGAME;

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

            drawShip(ship);

            EndDrawing();
            break;
        default:
            break;
        }

    }
    deInitShip(ship);
    CloseWindow();
}