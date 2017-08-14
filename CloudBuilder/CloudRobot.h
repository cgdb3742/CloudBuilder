#pragma once

#include "GameEntity.h"
#include "CloudCanvas.h"

class CloudRobot :
	public GameEntity
{
public:
	CloudRobot(GameContext& gameContext, CloudCanvas& canvas);
	CloudRobot(GameContext& gameContext, CloudCanvas& canvas, bool isWriter);
	CloudRobot(GameContext& gameContext, CloudCanvas& canvas, Enums::eColor color);
	CloudRobot(GameContext& gameContext, CloudCanvas& canvas, Enums::eColor color, bool isWriter);
	~CloudRobot();

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

	virtual void drawCurrent(sf::RenderTarget& target);
	virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);
private:
	Enums::eColor mColor;
	CloudCanvas& mCanvas;
	unsigned int mPosi;
	unsigned int mPosj;
	bool mIsWriter;

	sf::Vector2f mPosOffset;
};

