#pragma once

#include <raylib.h>

namespace game
{
void initAudio();
void playMenuSound();
void playGameMusic();
void playShootSound();
void playAsteroidsSeparateSound();
void playButtonSound();
void playLooseHpSound();
void playDeathSound();
void deinitAudio();
Sound getButtonSound();
Sound getDeathSound();
Sound getLooseHpSound();
Music getMenuMusic();
Music getGameMusic();
}