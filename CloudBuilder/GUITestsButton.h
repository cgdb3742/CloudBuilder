#pragma once
#include "GUIButton.h"

class Level;
class GUITestsModel;

class GUITestsButton :
	public GUIButton
{
public:
	GUITestsButton(GameContext& gameContext, sf::Vector2f positionRatio, Level& level, int dir);
	~GUITestsButton();

	virtual void clicked();

	virtual void drawCurrent(sf::RenderTarget& target);

	virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);
protected:
	virtual bool containsPoint(sf::Vector2f point);
private:
	int mDir;

	sf::ConvexShape mBasicShape;
	sf::ConvexShape mShape;

	Level& mLevel;
};

