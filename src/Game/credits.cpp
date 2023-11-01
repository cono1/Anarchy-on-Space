#include "credits.h"

#include <iostream>

#include "printer.h"
#include "menu.h"
#include "Sound/sound.h"

namespace game
{
static Font font;
static Color textColor;
static int centerX;
static float creditsSize;
static Vector2 mousePos;
extern CurrentScreen currentScreen;

Credits dev;
Credits art1;
Credits art2;
Credits music1;
Credits music2;
Credits sound1;
Credits sound2;
Credits sound3;
Credits sound4;

void initCredits();
void calculateCreditsPosition(Vector2& textPos, std::string text, Vector2 previousTextPos);
void calculateCreditsBox(Rectangle& rect, Vector2 textPos, std::string text);
void openURL(Rectangle rect, std::string url);
void updateCreditStatus();
void drawCredits(std::string text, Vector2 pos);

void printCredits()
{
	int backSize = getPauseSize();
	initCredits();

	updateCreditStatus();
	
	openURL(art2.rect, art2.url);
	openURL(music1.rect, music1.url);
	openURL(music2.rect, music2.url);
	openURL(sound1.rect, sound1.url);
	openURL(sound2.rect, sound2.url);
	openURL(sound4.rect, sound4.url);

	initDrawing();
	printBackButton(false, backSize);

	drawCredits(dev.text, dev.pos);
	drawCredits(art1.text, art1.pos);
	drawCredits(art2.text, art2.pos);

	drawCredits(music1.text, music1.pos);
	drawCredits(music2.text, music2.pos);

	drawCredits(sound1.text, sound1.pos);
	drawCredits(sound2.text, sound2.pos);
	drawCredits(sound3.text, sound3.pos);
	drawCredits(sound4.text, sound4.pos);
	endDrawing();

}

void initCredits()
{
	font = getFont();
	textColor = getTextColor();
	centerX = GetScreenWidth() / 2;
	creditsSize = 45;
	mousePos = GetMousePosition();

	dev.text = "Developed by Daniela Gonzalez";
	dev.pos.x = centerX - (MeasureTextEx(font, dev.text.c_str(), creditsSize, 0).x) / 2;
	dev.pos.y = 40;

	art1.text = "Player ship and asteroids art by Eros Beron";
	calculateCreditsPosition(art1.pos, art1.text, dev.pos);

	art2.text = "Enemy art by Rorkkkk";
	art2.url = "https://www.instagram.com/rorkkkkkk/";
	calculateCreditsPosition(art2.pos, art2.text, art1.pos);
	calculateCreditsBox(art2.rect, art2.pos, art2.text);

	music1.text = "Distorted Synth Guitar by Furbyguy";
	music1.url = "https://freesound.org/people/furbyguy/sounds/370352/";
	calculateCreditsPosition(music1.pos, music1.text, art2.pos);
	calculateCreditsBox(music1.rect, music1.pos, music1.text);

	music2.text = "October and Twenty Three by Steven F Allen";
	music2.url = "https://freesound.org/people/audiomirage/sounds/706735/";
	calculateCreditsPosition(music2.pos, music2.text, music1.pos);
	calculateCreditsBox(music2.rect, music2.pos, music2.text);

	sound1.text = "8bit-damage15 (Shooting sound) by MOsh";
	sound1.url = "https://www.gamedevmarket.net/asset/ultimate-8bit-sfx-library-vol-3-35-retro-game-sounds";
	calculateCreditsPosition(sound1.pos, sound1.text, music2.pos);
	calculateCreditsBox(sound1.rect, sound1.pos, sound1.text);

	sound2.text = "XYLOPHONE G4 (Death sound) by Juan Camilo Ojuela";
	sound2.url = "https://freesound.org/people/juancamiloorjuela/sounds/204648/";
	calculateCreditsPosition(sound2.pos, sound2.text, sound1.pos);
	calculateCreditsBox(sound2.rect, sound2.pos, sound2.text);

	sound3.text = "Click button sound by Sebastian Alarcon";
	calculateCreditsPosition(sound3.pos, sound3.text, sound2.pos);

	sound4.text = "Click_Designed_Metallic_Dirty_Negative_1 (collision sound)\nand Click_Organic_Pop_Negative_1 (asteroids break sound)\n \t\t\t \t\t by MadRooster";
	sound4.url = "https://www.gamedevmarket.net/asset/free-ui-click-sound-effects-pack";
	sound4.pos.x = centerX - (MeasureTextEx(font, "and Click_Organic_Pop_Negative_1 (asteroids break sound)", creditsSize, 0).x) / 2;
	sound4.pos.y = sound3.pos.y + MeasureTextEx(font, "SFX_UI_Click_Designed_Metallic_Dirty_Negative_1 (collision sound)", creditsSize, 0).y;
	calculateCreditsBox(sound4.rect, sound4.pos, sound4.text);
}

void calculateCreditsPosition(Vector2& textPos, std::string text, Vector2 previousTextPos)
{
	textPos.x = centerX - (MeasureTextEx(font, text.c_str(), creditsSize, 0).x) / 2;
	textPos.y = previousTextPos.y + MeasureTextEx(font, text.c_str(), creditsSize, 0).y + 20;
}

void calculateCreditsBox(Rectangle& rect, Vector2 textPos, std::string text)
{
	rect.x = textPos.x;
	rect.y = textPos.y;
	rect.width = MeasureTextEx(font,  text.c_str(), creditsSize, 0).x;
	rect.height = MeasureTextEx(font, text.c_str(), creditsSize, 0).y;
}

void openURL(Rectangle rect, std::string url)
{
	if (CheckCollisionPointRec(mousePos, rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		OpenURL(url.c_str());
	}
}

void updateCreditStatus()
{
	if (isPausePressed() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		currentScreen = MENU;
		currentScreen = PAUSE;
		playButtonSound();
	}
}

void drawCredits(std::string text, Vector2 pos)
{
	DrawTextEx(font, text.c_str(), pos, creditsSize, 0, textColor);
}

}