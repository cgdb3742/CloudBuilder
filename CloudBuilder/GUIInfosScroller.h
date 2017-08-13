#pragma once
#include "GUIButton.h"

class GUIInfosContainer;

class GUIInfosScroller :
	public GUIButton
{
public:
	GUIInfosScroller(GUIInfosContainer& container, int dir, sf::Vector2f positionRatio);
	~GUIInfosScroller();

	void scroll();

	virtual void clicked();
	//virtual void handleEventCurrent(const sf::Event& event);
	virtual void drawCurrent(sf::RenderTarget& target);

	virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);
protected:
	virtual bool containsPoint(sf::Vector2f point);
private:
	//bool containsPoint(sf::Vector2f point);
	int mDir;

	GUIInfosContainer& mContainer;

	sf::ConvexShape mBasicShape;
	sf::ConvexShape mShape;
};

