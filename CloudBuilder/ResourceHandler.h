#pragma once
#include "SpriteHandler.h"
#include "SoundHandler.h"
#include "MusicHandler.h"
#include "FontHandler.h"

class ResourceHandler
{
public:
	ResourceHandler();
	~ResourceHandler();

	void loadResources();

	sf::Sprite createSprite(SpriteHandler::eSprite id);

	sf::Sound& playSound(SoundHandler::eSound id);
	void clearSounds();

	void changeMusic(MusicHandler::eMusic newMusic);
	void changeMusic(MusicHandler::eMusic newMusic, bool playLayer);
	void changeAndPlayMusic(MusicHandler::eMusic newMusic, bool playLayer);

	void playMusic(bool playLayer);
	void pauseMusic();
	void stopMusic();

	sf::Font& getFont(FontHandler::eFont id);

	virtual void updateAll(sf::Time dt);
private:
	SpriteHandler mSprites;
	SoundHandler mSoundPlayer;
	MusicHandler mMusicPlayer;
	FontHandler mFonts;
};

