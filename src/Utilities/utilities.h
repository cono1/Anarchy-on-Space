#pragma once

#include <iostream>
#include <time.h>

#include <raylib.h>

namespace game
{
struct Timer
{
	std::clock_t start;
	std::clock_t end;
};

Vector2 getRandomPositionNearEdges(int margin);
void startTimer(Timer& timer);
void stopTimer(Timer& timer);
double getTimeElapsed(Timer timer);
}