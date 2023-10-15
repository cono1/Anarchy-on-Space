#include "menu.h"

#include <iostream>

#include <raylib.h>

namespace game
{
const int maxMenuRects = 4;
static MenuRect menuRect[maxMenuRects];
static MenuRect pauseRect;

void writeOnMenuSquare(std::string word, int pos, int fontSize);
bool checkMenuInput(CurrentScreen currentSquare);
bool checkCollision(MenuRect& menuRec, float initWidth, float maxWidth);

void initMenu(const int screenWidth)
{
	int spaceBetweenRects = 20;
	int firstRectYPosition = 300;

	for (int i = 0; i < maxMenuRects; i++)
	{
		menuRect[i].width = 450;
		menuRect[i].height = 80;
		menuRect[i].x = (screenWidth - menuRect[i].x) / 2;
		menuRect[i].y = static_cast<int>(firstRectYPosition + (menuRect[i].height + spaceBetweenRects) * i);
		menuRect[i].initWidth = menuRect[i].width;
		menuRect[i].maxWidth = menuRect[i].width + 20;
	}

	pauseRect.x = 40;
	pauseRect.y = 15;
	pauseRect.width = 35;
	pauseRect.height = 35;
	pauseRect.initWidth = pauseRect.width;
	pauseRect.maxWidth = pauseRect.width + 10;
}

void updateMenu(CurrentScreen& currentScreen)
{
	if (checkMenuInput(PLAY))
		currentScreen = PLAY;	

	if (checkMenuInput(PAUSE))
		currentScreen = PAUSE;

	if (checkMenuInput(RULES))
		currentScreen = RULES;

	if (checkMenuInput(CREDITS))
		currentScreen = CREDITS;

	if (checkMenuInput(EXIT))
		currentScreen = EXIT;
}

void printMenu(std::string title, int titleSize, int optionsSize)
{
	DrawText(TextFormat(title.c_str()), (GetScreenWidth() - MeasureText(title.c_str(), titleSize)) / 2, 100, titleSize, YELLOW);

	for (int i = 0; i < maxMenuRects; i++)
	{
		DrawRectangleGradientH(static_cast<int>(menuRect[i].x - menuRect[i].width / 2), 
							   static_cast<int>(menuRect[i].y - menuRect[i].height / 2),
							   static_cast<int>(menuRect[i].width),
							   static_cast<int>(menuRect[i].height), GOLD, DARKBROWN);

		if (i == PLAY)
			writeOnMenuSquare("PLAY", i, optionsSize);
		
		if (i == RULES)
			writeOnMenuSquare("HOW TO PLAY", i, optionsSize);

		if (i == CREDITS)
			writeOnMenuSquare("CREDITS", i, optionsSize);

		if (i == EXIT)
			writeOnMenuSquare("EXIT", i, optionsSize);
	}
}

void writeOnMenuSquare(std::string word, int pos, int fontSize)
{
	int xOffsetText = static_cast<int>(menuRect[pos].x) - static_cast<int>(MeasureText(word.c_str(), fontSize)) / 2;
	int yOffsetText = static_cast<int>((menuRect[pos].height - fontSize / 2) / 2);

	DrawText(word.c_str(), xOffsetText, menuRect[pos].y - yOffsetText, fontSize, WHITE);
}

bool checkMenuInput(CurrentScreen currentSquare)
{
	return (checkCollision(menuRect[currentSquare], menuRect[currentSquare].initWidth, 
			menuRect[currentSquare].maxWidth) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}

bool checkCollision(MenuRect& menuRec, float initWidth, float maxWidth)
{
	int mouseX = static_cast<int>(GetMousePosition().x);
	int mouseY = static_cast<int>(GetMousePosition().y);

	if (mouseX >= menuRec.x - menuRec.width / 2 &&
		mouseX <= menuRec.x + menuRec.width / 2 &&
		mouseY >= menuRec.y - menuRec.height / 2 &&
		mouseY <= menuRec.y + menuRec.height / 2)
	{
		if (menuRec.width < maxWidth)
			menuRec.width += 5;
		
		return true;
	}
	else
	{
		menuRec.width = initWidth;
		return false;
	}
}


void printBackButton(bool pause, int fontSize)
{
	DrawRectangleGradientH(static_cast<int>(pauseRect.x - pauseRect.width / 2), 
						   static_cast<int>(pauseRect.y - pauseRect.height / 2), 
						   static_cast<int>(pauseRect.width), 
						   static_cast<int>(pauseRect.height), YELLOW, ORANGE);

	if (pause)
		DrawText("||", pauseRect.x, pauseRect.y - 10, fontSize, WHITE);
	else
		DrawText("<-", pauseRect.x, pauseRect.y - 10, fontSize, WHITE);
}

bool isPausePressed()
{
	return checkCollision(pauseRect, pauseRect.initWidth, pauseRect.maxWidth);
}
}