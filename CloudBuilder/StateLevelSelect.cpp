#include "StateLevelSelect.h"
#include "Game.h"



StateLevelSelect::StateLevelSelect(GameContext& gameContext) :
	State(gameContext, Enums::eState::LevelSelect),
	mDesc(gameContext, sf::Vector2f(0.5f,0.5f)),
	mSelectedWorld(1),
	mSelectedLevel(0)
{
	initLevels();
}


StateLevelSelect::~StateLevelSelect()
{
}

void StateLevelSelect::selectWorld(unsigned int newWorld)
{
	mSelectedWorld = newWorld;
	updateChildsVector(); //Childs shouldn't have to update their own childs
}

void StateLevelSelect::selectLevel(unsigned int newLevel)
{
	mSelectedLevel = newLevel;
	mDesc.setLevelText(mSelectedWorld, mSelectedLevel);
}

unsigned int StateLevelSelect::getWorld()
{
	return mSelectedWorld;
}

unsigned int StateLevelSelect::getLevel()
{
	return mSelectedLevel;
}

void StateLevelSelect::startLevel()
{
	if (mSelectedLevel == 0)
	{
		return;
	}

	mGameContext.dataReader.loadLevelData(mSelectedWorld, mSelectedLevel);

	//mMachine.requestStop(Enums::eState::LevelSelect);
	//mMachine.requestStart(Enums::eState::Level);
	mGameContext.stateStack.addStopRequest(Enums::eState::LevelSelect);
	mGameContext.stateStack.addStartRequest(Enums::eState::Level);
}

void StateLevelSelect::setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	float topPartRatio = 0.1f;
	float bottomPartRatio = 0.1f;
	unsigned int maxLevels = 1;

	float worldMargin = mBoundingBox.x / 80.0f;
	float worldSize = (mBoundingBox.x - worldMargin) / mWorlds.size() - worldMargin;

	sf::Vector2f worldBoundingBox = sf::Vector2f(worldSize, topPartRatio * mBoundingBox.y - 2.0f * worldMargin);

	for (unsigned int i = 0; i < mWorlds.size(); i++)
	{
		mWorlds[i].setBoundingBoxCurrent(worldBoundingBox);
		mWorlds[i].setPositionAll(mTopLeftCorner + sf::Vector2f(worldMargin, worldMargin), sf::Vector2f(mBoundingBox.x - 2.0f * worldMargin, topPartRatio * mBoundingBox.y - 2.0f * worldMargin));

		if (mLevels[i].size() > maxLevels)
		{
			maxLevels = mLevels[i].size();
		}
	}

	float levelMargin = mBoundingBox.y / 80.0f;
	float levelSize = (mBoundingBox.y * (1.0f - topPartRatio - bottomPartRatio) - levelMargin) / maxLevels - levelMargin;

	sf::Vector2f levelBoundingBox = sf::Vector2f(mBoundingBox.x / 2.0f - 2.0f * levelMargin, levelSize);

	for (unsigned int i = 0; i < mWorlds.size(); i++)
	{
		for (unsigned int j = 0; j < mLevels[i].size(); j++)
		{
			mLevels[i][j].setBoundingBoxCurrent(levelBoundingBox);
			mLevels[i][j].setPositionAll(mTopLeftCorner + sf::Vector2f(mBoundingBox.x / 2.0f + levelMargin, topPartRatio * mBoundingBox.y + levelMargin), sf::Vector2f(mBoundingBox.x / 2.0f - 2.0f * levelMargin, mBoundingBox.y * (1.0f - topPartRatio - bottomPartRatio) - 2.0f * levelMargin));
		}
	}

	sf::Vector2f descBoundingBox = sf::Vector2f(mBoundingBox.x / 2.0f - 2.0f * levelMargin, mBoundingBox.y * (1.0f - topPartRatio - bottomPartRatio) - 2.0f*levelMargin);

	mDesc.setBoundingBoxCurrent(descBoundingBox);
	mDesc.setPositionAll(mTopLeftCorner + sf::Vector2f(levelMargin, topPartRatio * mBoundingBox.y + levelMargin), sf::Vector2f(mBoundingBox.x / 2.0f - 2.0f * levelMargin, mBoundingBox.y * (1.0f - topPartRatio - bottomPartRatio) - 2.0f * levelMargin));
}

void StateLevelSelect::updateChildsVector()
{
	mChilds.clear();

	for (unsigned int i = 0; i < mWorlds.size(); i++)
	{
		mChilds.push_back(mWorlds[i]);
	}

	for (unsigned int i = 0; i < mLevels[mSelectedWorld-1].size(); i++)
	{
		mChilds.push_back(mLevels[mSelectedWorld-1][i]);
	}

	mChilds.push_back(mDesc);
}

void StateLevelSelect::initLevels()
{
	mWorlds.clear();
	mLevels.clear();

	unsigned int maxLevels = 1;

	for (unsigned int i = 0; i < mGameContext.gameData.worldName.size(); i++)
	{
		sf::Vector2f worldPos((static_cast<float>(i)+0.5f) / static_cast<float>(mGameContext.gameData.worldName.size()), 0.5f);

		mWorlds.push_back(WorldSelectButton(mGameContext, worldPos, *this, i+1));

		if (mGameContext.gameData.levelName[i].size() > maxLevels)
		{
			maxLevels = mGameContext.gameData.levelName[i].size();
		}
	}

	for (unsigned int i = 0; i < mGameContext.gameData.worldName.size(); i++)
	{
		std::vector<LevelSelectButton> worldLevels;

		for (unsigned int j = 0; j < mGameContext.gameData.levelName[i].size(); j++)
		{
			sf::Vector2f levelPos(0.5f, (static_cast<float>(j)+0.5f) / static_cast<float>(maxLevels));

			worldLevels.push_back(LevelSelectButton(mGameContext, levelPos, *this, i+1, j+1));
		}

		mLevels.push_back(worldLevels);
	}
}
