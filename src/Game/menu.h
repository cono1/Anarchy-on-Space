#pragma once

#include <string>

#include <raylib.h>

namespace game
{
enum CurrentScreen { PLAY, RULES, CREDITS, EXIT, MENU, PAUSE };

struct MenuRect
{
	int x;
	int y;
	float width;
	float height;
	float initWidth;
	float maxWidth;
};

void initMenu(const int screenWidth);
void updateMenu(CurrentScreen& currentScreen);
void updateMenu(CurrentScreen& currentScreen, bool& playAgain);
void printMenu(std::string title, std::string firstOption, int titleSize, int optionsSize);
void printBackButton(bool pause, int fontSize);
bool isPausePressed();
}
