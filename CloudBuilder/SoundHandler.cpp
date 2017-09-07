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
	sf::Sound toInsert;
	toInsert.setBuffer(getBuffer(id));
	toInsert.play();
	toInsert.setVolume(mVolumeRatio * 100.0f);
	return (mSounds.insert(std::pair<eSound, sf::Sound>(id, toInsert)))->second;
}
