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
	float speed;
	int lives;
	int maxLives;
	bool isAlive;
};

void initShip(Ship& ship);
void initEnemyShip(Ship& ship);
void restartShip(Ship& ship);
void restartEnemyShip(Ship& ship);
void updateShip(Ship& ship);
void updateEnemyShip(Ship& ship, Ship player);
void drawShip(Ship ship);
void deInitShip(Ship& ship);

void addShipLives(Ship& ship, int lives);
void removeShipLives(Ship& ship, int lives);
}