#pragma once
#include <vector>
#include "GameEntity.h"

class InstructionBoard;

class InstructionBoardFlow :
	public GameEntity
{
public:
	InstructionBoardFlow(GameContext& gameContext, InstructionBoard& board);
	~InstructionBoardFlow();

	void computeLinks();

	virtual void updateCurrent(sf::Time dt);
	virtual void drawCurrent(sf::RenderTarget& target);
private:
	InstructionBoard& mBoard;

	float mFlowPos;

	std::vector<std::vector<bool>> mLinkUp;
	std::vector<std::vector<bool>> mLinkDown;
	std::vector<std::vector<bool>> mLinkLeft;
	std::vector<std::vector<bool>> mLinkRight;
};

