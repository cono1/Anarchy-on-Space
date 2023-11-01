#include "sound.h"

namespace game
{
static Music menuMusic;
static Music gameMusic;
static Sound clickButtonSound;
static Sound shootSound;
static Sound asteroidsSeparateSound;
static Sound looseHpSound;
static Sound deathSound;

void initAudio()
{
	InitAudioDevice();
	menuMusic = LoadMusicStream("res/sfx/370352__furbyguy__distorted-synth-guitar-1-c-110bpm.wav");//https://freesound.org/people/furbyguy/sounds/370352/
	gameMusic = LoadMusicStream("res/sfx/706735__audiomirage__october-and-twenty-three.wav");//https://freesound.org/people/audiomirage/sounds/706735/
	shootSound = LoadSound("res/sfx/8bit-damage15.wav"); //https://www.gamedevmarket.net/asset/ultimate-8bit-sfx-library-vol-3-35-retro-game-sounds
	asteroidsSeparateSound = LoadSound("res/sfx/Free UI Click Sound Effects Pack/SFX_UI_Click_Organic_Pop_Negative_1.wav"); //https://www.gamedevmarket.net/asset/free-ui-click-sound-effects-pack
	clickButtonSound = LoadSound("res/sfx/buttonSound.mp3");
	looseHpSound = LoadSound("res/sfx/Free UI Click Sound Effects Pack/SFX_UI_Click_Designed_Metallic_Dirty_Negative_1.wav"); //https://www.gamedevmarket.net/asset/free-ui-click-sound-effects-pack
	deathSound = LoadSound("res/sfx/death__juancamiloorjuela__xylophone-g4.wav"); //https://freesound.org/people/juancamiloorjuela/sounds/204648/
}

void playMenuSound()
{
	PlayMusicStream(menuMusic);
}

void playGameMusic()
{
	PlayMusicStream(gameMusic);
}

void playShootSound()
{
	PlaySound(shootSound);
}

void playAsteroidsSeparateSound()
{
	PlaySound(asteroidsSeparateSound);
}

void playButtonSound()
{
	PlaySound(clickButtonSound);
}

void playLooseHpSound()
{
	PlaySound(looseHpSound);
}

void playDeathSound()
{
	PlaySound(deathSound);
}

void deinitAudio()
{
	UnloadMusicStream(menuMusic);
	UnloadMusicStream(gameMusic);
	UnloadSound(clickButtonSound);
	UnloadSound(shootSound);
	UnloadSound(asteroidsSeparateSound);
	UnloadSound(looseHpSound);
	UnloadSound(deathSound);
	CloseAudioDevice();
}

Sound getButtonSound()
{
	return clickButtonSound;
}

Sound getDeathSound()
{
	return deathSound;
}

Sound getLooseHpSound()
{
	return looseHpSound;
}

Music getMenuMusic()
{
	return menuMusic;
}

Music getGameMusic()
{
	return gameMusic;
}
}