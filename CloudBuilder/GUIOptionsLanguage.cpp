#include "GUIOptionsLanguage.h"
#include "Game.h"



GUIOptionsLanguage::GUIOptionsLanguage(GameContext & gameContext, sf::Vector2f positionRatio, unsigned int id, sf::Color normalFillColor, sf::Color selectedFillColor, sf::Color outlineColor):
	GUIButton(gameContext, positionRatio),
	mId(id),
	mNormalFillColor(normalFillColor),
	mSelectedFillColor(selectedFillColor),
	mOutlineColor(outlineColor),
	mFont(gameContext.resourceHandler.getFont(FontHandler::Arial))
{
}


GUIOptionsLanguage::~GUIOptionsLanguage()
{
}

void GUIOptionsLanguage::clicked()
{
	mGameContext.dataReader.writeLanguage(mGameContext.gameData.availableLanguageTag[mId]);
}

void GUIOptionsLanguage::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape background(mBoundingBox);
	background.setPosition(mTopLeftCorner);

	if (mGameContext.saveData.currentLanguage == mGameContext.gameData.availableLanguageTag[mId])
	{
		background.setFillColor(mSelectedFillColor);
	}
	else
	{
		background.setFillColor(mNormalFillColor);
	}

	if (mOutlineColor.a > 0)
	{
		background.setOutlineThickness(1.0f);
		background.setOutlineColor(mOutlineColor);
	}

	target.draw(background);

	sf::Text text;
	text.setFont(mFont);
	text.setString(mGameContext.gameData.availableLanguageName[mId]);
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
