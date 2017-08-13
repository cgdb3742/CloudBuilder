#pragma once
#include <string>
#include "GUIButton.h"
class GUIInfosText :
	public GUIButton
{
public:
	GUIInfosText(sf::Vector2f positionRatio);
	~GUIInfosText();

	virtual void updateCurrent(sf::Time dt);
	virtual void clicked();
	//virtual void handleEventCurrent(const sf::Event& event);
	virtual void drawCurrent(sf::RenderTarget& target);

	void setNewText(std::string newString);
	void showAll();
private:
	void wrapCurrentString();

	std::string mCompleteString;
	unsigned int mCurrentLength;
	std::string mCurrentString;
	std::string mWrappedString;

	float mTimerShow;
	float mMaxTimerShow;

	//sf::Font& mFont;
};

