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

	void setNewText(std::wstring newString);
	void showAll();
private:
	void wrapCompleteString();

	std::wstring mCompleteString;
	size_t mCurrentLength;
	std::wstring mCurrentString;
	std::wstring mWrappedString;

	float mTimerShow;
	float mMaxTimerShow;

	sf::Font& mFont;
};

