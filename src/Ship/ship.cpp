#include "ship.h"

#include "raymath.h"   

namespace game
{
//void rotateShip(Ship& ship);
//void moveShip(Ship& ship);
//void checkShipLimits(Ship& ship);

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

//void updateShip(Ship& ship)
//{
//    //rotateShip(ship);
//    //moveShip(ship);
//    checkShipLimits(ship);
//}

void drawShip(Ship ship)
{
    DrawTexturePro(ship.texture,
        { 0.0f, 0.0f, static_cast<float>(ship.texture.width), static_cast<float>(ship.texture.height) },
        { ship.pos.x, ship.pos.y, static_cast<float>(ship.texture.width), static_cast<float>(ship.texture.height) },
        { static_cast<float>(ship.texture.width / 2), static_cast<float>(ship.texture.height / 2) }, ship.rotation, WHITE);
    DrawCircleLines(static_cast<int>(ship.pos.x), static_cast<int>(ship.pos.y), ship.radius, RED);
}

//void rotateShip(Ship& ship)
//{
//  
//}
//
//void moveShip(Ship& ship)
//{
//
//}
//
//void checkShipLimits(Ship& ship)
//{
//
//}

void deInitShip(Ship& ship)
{
    UnloadTexture(ship.texture);
}
}