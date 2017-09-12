#include <list>
#include "SoundHandler.h"



SoundHandler::SoundHandler():
	mVolumeRatio(1.0f)
{
}


SoundHandler::~SoundHandler()
{
}

void SoundHandler::loadResources()
{
	mSoundBuffers.insert(std::pair<eSound, sf::SoundBuffer>(eSound::SFXYes, sf::SoundBuffer()));
	mSoundBuffers.at(eSound::SFXYes).loadFromFile("Sounds/sfx_yes.wav");
	mSoundBuffers.insert(std::pair<eSound, sf::SoundBuffer>(eSound::SFXNo, sf::SoundBuffer()));
	mSoundBuffers.at(eSound::SFXNo).loadFromFile("Sounds/sfx_no.wav");
	mSoundBuffers.insert(std::pair<eSound, sf::SoundBuffer>(eSound::SFXBlip, sf::SoundBuffer()));
	mSoundBuffers.at(eSound::SFXBlip).loadFromFile("Sounds/sfx_blip.wav");
	mSoundBuffers.insert(std::pair<eSound, sf::SoundBuffer>(eSound::SFXClic, sf::SoundBuffer()));
	mSoundBuffers.at(eSound::SFXClic).loadFromFile("Sounds/sfx_clic.wav");
	mSoundBuffers.insert(std::pair<eSound, sf::SoundBuffer>(eSound::SFXSleep, sf::SoundBuffer()));
	mSoundBuffers.at(eSound::SFXSleep).loadFromFile("Sounds/sfx_sleep.wav");
	mSoundBuffers.insert(std::pair<eSound, sf::SoundBuffer>(eSound::SFXMove, sf::SoundBuffer()));
	mSoundBuffers.at(eSound::SFXMove).loadFromFile("Sounds/sfx_move.wav");
}

void SoundHandler::updateCurrent(sf::Time dt)
{
	std::list<std::multimap<eSound, sf::Sound>::iterator> toRemove;

	for (std::multimap<eSound, sf::Sound>::iterator pos = mSounds.begin(); pos != mSounds.end(); ++pos)
	{
		if (pos->second.getStatus() == sf::SoundSource::Status::Stopped)
		{
			toRemove.push_back(pos);
		}
	}

	for (std::multimap<eSound, sf::Sound>::iterator removable : toRemove)
	{
		mSounds.erase(removable);
	}
}

void SoundHandler::clearSounds()
{
	mSounds.clear();
}

void SoundHandler::setVolume(float volume)
{
	mVolumeRatio = std::min(0.0f, std::max(1.0f, volume));

	for (std::multimap<eSound, sf::Sound>::iterator pos = mSounds.begin(); pos != mSounds.end(); ++pos)
	{
		pos->second.setVolume(mVolumeRatio * 100.0f);
	}
}

float SoundHandler::getVolume()
{
	return mVolumeRatio;
}

sf::SoundBuffer & SoundHandler::getBuffer(eSound id)
{
	return mSoundBuffers[id];
}

sf::Sound & SoundHandler::playSound(eSound id)
{
	sf::Sound& toReturn = (mSounds.insert(std::pair<eSound, sf::Sound>(id, sf::Sound())))->second;
	toReturn.setBuffer(getBuffer(id));
	toReturn.play();
	toReturn.setVolume(mVolumeRatio * 100.0f);
	return toReturn;

	//sf::Sound toInsert;
	//toInsert.setBuffer(getBuffer(id));
	//toInsert.play();
	//toInsert.setVolume(mVolumeRatio * 100.0f);
	//return (mSounds.insert(std::pair<eSound, sf::Sound>(id, toInsert)))->second;
}
