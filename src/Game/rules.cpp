#include "rules.h"

#include <string>

#include <raylib.h>

#include "printer.h"
#include "menu.h"
#include "Player/player.h"
#include "Sound/sound.h"

namespace game
{
extern CurrentScreen currentScreen;

void calculateRulesPosition(Vector2& pos, std::string text, Vector2 previousPos, float size);
void updateStatus();
void drawRules(std::string text, Vector2 pos, float size);

void printHowToPlay()
{
	Font font = getFont();
	int backSize = getPauseSize();
	float size = static_cast<float>(getOptionsSize());
	Color color = getTextColor();
	std::string points = std::to_string(getMaxScore());

	std::string movementText = "Move: Right click to move.";
	Vector2 movPos;
	movPos.x = GetScreenWidth() / 2 - (MeasureTextEx(font, movementText.c_str(), size, 0).x) / 2;
	movPos.y = static_cast<float>(GetScreenHeight()) / 4;

	std::string shootText = "Shoot: Left click to fire.";
	Vector2 shootPos;
	calculateRulesPosition(shootPos, shootText, movPos, size);

	std::string objectiveText = "Objective: Avoid and destroy asteroids. If they touch you, you lose one life.";
	Vector2 objectivePos;
	calculateRulesPosition(objectivePos, objectiveText, shootPos, size - 5);

	std::string lifeText = "You have 3 lives. If you loose all of them, it's game over.";
	Vector2 lifePos;
	calculateRulesPosition(lifePos, lifeText, objectivePos, size);

	std::string winText = "Winning: Reach" + points  + " points to win the game.";
	Vector2 winPos;
	calculateRulesPosition(winPos, winText, lifePos, size);

	updateStatus();

	initDrawing();
	printBackButton(false, backSize);

	drawRules(movementText, movPos, size);
	drawRules(shootText, shootPos, size);
	drawRules(objectiveText, objectivePos, size - 5);
	drawRules(lifeText, lifePos, size);
	drawRules(winText, winPos, size);
	endDrawing();
}

void calculateRulesPosition(Vector2& pos, std::string text, Vector2 previousPos, float size)
{
	pos.x = GetScreenWidth() / 2 - (MeasureTextEx(getFont(), text.c_str(), size, 0).x) / 2;
	pos.y = previousPos.y + MeasureTextEx(getFont(), text.c_str(), size, 0).y + 20;
}

void updateStatus()
{
	if (isPausePressed() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		currentScreen = MENU;
		currentScreen = PAUSE;
		playButtonSound();
	}
}

void drawRules(std::string text, Vector2 pos, float size)
{
	DrawTextEx(getFont(), text.c_str(), pos, size, 0, getTextColor());
}
}