#pragma once

#include "Ship/ship.h"
#include "Asteroids/asteroids.h"
#include "Bullets/bullets.h"

namespace game
{
bool checkBulletToAsteroidCollision(Bullet bullet, Asteroid asteroid);
bool checkShipToAsteroidCollision(Ship ship, Asteroid asteroid);
bool checkBulletToShipCollision(Ship ship, Bullet bullet);
bool checkShipToShipCollision(Ship ship, Ship enemyShip);
}