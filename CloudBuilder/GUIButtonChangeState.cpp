#include "GUIButtonChangeState.h"
#include "Game.h"



GUIButtonChangeState::GUIButtonChangeState(GameContext& gameContext, sf::Vector2f positionRatio, Enums::eState currentState, Enums::eState newState, sf::Color fillColor, sf::Color outlineColor, std::string text):
	GUIButton(gameContext,positionRatio),
	mCurrentState(currentState),
	mNewState(newState),
	mFillColor(fillColor),
	mOutlineColor(outlineColor),
	mText(text),
	mFont(gameContext.resourceHandler.getFont(FontHandler::Arial))

{
}

GUIButtonChangeState::GUIButtonChangeState(GameContext & gameContext, sf::Vector2f positionRatio, Enums::eState currentState, Enums::eState newState, sf::Color fillColor, sf::Color outlineColor) :
	GUIButton(gameContext, positionRatio),
	mCurrentState(currentState),
	mNewState(newState),
	mFillColor(fillColor),
	mOutlineColor(outlineColor),
	mText(gameContext.gameData.stateName[newState]),
	mFont(gameContext.resourceHandler.getFont(FontHandler::Arial))
{
}


GUIButtonChangeState::~GUIButtonChangeState()
{
}

void GUIButtonChangeState::clicked()
{
	mGameContext.stateStack.addStopRequest(mCurrentState);
	mGameContext.stateStack.addStartRequest(mNewState);
}

void GUIButtonChangeState::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape background(mBoundingBox);
	background.setPosition(mTopLeftCorner);
	background.setFillColor(mFillColor);

	if (mOutlineColor.a > 0)
	{
		background.setOutlineThickness(1.0f);
		background.setOutlineColor(mOutlineColor);
	}

	target.draw(background);

	sf::Text text;
	text.setFont(mFont);
	text.setString(mText);
	text.setCharacterSize(36);
	text.setFillColor(sf::Color(0, 0, 0));
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	//text.setOrigin(sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height) / 2.0f);
	float scale = std::min(mBoundingBox.x / textRect.width, mBoundingBox.y / textRect.height);
	text.scale(sf::Vector2f(scale, scale) * 0.8f);
	text.setPosition(mTopLeftCorner + mBoundingBox / 2.0f);
	target.draw(text);
}
