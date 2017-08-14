#pragma once

#include "GameEntity.h"
#include "Enums.h"

class CloudSquare :
	public GameEntity
{
public:
	CloudSquare(GameContext& gameContext);
	CloudSquare(GameContext& gameContext, bool isCloud);
	~CloudSquare();

	Enums::eColor getColor();
	bool getIsCloud();

	void setColor(Enums::eColor newColor);
	void setIsCloud(bool newIsCloud);

	virtual void drawCurrent(sf::RenderTarget & target);
private:
	Enums::eColor mColor;
	bool mIsCloud;
};

