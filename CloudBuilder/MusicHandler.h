#pragma once
#include <map>
#include <SFML/Audio.hpp>

class MusicHandler
{
public:
	enum eMusic
	{
		None = 0,
		Title = 1,
		LevelTuto = 2,
		LevelTricky = 3
	};

	MusicHandler();
	~MusicHandler();

	void fillFilenames();

	void changeMusic(eMusic newMusic, bool playLayer);
	void changeAndPlayMusic(eMusic newMusic, bool playLayer);

	void playMusic(bool playLayer);
	void pauseMusic();
	void stopMusic();

	void setVolume(float volume);
	float getVolume();

	virtual void updateCurrent(sf::Time dt);
private:
	void loadMusic();

	std::map<eMusic, std::string> mBaseName;
	std::map<eMusic, std::string> mLayerName;

	sf::Music mMusicBase;
	sf::Music mMusicLayer;
	bool mIsBaseActive;
	bool mIsLayerActive;

	eMusic mCurrentMusic;
	bool mPlayLayer;
	float mLayerCoeff;
	float mFadeDuration;

	float mVolumeRatio;
};

