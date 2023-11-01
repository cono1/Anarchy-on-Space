#include "printer.h"

namespace game
{
static Font font;
static int titleSize = 90;
static int optionsSize = 50;
static int pauseSize = 25;
static float textSize = 50;
static Color textColor = MAGENTA;
static Vector2 scoreTextPos;
static Vector2 hpTextPos;

void initPrinter()
{
	font = LoadFontEx("res/BebasNeue-Regular.ttf", 150, 0, 550);
	scoreTextPos.x = static_cast<float>(GetScreenWidth()) - (MeasureTextEx(font, "SCORE: 00000", textSize, 0).x);
	scoreTextPos.y = 10;
	hpTextPos.x = static_cast<float>(GetScreenWidth()) - (MeasureTextEx(font, "LIVES: 00", textSize, 0).x);
	hpTextPos.y = scoreTextPos.y + MeasureTextEx(font, "LIVES: 00", textSize, 0).y;
}

void initDrawing()
{
	BeginDrawing();
	ClearBackground(BLACK);
}

void printScore(int score)
{
	DrawTextEx(font, TextFormat("SCORE: %i", score), scoreTextPos, textSize, 0, textColor);
}

void printLives(int lives)
{
	DrawTextEx(font, TextFormat("LIVES: %i", lives), hpTextPos, textSize, 0, textColor);
}

Font getFont()
{
	return font;
}

Color getTextColor()
{
	return textColor;
}

int getTitleSize()
{
	return titleSize;
}

int getOptionsSize()
{
	return optionsSize;
}

int getPauseSize()
{
	return pauseSize;
}

void endDrawing()
{
	EndDrawing();
}

void deinitPrinter()
{
	UnloadFont(font);
}
}