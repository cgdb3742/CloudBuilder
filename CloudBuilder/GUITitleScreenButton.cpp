#include "GUITitleScreenButton.h"



GUITitleScreenButton::GUITitleScreenButton(GameContext& gameContext, sf::Vector2f positionRatio, unsigned int id):
	GUIButton(gameContext, positionRatio),
	mId(id)
{
}


GUITitleScreenButton::~GUITitleScreenButton()
{
}

void GUITitleScreenButton::clicked()
{
}
