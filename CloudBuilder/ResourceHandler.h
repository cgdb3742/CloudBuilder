#pragma once
#include "MusicHandler.h"
#include "FontHandler.h"

class ResourceHandler
{
public:
	ResourceHandler();
	~ResourceHandler();

	void loadResources();

	void changeMusic(MusicHandler::eMusic newMusic);
	void changeMusic(MusicHandler::eMusic newMusic, bool playLayer);
	void changeAndPlayMusic(MusicHandler::eMusic newMusic, bool playLayer);

	void playMusic(bool playLayer);
	void pauseMusic();
	void stopMusic();

	sf::Font& getFont(FontHandler::eFont id);

	virtual void updateAll(sf::Time dt);
private:
	MusicHandler mMusicPlayer;
	FontHandler mFonts;
};

