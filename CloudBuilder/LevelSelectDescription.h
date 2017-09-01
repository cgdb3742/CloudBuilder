#pragma once
#include "GUIButton.h"
class LevelSelectDescription :
	public GUIButton
{
public:
	LevelSelectDescription(GameContext& gameContext, sf::Vector2f positionRatio);
	~LevelSelectDescription();

	void setLevelText(unsigned int worldId, unsigned int levelId);
	void wrapDescription(std::string& desc);

	virtual void drawCurrent(sf::RenderTarget & target);

	virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);
private:
	std::string mText;
	std::string mWrappedText;

	sf::Font& mFont;
};

