#pragma once
#include <map>
#include <SFML/Audio.hpp>

class SoundHandler
{
public:
	enum eSound
	{
		SoundTODO = 0
	};

	SoundHandler();
	~SoundHandler();

	void loadResources();

	virtual void updateCurrent(sf::Time dt);

	void clearSounds();

	void setVolume(float volume);
	float getVolume();

	sf::SoundBuffer& getBuffer(eSound id);
	sf::Sound& playSound(eSound id);
private:
	std::map<eSound, sf::SoundBuffer> mSoundBuffers;
	std::multimap<eSound, sf::Sound> mSounds;

	float mVolumeRatio;
};

