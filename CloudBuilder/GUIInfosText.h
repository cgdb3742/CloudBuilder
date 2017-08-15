#pragma once
#include <string>
#include "GUIButton.h"
class GUIInfosText :
	public GUIButton
{
public:
	GUIInfosText(GameContext& gameContext, sf::Vector2f positionRatio);
	~GUIInfosText();

	virtual void updateCurrent(sf::Time dt);
	virtual void clicked();
	//virtual void handleEventCurrent(const sf::Event& event);
	virtual void drawCurrent(sf::RenderTarget& target);

	virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);

	void setNewText(std::string newString);
	void showAll();
private:
	void wrapCompleteString();

	std::string mCompleteString;
	size_t mCurrentLength;
	std::string mCurrentString;
	std::string mWrappedString;

	float mTimerShow;
	float mMaxTimerShow;

	sf::Font& mFont;
};

