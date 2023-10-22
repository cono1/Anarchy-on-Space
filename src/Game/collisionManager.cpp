#include "collisionManager.h"

#include <raymath.h>

namespace game
{
bool checkBulletToAsteroidCollision(Bullet bullet, Asteroid asteroid)
{
    if (asteroid.active && bullet.active)
    {
        return CheckCollisionCircleRec(asteroid.pos, asteroid.radius, bullet.r);
    }
    else
    {
        return false;
    }
}

bool checkShipToAsteroidCollision(Ship ship, Asteroid asteroid)
{
    if (asteroid.active)
    {
        float distX = (ship.pos.x - (ship.texture.width / 2)) - (asteroid.pos.x - (asteroid.texture.width / 2));
        float distY = (ship.pos.y - (ship.texture.height / 2)) - (asteroid.pos.y - (asteroid.texture.height / 2));
        float distance = static_cast<float>(sqrt((distX * distX) + (distY * distY)));

        return (distance <= ship.radius + asteroid.radius);
    }
    else
    {
        return false;
    }
}
}