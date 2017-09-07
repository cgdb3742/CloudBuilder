#include "MusicHandler.h"



MusicHandler::MusicHandler():
	mCurrentMusic(eMusic::None),
	mPlayLayer(false),
	mLayerCoeff(0.0f),
	mIsBaseActive(false),
	mIsLayerActive(false),
	mFadeDuration(1.0f),
	mVolumeRatio(1.0f)
{
	fillFilenames();
	mMusicBase.setLoop(true);
	mMusicLayer.setLoop(true);
	mMusicBase.setVolume(100.0f);
	mMusicLayer.setVolume(0.0f);
}


MusicHandler::~MusicHandler()
{
}

void MusicHandler::fillFilenames()
{
	mBaseName.clear();
	mLayerName.clear();

	mBaseName.insert(std::pair<eMusic, std::string>(eMusic::None, "NONE"));
	mLayerName.insert(std::pair<eMusic, std::string>(eMusic::None, "NONE"));
	mBaseName.insert(std::pair<eMusic, std::string>(eMusic::Title, "Pouillasse.ogg"));
	mLayerName.insert(std::pair<eMusic, std::string>(eMusic::Title, "NONE"));
	mBaseName.insert(std::pair<eMusic, std::string>(eMusic::LevelTuto, "LupanarBase.ogg"));
	mLayerName.insert(std::pair<eMusic, std::string>(eMusic::LevelTuto, "LupanarLayer.ogg"));
	mBaseName.insert(std::pair<eMusic, std::string>(eMusic::LevelTricky, "CafouilleBase.ogg"));
	mLayerName.insert(std::pair<eMusic, std::string>(eMusic::LevelTricky, "CafouilleLayer.ogg"));
}

//TODO Layer fade-in/fade-out
void MusicHandler::changeMusic(eMusic newMusic, bool playLayer)
{
	if (newMusic != mCurrentMusic)
	{
		mCurrentMusic = newMusic;

		loadMusic();
	}

	mPlayLayer = playLayer;
	mLayerCoeff = playLayer ? 1.0f : 0.0f;
}

void MusicHandler::changeAndPlayMusic(eMusic newMusic, bool playLayer)
{
	changeMusic(newMusic, playLayer);
	playMusic(playLayer);
}

void MusicHandler::playMusic(bool playLayer)
{
	mPlayLayer = playLayer;
	//mLayerCoeff = playLayer ? 1.0f : 0.0f;

	if (mMusicBase.getStatus() != sf::Music::Status::Playing && mIsBaseActive)
	{
		mMusicBase.play();
	}

	if (mMusicLayer.getStatus() != sf::Music::Status::Playing && mIsLayerActive)
	{
		mMusicLayer.play();
	}

	if (mIsLayerActive)
	{
		mMusicLayer.setVolume(mLayerCoeff * mMusicBase.getVolume());
	}
}

void MusicHandler::pauseMusic()
{
	if (mIsBaseActive)
	{
		mMusicBase.pause();
	}

	if (mIsLayerActive)
	{
		mMusicLayer.stop();
	}
}

void MusicHandler::stopMusic()
{
	if (mIsBaseActive)
	{
		mMusicBase.stop();
	}

	if (mIsLayerActive)
	{
		mMusicLayer.stop();
	}
}

void MusicHandler::setVolume(float volume)
{
	mVolumeRatio = std::min(0.0f, std::max(1.0f, volume));

	mMusicBase.setVolume(mVolumeRatio * 100.0f);
	mMusicLayer.setVolume(mLayerCoeff * mVolumeRatio * 100.0f);
}

float MusicHandler::getVolume()
{
	return mVolumeRatio;
}

void MusicHandler::updateCurrent(sf::Time dt)
{
	if (mPlayLayer && mLayerCoeff < 1.0f)
	{
		mLayerCoeff = std::min(mLayerCoeff + dt.asSeconds() / mFadeDuration, 1.0f);

		if (mIsLayerActive)
		{
			mMusicLayer.setVolume(mLayerCoeff * mMusicBase.getVolume());
		}
	}

	if (!mPlayLayer && mLayerCoeff > 0.0f)
	{
		mLayerCoeff = std::max(mLayerCoeff - dt.asSeconds() / mFadeDuration, 0.0f);

		if (mIsLayerActive)
		{
			mMusicLayer.setVolume(mLayerCoeff * mMusicBase.getVolume());
		}
	}
}

void MusicHandler::loadMusic()
{
	if (mIsBaseActive)
	{
		mMusicBase.stop();
	}

	if (mIsLayerActive)
	{
		mMusicLayer.stop();
	}

	if (mBaseName[mCurrentMusic] == "NONE")
	{
		mIsBaseActive = false;
	}
	else
	{
		mIsBaseActive = true;
		mMusicBase.openFromFile(mBaseName[mCurrentMusic]);
	}

	if (mLayerName[mCurrentMusic] == "NONE")
	{
		mIsLayerActive = false;
	}
	else
	{
		mIsLayerActive = true;
		mMusicLayer.openFromFile(mLayerName[mCurrentMusic]);
	}
}
