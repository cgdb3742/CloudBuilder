#pragma once

#include "GameEntity.h"
#include "InstructionBoard.h"
#include "SpriteHandler.h"

class InstructionRobot :
	public GameEntity
{
public:
	InstructionRobot(GameContext& gameContext, InstructionBoard& board, bool isVisible);
	InstructionRobot(GameContext& gameContext, InstructionBoard& board, Enums::eColor color, bool isVisible);
	~InstructionRobot();

	bool getIsVisible();

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

	bool changeFace(SpriteHandler::eSprite newFace);

	virtual void updateCurrent(sf::Time dt);

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

	bool mIsVisible;

	sf::Vector2f mPosOffset;

	float mRotation;
	float mMaxRotation;
	bool mRotateLeft;

	sf::Sprite mHead;
	sf::Sprite mFace;
	sf::Sprite mBand;
};

