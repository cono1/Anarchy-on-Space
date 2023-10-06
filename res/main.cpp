#include "raylib.h"

#include <iostream>

enum Screens{MENU, INGAME};

int main()
{
    // Inicialización
    InitWindow(1024, 768, "Asteroids");

    Screens screen = MENU;

    Rectangle rect;

    rect.x = GetScreenWidth() / 2;
    rect.y = GetScreenHeight() / 2;
    rect.width = 70;
    rect.height = 45;

    float posX = 320.0f;
    int posY = 400;
    int radio = 100;
    float speed = 50;

    // Loop
    while (!WindowShouldClose())
    {
        switch (screen)
        {
        case MENU:

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), rect))
            {
                screen = INGAME;
                std::cout << "CLICK\n";
            }
            
            BeginDrawing();
            ClearBackground(WHITE);

            DrawRectangle(rect.x, rect.y,rect.width, rect.height, MAGENTA);

            EndDrawing();
            break;
        case INGAME:
            // Chequeo de Input
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), rect))
            {
                screen = MENU;
            }


            if (IsKeyDown(KEY_UP))
            {
                posY -= 2 * GetFrameTime();
            }

            if (IsKeyDown(KEY_DOWN))
            {
                posY += 2000 * GetFrameTime();
            }

            if (IsKeyDown(KEY_LEFT))
                posX -= speed * GetFrameTime();

            if (IsKeyDown(KEY_RIGHT))
                posX += speed * GetFrameTime();


            // Actualización

            // Dibujado
            BeginDrawing();
            ClearBackground(WHITE);

            DrawCircle(posX, posY, radio, BLUE);
            DrawRectangle(rect.x, rect.y, rect.width, rect.height, MAGENTA);
            EndDrawing();
            break;
        default:
            break;
        }

    }
    // Cierre
    CloseWindow();
}