#pragma once

#include "GameEntity.h"
#include "InstructionBoard.h"

class InstructionRobot :
	public GameEntity
{
public:
	explicit InstructionRobot(InstructionBoard& board);
	InstructionRobot(InstructionBoard& board, Enums::eColor color);
	~InstructionRobot();

	InstructionSquare& getPos();
	bool setPos(unsigned int i, unsigned int j);
	bool move(unsigned int i, unsigned int j, float progress);
	bool moveLeft(float progress);
	bool moveRight(float progress);
	bool moveUp(float progress);
	bool moveDown(float progress);

	void resetAll();

	bool getLastCheck();
	void setLastCheck(bool newValue);

	Enums::eResult getResult();
	void setResult(Enums::eResult newValue);

	bool getIsActive();
	void setIsActive(bool newValue);

	virtual void drawCurrent(sf::RenderTarget& target);
	virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);
private:
	Enums::eColor mColor;
	InstructionBoard& mBoard;
	unsigned int mPosi;
	unsigned int mPosj;

	bool mIsActive;
	bool mLastCheck;
	Enums::eResult mResult;

	sf::Vector2f mPosOffset;
};

