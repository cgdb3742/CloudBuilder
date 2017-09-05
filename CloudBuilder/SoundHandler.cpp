#include <list>
#include "SoundHandler.h"



SoundHandler::SoundHandler()
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

sf::SoundBuffer & SoundHandler::getBuffer(eSound id)
{
	return mSoundBuffers[id];
}

sf::Sound & SoundHandler::playSound(eSound id)
{
	sf::Sound toInsert;
	toInsert.setBuffer(getBuffer(id));
	toInsert.play();
	return (mSounds.insert(std::pair<eSound, sf::Sound>(id, toInsert)))->second;
}
