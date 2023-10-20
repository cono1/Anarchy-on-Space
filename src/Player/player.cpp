#include "player.h"

namespace game
{
void initPlayer(Player& player)
{
	player.score = 0;
	player.maxScore = 1000;
}

//void updatePlayer(Player& player)
//{
//
//}

void addScore(Player& player, int score)
{
	player.score += score;
}

void removeScore(Player& player, int score)
{
	player.score -= score;
}

void deinitPlayer(Player& player)
{
	player.score = 0;
}
}