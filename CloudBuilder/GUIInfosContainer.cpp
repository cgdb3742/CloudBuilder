#include "GUIInfosContainer.h"



GUIInfosContainer::GUIInfosContainer():
	mCurrentTopic(0),
	mCurrentText(0),
	mText(sf::Vector2f(0.5f,0.5f)),
	mScrollerUp(*this, -1, sf::Vector2f(0.95f, 0.2f)),
	mScrollerDown(*this, 1, sf::Vector2f(0.95f, 0.8f))
{
	//Create mStrings...
	mStrings = { {"Test 0.1, too long for one line because waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga waga", "Test 0.2", "Test 0.3" },{ "Test 1.1" },{ "Test 2.1" },{ "Test 3.1" } };
	mTopicNames = { "Label 0","Label 1","Label 2","Label 3"};

	for (unsigned int i = 0; i < mStrings.size(); i++)
	{
		mTopics.push_back(GUIInfosTopic(*this, i, mTopicNames[i], sf::Vector2f(0.05f, (2.0f * i + 1.0f) / (2.0f * mStrings.size()))));
	}
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
	float margin = minSize * 0.15f;

	sf::Vector2f childBoundingBox = sf::Vector2f(minSize - 2.0f * margin, (minSize - 2.0f* margin) / (1.0f + mStrings.size()));

	for (GUIInfosTopic& topic : mTopics)
	{
		topic.setBoundingBoxCurrent(childBoundingBox);
		topic.setPositionAll(minCorner + sf::Vector2f(margin, margin), maxBox - 2.0f * sf::Vector2f(margin, margin));
	}

	childBoundingBox = sf::Vector2f(minSize / 1.5f - 2.0f * margin, minSize / 1.5f - 2.0f * margin);
	mScrollerUp.setBoundingBoxCurrent(childBoundingBox);
	mScrollerUp.setPositionAll(minCorner + sf::Vector2f(margin, margin), maxBox - 2.0f * sf::Vector2f(margin, margin));
	mScrollerDown.setBoundingBoxCurrent(childBoundingBox);
	mScrollerDown.setPositionAll(minCorner + sf::Vector2f(margin, margin), maxBox - 2.0f * sf::Vector2f(margin, margin));

	childBoundingBox = sf::Vector2f(mBoundingBox.x * 3.5 / 5.0f - 2.0f * margin, minSize - 2.0f * margin);
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
