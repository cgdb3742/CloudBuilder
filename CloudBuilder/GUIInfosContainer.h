#pragma once
#include <vector>
#include <string>
#include "GameEntity.h"
#include "GUIInfosText.h"
#include "GUIInfosTopic.h"
#include "GUIInfosScroller.h"

class GUIInfosContainer :
	public GameEntity
{
public:
	GUIInfosContainer();
	~GUIInfosContainer();

	void setNewText(unsigned int topic, unsigned int text);
	bool canScrollUp();
	bool canScrollDown();
	void scrollUp();
	void scrollDown();
	void changeTopic(unsigned int newTopic);

	virtual void drawCurrent(sf::RenderTarget& target);

	virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
protected:
	virtual void updateChildsVector();
private:
	GUIInfosText mText;
	std::vector<GUIInfosTopic> mTopics;
	GUIInfosScroller mScrollerUp;
	GUIInfosScroller mScrollerDown;
	std::vector<std::vector<std::string>> mStrings;
	std::vector<std::string> mTopicNames;

	unsigned int mCurrentTopic;
	unsigned int mCurrentText;

	//sf::Font mFont;
};

