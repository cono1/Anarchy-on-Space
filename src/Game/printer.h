#pragma once

#include <raylib.h>

namespace game
{
void initPrinter();
void initDrawing();
void printScore(int score);
void printLives(int lives);
Font getFont();
Color getTextColor();
int getTitleSize();
int getOptionsSize();
int getPauseSize();
void endDrawing();
void deinitPrinter();
}