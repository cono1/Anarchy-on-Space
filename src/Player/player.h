#pragma once

namespace game
{
struct Player
{
	int score;
	int maxScore;
};

void initPlayer(Player& player);
//void updatePlayer(Player& player);
void addScore(Player& player, int score);
void removeScore(Player& player, int score);
void deinitPlayer(Player& player);
}