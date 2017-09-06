#include "PopUpButton.h"
#include "Game.h"
#include "StateMachine.h"



PopUpButton::PopUpButton(GameContext& gameContext, sf::Vector2f positionRatio, PopUpData messageData):
	GUIButton(gameContext, positionRatio),
	mText(messageData.buttonMessage),
	mFont(gameContext.resourceHandler.getFont(FontHandler::Arial))
{
}


PopUpButton::~PopUpButton()
{
}

void PopUpButton::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape background(mBoundingBox);
	background.setPosition(mTopLeftCorner);
	background.setFillColor(sf::Color(127, 127, 127));
	target.draw(background);

	sf::Text text;
	text.setFont(mFont);
	text.setString(mText);
	text.setCharacterSize(36);
	text.setFillColor(sf::Color(255, 255, 255));
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	float scale = std::min(mBoundingBox.x / textRect.width, mBoundingBox.y / textRect.height);
	text.scale(sf::Vector2f(scale, scale) * 0.8f);
	text.setPosition(mTopLeftCorner + mBoundingBox / 2.0f);
	target.draw(text);
}

void PopUpButton::clicked()
{
	//mMachine.requestStop(Enums::eState::PopUp);
	mGameContext.stateStack.addStopRequest(Enums::eState::PopUp);

	if (!mGameContext.popUpStack.isEmpty())
	{
		mGameContext.stateStack.addStartRequest(Enums::eState::PopUp);
	}
}
