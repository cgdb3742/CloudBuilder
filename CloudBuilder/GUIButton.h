#pragma once
#include "GameEntity.h"
class GUIButton :
	public GameEntity
{
public:
	GUIButton(GameContext& gameContext, sf::Vector2f positionRatio);
	~GUIButton();

	virtual void clicked();
	virtual void beginHover();
	virtual void endHover();

	virtual void handleEventCurrent(const sf::Event& event);

	virtual void setBoundingBoxCurrent(sf::Vector2f boundingBox);
	virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);

protected:
	virtual bool containsPoint(sf::Vector2f point);

	bool mIsHovered;

	sf::Vector2f mPositionRatio;
};

