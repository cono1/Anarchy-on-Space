#pragma once

#include <string>

#include <raylib.h>

namespace game
{
struct Credits
{
	Vector2 pos;
	std::string text;
	Rectangle rect;
	std::string url;
};

void printCredits();
}