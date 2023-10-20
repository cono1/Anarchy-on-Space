#include "ship.h"

#include <raymath.h>   

namespace game
{
void rotateShip(Ship& ship);
void moveShip(Ship& ship);
void checkShipLimits(Ship& ship);
void checkShipIsAlive(Ship& ship);

void initShip(Ship& ship)
{
    ship.texture = LoadTexture("res/TempShip.png");
    ship.pos.x = static_cast<float>(GetScreenWidth() / 2);
    ship.pos.y = static_cast<float>(GetScreenHeight() / 2);
    ship.dir.x = 15;
    ship.dir.y = 15;
    ship.rotation = 0;
    ship.acceleration.x = 0;
    ship.acceleration.y = 0;
    ship.radius = static_cast<float>(ship.texture.width / 2);
}

void restartShip(Ship& ship)
{
    ship.pos.x = static_cast<float>(GetScreenWidth()) / 2;
    ship.pos.y = static_cast<float>(GetScreenHeight()) / 2;
    ship.dir.x = 15;
    ship.dir.y = 15;
    ship.rotation = 0;
    ship.acceleration.x = 0;
    ship.acceleration.y = 0;
}

void updateShip(Ship& ship)
{
    rotateShip(ship);
    moveShip(ship);
    checkShipLimits(ship);
}

void drawShip(Ship ship)
{
    DrawTexturePro(ship.texture,
        { 0.0f, 0.0f, static_cast<float>(ship.texture.width), static_cast<float>(ship.texture.height) },
        { ship.pos.x, ship.pos.y, static_cast<float>(ship.texture.width), static_cast<float>(ship.texture.height) },
        { static_cast<float>(ship.texture.width / 2), static_cast<float>(ship.texture.height / 2) }, ship.rotation, WHITE);
#ifdef _DEBUG
    DrawCircleLines(static_cast<int>(ship.pos.x), static_cast<int>(ship.pos.y), ship.radius, RED);
#endif
}

void deInitShip(Ship& ship)
{
    UnloadTexture(ship.texture);
}

void addShipLives(Ship& ship, int lives)
{
    if (ship.lives - lives <= ship.maxLives)
        ship.lives += lives;
}

void removeShipLives(Ship& ship, int lives)
{
    if (ship.lives - lives >= 0)
        ship.lives -= lives;
}

void rotateShip(Ship& ship)
{
    ship.dir.x = ship.pos.x - GetMouseX();
    ship.dir.y = ship.pos.y - GetMouseY();
    float angle = (atan2f(static_cast<float>(ship.dir.y), static_cast<float>(ship.dir.x))) * 180 / PI;

    if (ship.dir.x < GetScreenWidth() / 2 && ship.dir.y < GetScreenHeight() / 2 ||
        GetMouseX() < GetScreenWidth() / 2 && GetMouseY() > GetScreenHeight() / 2) //cuadrante dos y tres
    {
        angle += 180;
    }
    else if (ship.dir.x > GetScreenWidth() / 2 && ship.dir.y < GetScreenHeight() / 2)
    {
        angle += 360;
    }

    ship.rotation = angle;
}

void moveShip(Ship& ship)
{
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
    {
        ship.dir = Vector2Normalize(ship.dir);
        ship.acceleration.x -= ship.dir.x;
        ship.acceleration.y -= ship.dir.y;
    }

    ship.pos.x += ship.acceleration.x * GetFrameTime();
    ship.pos.y += ship.acceleration.y * GetFrameTime();
}

void checkShipLimits(Ship& ship)
{
    if (ship.pos.x > static_cast<float>(GetScreenWidth()))
        ship.pos.x = 0;

    if (ship.pos.x < 0)
        ship.pos.x = static_cast<float>(GetScreenWidth());

    if (ship.pos.y > static_cast<float>(GetScreenHeight()))
        ship.pos.y = 0;

    if (ship.pos.y < 0)
        ship.pos.y = static_cast<float>(GetScreenHeight());
}

void checkShipIsAlive(Ship& ship)
{
    if (ship.lives <= 0)
    {
        ship.isAlive = false;
    }
}
}