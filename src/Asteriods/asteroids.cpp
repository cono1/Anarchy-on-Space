#include "asteroids.h"

#include <iostream>

namespace game
{
void initBigAsteroid(Asteroid& asteroid);
//void updateBigAsteroid(Asteroid& asteroid);
void drawBigAsteroid(Asteroid asteroid);
void deInitBigAsteroid(Asteroid& asteroid);

void initAsteroid(Asteroid& asteroid, AsteroidType asteroidType)
{
	switch (asteroidType)
	{
	case BIG:
		initBigAsteroid(asteroid);
		break;
	case MEDIUM:
		break;
	case SMALL:
		break;
	default:
		break;
	}
}

//void updateAsteroid(Asteroid& asteroid, AsteroidType asteroidType)
//{
//	switch (asteroidType)
//	{
//	case BIG:
//		//updateBigAsteroid(asteroid);
//		break;
//	case MEDIUM:
//		break;
//	case SMALL:
//		break;
//	default:
//		break;
//	}
//}

void drawAsteroid(Asteroid asteroid, AsteroidType asteroidType)
{
	if (asteroid.active)
	{
		switch (asteroidType)
		{
		case BIG:
			drawBigAsteroid(asteroid);
			break;
		case MEDIUM:
			break;
		case SMALL:
			break;
		default:
			break;
		}
	}
}

void deInitAsteroid(Asteroid& asteroid)
{
	deInitBigAsteroid(asteroid);
}


void initBigAsteroid(Asteroid& asteroid)
{
	asteroid.texture = LoadTexture("res/TempAsteroid.png");
	asteroid.pos.x = 250;
	asteroid.pos.y = 250;
	asteroid.dir.x = 0;
	asteroid.dir.y = 0;
	asteroid.radius = static_cast<float>(asteroid.texture.width / 2);
	asteroid.rotation = 0;
	asteroid.active = true;
}

//void updateBigAsteroid(Asteroid& asteroid)
//{
//
//}

void drawBigAsteroid(Asteroid asteroid)
{
	DrawTexturePro(asteroid.texture,
		{ 0.0f, 0.0f, static_cast<float>(asteroid.texture.width), static_cast<float>(asteroid.texture.height) },
		{ asteroid.pos.x, asteroid.pos.y, static_cast<float>(asteroid.texture.width), static_cast<float>(asteroid.texture.height) },
		{ static_cast<float>(asteroid.texture.width / 2), static_cast<float>(asteroid.texture.height / 2) }, asteroid.rotation, WHITE);
	DrawCircleLines(static_cast<int>(asteroid.pos.x), static_cast<int>(asteroid.pos.y), asteroid.radius, RED);
}

void deInitBigAsteroid(Asteroid& asteroid)
{
	UnloadTexture(asteroid.texture);
}
}