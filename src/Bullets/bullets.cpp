#include "bullets.h"

#include <iostream>

#include "raymath.h"

namespace game
{
void initBullet(Bullet& bullet, Vector2 shipPos, int shipWidth, int shipHeight)
{
    bullet.r.x = shipPos.x + shipWidth / 2;
    bullet.r.y = shipPos.y + shipHeight / 2;
    bullet.dir.x = 0;
    bullet.dir.y = 0;
    bullet.r.width = 10;
    bullet.r.height = 10;
    bullet.speed = 650;
    bullet.active = false;
    bullet.color = RED;
}

void activateBullet(Bullet& bullet, Vector2 shipPos, int shipWidth, int shipHeight)
{
    bullet.active = true;
    bullet.dir = Vector2Normalize(Vector2{ GetMouseX() - shipPos.x, GetMouseY() - shipPos.y });
    bullet.r.x = shipPos.x + bullet.dir.x * shipWidth / 2;
    bullet.r.y = shipPos.y + bullet.dir.y * shipHeight / 2;
    bullet.speed = 300;
}

void updateBullet(Bullet& bullet)
{
    if (bullet.active)
    {
        bullet.r.x += (bullet.dir.x * bullet.speed) * GetFrameTime();
        bullet.r.y += (bullet.dir.y * bullet.speed) * GetFrameTime();

        if (bullet.r.x < 0 || bullet.r.x > GetScreenWidth() ||
            bullet.r.y < 0 || bullet.r.y > GetScreenHeight())
        {
            bullet.active = false;
        }
    }
}

void drawBullet(Bullet bullet)
{
    if (bullet.active)
        DrawRectangleV({ bullet.r.x, bullet.r.y }, {bullet.r.width, bullet.r.height}, bullet.color);
}

void deActivateBullet(Bullet& bullet)
{
    bullet.active = false;
    bullet.r.x = 0;
    bullet.r.y = 0;
    bullet.speed = 0;
}
}