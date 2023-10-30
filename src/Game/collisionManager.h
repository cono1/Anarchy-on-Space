#pragma once

#include "Ship/ship.h"
#include "Asteroids/asteroids.h"
#include "Bullets/bullets.h"

namespace game
{
bool checkBulletToAsteroidCollision(Bullet bullet, Asteroid asteroid);
bool checkShipToAsteroidCollision(Ship ship, Asteroid asteroid);
}