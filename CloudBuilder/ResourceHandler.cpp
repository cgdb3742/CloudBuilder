#include "ResourceHandler.h"



ResourceHandler::ResourceHandler()
{
	//TODO Pre-load only stuff necessary for the first screen and create a loading screen for the rest ?
	loadResources();
}


ResourceHandler::~ResourceHandler()
{
}

void ResourceHandler::loadResources()
{
	mSprites.loadResources();
	mSoundPlayer.loadResources();
	mFonts.loadResources();
}

sf::Sprite ResourceHandler::createSprite(SpriteHandler::eSprite id)
{
	return mSprites.createSprite(id);
}

sf::Sound & ResourceHandler::playSound(SoundHandler::eSound id)
{
	return mSoundPlayer.playSound(id);
}

void ResourceHandler::clearSounds()
{
	mSoundPlayer.clearSounds();
}

void ResourceHandler::changeMusic(MusicHandler::eMusic newMusic)
{
	mMusicPlayer.changeMusic(newMusic, false);
}

void ResourceHandler::changeMusic(MusicHandler::eMusic newMusic, bool playLayer)
{
	mMusicPlayer.changeMusic(newMusic, playLayer);
}

void ResourceHandler::changeAndPlayMusic(MusicHandler::eMusic newMusic, bool playLayer)
{
	mMusicPlayer.changeAndPlayMusic(newMusic, playLayer);
}

void ResourceHandler::playMusic(bool playLayer)
{
	mMusicPlayer.playMusic(playLayer);
}

void ResourceHandler::pauseMusic()
{
	mMusicPlayer.pauseMusic();
}

void ResourceHandler::stopMusic()
{
	mMusicPlayer.stopMusic();
}

sf::Font & ResourceHandler::getFont(FontHandler::eFont id)
{
	return mFonts.getFont(id);
}

void ResourceHandler::updateAll(sf::Time dt)
{
	mSoundPlayer.updateCurrent(dt);
	mMusicPlayer.updateCurrent(dt);
}
