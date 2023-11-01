#include "player.h"

namespace game
{
static int maxScore;

void initPlayer(Player& player)
{
	player.score = 0;
	maxScore = 10000;
	player.won = false;
}

void addScore(Player& player, int score)
{
	player.score += score;
}

void removeScore(Player& player, int score)
{
	player.score -= score;
}

void resetPlayer(Player& player)
{
	player.score = 0;
	player.won = false;
}

int getMaxScore()
{
	return maxScore;
}
}