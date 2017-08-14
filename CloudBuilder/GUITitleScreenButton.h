#pragma once
#include "GUIButton.h"
class GUITitleScreenButton :
	public GUIButton
{
public:
	GUITitleScreenButton(GameContext& gameContext, sf::Vector2f positionRatio, unsigned int id);
	~GUITitleScreenButton();

	virtual void clicked();

private:
	unsigned int mId;
};

