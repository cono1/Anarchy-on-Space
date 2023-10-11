#pragma once

#include "raylib.h"

namespace game
{
struct Bullet
{
	Vector2 pos;
	Vector2 dir;
	Vector2 size;
	float speed;
	bool active;
	Color color;
};

void initBullet(Bullet& bullet, Vector2 shipPos, int shipWidth, int shipHeight);
void activateBullet(Bullet& bullet, Vector2 shipPos, int shipWidth, int shipHeight);
void updateBullet(Bullet& bullet);
void drawBullet(Bullet bullet);
}
