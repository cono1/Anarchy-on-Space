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
}