#pragma once

#include <raylib.h>

namespace game
{
enum AsteroidType { BIG, MEDIUM, SMALL };

struct Asteroid
{
	Texture2D texture;
	Vector2 pos;
	Vector2 dir;
	float radius;
	float rotation;
	bool active;
};

void initAsteroid(Asteroid& asteroid, AsteroidType asteroidType);
void restartAsteroids(Asteroid& asteroid);
void updateAsteroid(Asteroid& asteroid);
void drawAsteroid(Asteroid asteroid);
void deInitAsteroid(Asteroid& asteroid);
}