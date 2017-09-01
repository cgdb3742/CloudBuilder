#pragma once
#include <vector>
#include "State.h"
#include "WorldSelectButton.h"
#include "LevelSelectButton.h"
#include "LevelSelectDescription.h"

class StateLevelSelect :
	public State
{
public:
	StateLevelSelect(GameContext& gameContext, StateMachine& machine);
	~StateLevelSelect();

	void selectWorld(unsigned int newWorld);
	void selectLevel(unsigned int newLevel);

	unsigned int getWorld();
	unsigned int getLevel();

	void startLevel();

	virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);

	virtual void updateChildsVector();

private:
	void initLevels();

	std::vector<WorldSelectButton> mWorlds;
	std::vector<std::vector<LevelSelectButton>> mLevels;
	LevelSelectDescription mDesc;

	unsigned int mSelectedLevel;
	unsigned int mSelectedWorld;
};

