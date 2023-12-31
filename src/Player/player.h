#pragma once

namespace game
{
struct Player
{
	int score;
	bool won;
};

void initPlayer(Player& player);
void addScore(Player& player, int score);
void removeScore(Player& player, int score);
void resetPlayer(Player& player);
int getMaxScore();
}