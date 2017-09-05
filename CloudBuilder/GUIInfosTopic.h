#pragma once
#include <string>
#include "GUIButton.h"

class GUIInfosContainer;

class GUIInfosTopic :
	public GUIButton
{
public:
	GUIInfosTopic(GameContext& gameContext, GUIInfosContainer& container, int id, sf::Vector2f positionRatio);
	~GUIInfosTopic();

	virtual void clicked();
	//virtual void handleEventCurrent(const sf::Event& event);
	virtual void drawCurrent(sf::RenderTarget& target);
private:
	int mId;

	GUIInfosContainer& mContainer;

	sf::Font& mFont;
};

