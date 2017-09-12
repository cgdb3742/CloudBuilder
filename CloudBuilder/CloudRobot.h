#pragma once

#include "GameEntity.h"
#include "CloudCanvas.h"

class CloudRobot :
	public GameEntity
{
public:
	CloudRobot(GameContext& gameContext, CloudCanvas& canvas, bool isVisible);
	CloudRobot(GameContext& gameContext, CloudCanvas& canvas, bool isWriter, bool isVisible);
	CloudRobot(GameContext& gameContext, CloudCanvas& canvas, Enums::eColor color, bool isVisible);
	CloudRobot(GameContext& gameContext, CloudCanvas& canvas, Enums::eColor color, bool isWriter, bool isVisible);
	~CloudRobot();

	bool getIsVisible();

	bool getIsWriter();
	void setIsWriter(bool newValue);
	CloudSquare& getPos();
	unsigned int getPosi();
	unsigned int getPosj();
	bool setPos(unsigned int i, unsigned int j);
	bool move(unsigned int i, unsigned int j, float progress);
	bool moveLeft(float progress);
	bool moveRight(float progress);
	bool moveUp(float progress);
	bool moveDown(float progress);

	void resetAll();

	virtual void animateBody(float bodyRotation, float backArmRotation, float frontArmRotation, float backLegRotation, float frontLegRotation, bool reflect);
	virtual void animateBody(float backArmRotation, float frontArmRotation, float backLegRotation, float frontLegRotation, bool reflect);

	virtual void updateCurrent(sf::Time dt);

	virtual void drawCurrent(sf::RenderTarget& target);
	virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);
private:
	void loadSprites();

	Enums::eColor mColor;
	CloudCanvas& mCanvas;
	unsigned int mPosi;
	unsigned int mPosj;
	bool mIsWriter;

	bool mIsVisible;

	float mFlyOffset;
	float mFlyMax;
	bool mFlyUp;

	sf::Vector2f mPosOffset;

	sf::Sprite mBody;
	sf::Sprite mShirt;
	sf::Sprite mBackArm;
	sf::Sprite mFrontArm;
	sf::Sprite mBackLeg;
	sf::Sprite mFrontLeg;

	float mBodyRotation;
	float mBackArmRotation;
	float mFrontArmRotation;
	float mBackLegRotation;
	float mFrontLegRotation;
};

