#pragma once

#include <raylib.h>

namespace game
{
struct Ship
{
	Texture2D texture;
	Vector2 pos;
	Vector2 dir;
	Vector2 acceleration;
	float rotation;
	float radius;
};

void initShip(Ship& ship);
void updateShip(Ship& ship);
void drawShip(Ship ship);
void deInitShip(Ship& ship);
}