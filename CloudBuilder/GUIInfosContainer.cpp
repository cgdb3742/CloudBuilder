#include <iostream>
#include "GUIInfosContainer.h"
#include "Game.h"



GUIInfosContainer::GUIInfosContainer(GameContext& gameContext) :
	GameEntity(gameContext),
	mCurrentTopic(0),
	mCurrentText(0),
	mStrings(gameContext.levelData.infos),
	mText(gameContext, sf::Vector2f(0.5f,0.5f)),
	mScrollerUp(gameContext, *this, -1, sf::Vector2f(0.95f, 0.2f)),
	mScrollerDown(gameContext, *this, 1, sf::Vector2f(0.95f, 0.8f)),
	mLanguage(gameContext.saveData.currentLanguage)
{
	std::cout << "Creating GameEntity : GUIInfosContainer." << std::endl;

	////Create mStrings...
	//mStrings = gameContext.levelData.infos;

	for (unsigned int i = 0; i < mStrings.size(); i++)
	{
		mTopics.push_back(GUIInfosTopic(gameContext, *this, i, sf::Vector2f(0.075f, (2.0f * i + 1.0f) / (2.0f * mStrings.size()))));
	}

	setNewText(0, 0);
}


GUIInfosContainer::~GUIInfosContainer()
{
}

void GUIInfosContainer::setNewText(unsigned int topic, unsigned int text)
{
	mCurrentTopic = topic;
	mCurrentText = text;

	mText.setNewText(mStrings[topic][text]);
}

bool GUIInfosContainer::canScrollUp()
{
	return (mCurrentText > 0);
}

bool GUIInfosContainer::canScrollDown()
{
	return (mCurrentText < mStrings[mCurrentTopic].size() - 1);
}

void GUIInfosContainer::scrollUp()
{
	if (canScrollUp())
	{
		setNewText(mCurrentTopic, mCurrentText - 1);
	}
}

void GUIInfosContainer::scrollDown()
{
	if (canScrollDown())
	{
		setNewText(mCurrentTopic, mCurrentText + 1);
	}
}

void GUIInfosContainer::changeTopic(unsigned int newTopic)
{
	if (newTopic != mCurrentTopic &&  newTopic >= 0 && newTopic < mTopics.size())
	{
		setNewText(newTopic, 0);
	}
}

void GUIInfosContainer::updateCurrent(sf::Time dt)
{
	if (mLanguage != mGameContext.saveData.currentLanguage)
	{
		mLanguage = mGameContext.saveData.currentLanguage;
		mStrings = mGameContext.levelData.infos;
		setNewText(mCurrentTopic, mCurrentText);
	}
}

void GUIInfosContainer::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape background(mBoundingBox);
	background.setPosition(mTopLeftCorner);
	background.setFillColor(sf::Color(0, 191, 0, 127));
	target.draw(background);
}

void GUIInfosContainer::setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	float minSize = std::min(mBoundingBox.x / 5.0f, mBoundingBox.y);
	float margin = minSize * 0.1f;

	sf::Vector2f childBoundingBox = sf::Vector2f(minSize - 2.0f * margin, (minSize - 2.0f* margin) / (1.0f + mStrings.size()));

	for (GUIInfosTopic& topic : mTopics)
	{
		topic.setBoundingBoxCurrent(childBoundingBox);
		topic.setPositionAll(minCorner + sf::Vector2f(margin, margin), maxBox - 2.0f * sf::Vector2f(margin, margin));
	}

	childBoundingBox = sf::Vector2f(minSize / 2.0f - 2.0f * margin, minSize / 2.0f - 2.0f * margin);
	mScrollerUp.setBoundingBoxCurrent(childBoundingBox);
	mScrollerUp.setPositionAll(minCorner + sf::Vector2f(margin, margin), maxBox - 2.0f * sf::Vector2f(margin, margin));
	mScrollerDown.setBoundingBoxCurrent(childBoundingBox);
	mScrollerDown.setPositionAll(minCorner + sf::Vector2f(margin, margin), maxBox - 2.0f * sf::Vector2f(margin, margin));

	childBoundingBox = sf::Vector2f(mBoundingBox.x * 3.5f / 5.0f - 2.0f * margin, minSize - 2.0f * margin);
	mText.setBoundingBoxCurrent(childBoundingBox);
	mText.setPositionAll(minCorner + sf::Vector2f(margin, margin), maxBox - 2.0f * sf::Vector2f(margin, margin));
}

void GUIInfosContainer::updateChildsVector()
{
	mChilds.clear();

	mChilds.push_back(mText);
	mChilds.push_back(mScrollerUp);
	mChilds.push_back(mScrollerDown);

	for (GUIInfosTopic& topic : mTopics)
	{
		mChilds.push_back(topic);
	}
}
