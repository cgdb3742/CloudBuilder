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
	GUIInfosContainer(GameContext& gameContext);
	~GUIInfosContainer();

	void setNewText(unsigned int topic, unsigned int text);
	bool canScrollUp();
	bool canScrollDown();
	void scrollUp();
	void scrollDown();
	void changeTopic(unsigned int newTopic);

	virtual void updateCurrent(sf::Time dt);

	virtual void drawCurrent(sf::RenderTarget& target);

	virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
protected:
	virtual void updateChildsVector();
private:
	GUIInfosText mText;
	std::vector<GUIInfosTopic> mTopics;
	GUIInfosScroller mScrollerUp;
	GUIInfosScroller mScrollerDown;
	std::vector<std::vector<std::string>>& mStrings;

	unsigned int mCurrentTopic;
	unsigned int mCurrentText;

	std::string mLanguage;

	//sf::Font mFont;
};

