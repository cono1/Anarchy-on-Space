#include "asteroids.h"

#include <iostream>

#include "Utilities/utilities.h"

namespace game
{
void checkAsteroidLimits(Asteroid& asteroid);

void initBigAsteroid(Asteroid& asteroid);

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

void updateAsteroid(Asteroid& asteroid)
{
	if (asteroid.active)
	{
		checkAsteroidLimits(asteroid);
		asteroid.pos.x += asteroid.dir.x * GetFrameTime();
		asteroid.pos.y += asteroid.dir.y * GetFrameTime();
		asteroid.rotation += 10 * GetFrameTime();
	}
}

void drawAsteroid(Asteroid asteroid)
{
	if (asteroid.active)
	{
		DrawTexturePro(asteroid.texture,
			{ 0.0f, 0.0f, static_cast<float>(asteroid.texture.width), static_cast<float>(asteroid.texture.height) },
			{ asteroid.pos.x, asteroid.pos.y, static_cast<float>(asteroid.texture.width), static_cast<float>(asteroid.texture.height) },
			{ static_cast<float>(asteroid.texture.width / 2), static_cast<float>(asteroid.texture.height / 2) }, asteroid.rotation, WHITE);
		DrawCircleLines(static_cast<int>(asteroid.pos.x), static_cast<int>(asteroid.pos.y), asteroid.radius, RED);
	}
}

void deInitAsteroid(Asteroid& asteroid)
{
	UnloadTexture(asteroid.texture);
}

void checkAsteroidLimits(Asteroid& asteroid)
{
	if (asteroid.pos.x > static_cast<float>(GetScreenWidth()))
		asteroid.pos.x = 0;

	if (asteroid.pos.x < 0)
		asteroid.pos.x = static_cast<float>(GetScreenWidth());

	if (asteroid.pos.y > static_cast<float>(GetScreenHeight()))
		asteroid.pos.y = 0;

	if (asteroid.pos.y < 0)
		asteroid.pos.y = static_cast<float>(GetScreenHeight());
}

void initBigAsteroid(Asteroid& asteroid)
{
	asteroid.texture = LoadTexture("res/TempAsteroid.png");
	asteroid.pos = GetRandomPositionNearEdges(200);
	asteroid.dir.x = static_cast<float>(GetRandomValue(-120, 120));
	asteroid.dir.y = static_cast<float>(GetRandomValue(-120, 120));
	asteroid.radius = static_cast<float>(asteroid.texture.width / 2);
	asteroid.rotation = 0;
	asteroid.active = true;
}
}