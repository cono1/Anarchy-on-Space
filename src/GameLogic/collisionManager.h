#pragma once

#include "Ship/ship.h"
#include "Asteriods/asteroids.h"
#include "Bullets/bullets.h"

namespace game
{
bool checkBulletToAsteroidCollision(Bullet bullet, Asteroid asteroid);
}