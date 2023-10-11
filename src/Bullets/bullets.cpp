#include "bullets.h"

#include <iostream>

#include "raymath.h"

namespace game
{
void initBullet(Bullet& bullet, Vector2 shipPos, int shipWidth, int shipHeight)
{
    bullet.pos.x = shipPos.x + shipWidth / 2;
    bullet.pos.y = shipPos.y + shipHeight / 2;
    bullet.dir.x = 0;
    bullet.dir.y = 0;
    bullet.size.x = 10;
    bullet.size.y = 10;
    bullet.speed = 650;
    bullet.active = false;
    bullet.color = RED;
}

void updateBullet(Bullet& bullet)
{
    if (bullet.active)
    {
        bullet.pos.x += bullet.dir.x * bullet.speed * GetFrameTime();
        bullet.pos.y += bullet.dir.y * bullet.speed * GetFrameTime();

        if (bullet.pos.x < 0 || bullet.pos.x > GetScreenWidth() ||
            bullet.pos.y < 0 || bullet.pos.y > GetScreenHeight())
        {
            bullet.active = false;
        }
    }
}

void drawBullet(Bullet bullet)
{
    if (bullet.active)
        DrawRectangleV(bullet.pos, bullet.size, bullet.color);
}

void activateBullet(Bullet& bullet, Vector2 shipPos, int shipWidth, int shipHeight)
{
    bullet.active = true;
    bullet.dir = Vector2Normalize(Vector2{ GetMouseX() - shipPos.x, GetMouseY() - shipPos.y });
    bullet.pos.x = shipPos.x + bullet.dir.x * shipWidth / 2;
    bullet.pos.y = shipPos.y + bullet.dir.y * shipHeight / 2;
    bullet.speed = 300;
}
}