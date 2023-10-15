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
	int lives;
	int maxLives;
	bool isAlive;
};

void initShip(Ship& ship);
void restartShip(Ship& ship);
void updateShip(Ship& ship);
void drawShip(Ship ship);
void deInitShip(Ship& ship);

void addShipLives(Ship& ship, int lives);
void removeShipLives(Ship& ship, int lives);
}