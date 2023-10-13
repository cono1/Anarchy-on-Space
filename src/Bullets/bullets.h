#pragma once

#include "raylib.h"

namespace game
{
struct Bullet
{
	Rectangle r;
	Vector2 dir;
	float speed;
	bool active;
	Color color;
};

void initBullet(Bullet& bullet, Vector2 shipPos, int shipWidth, int shipHeight);
void activateBullet(Bullet& bullet, Vector2 shipPos, int shipWidth, int shipHeight);
void updateBullet(Bullet& bullet);
void drawBullet(Bullet bullet);
void deActivateBullet(Bullet& bullet);
}
