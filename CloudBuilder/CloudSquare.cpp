#include <iostream>
#include "CloudSquare.h"



CloudSquare::CloudSquare(GameContext& gameContext):
	GameEntity(gameContext),
	mColor(Enums::eColor::NoColor),
	mIsCloud(false)
{
	std::cout << "Creating GameEntity : CloudSquare." << std::endl;
}

CloudSquare::CloudSquare(GameContext& gameContext, bool isCloud):
	GameEntity(gameContext),
	mColor(Enums::eColor::NoColor),
	mIsCloud(isCloud)
{
	std::cout << "Creating GameEntity : CloudSquare." << std::endl;
}


CloudSquare::~CloudSquare()
{
	
}

Enums::eColor CloudSquare::getColor()
{
	return mColor;
}

bool CloudSquare::getIsCloud()
{
	return mIsCloud;
}

void CloudSquare::setColor(Enums::eColor newColor)
{
	mColor = newColor;
}

void CloudSquare::setIsCloud(bool newIsCloud)
{
	mIsCloud = newIsCloud;
}

void CloudSquare::drawCurrent(sf::RenderTarget & target)
{
	
	//std::cout << "Drawing CloudSquare : mIsCloud." << std::endl;
	
	sf::RectangleShape cloud(mBoundingBox);
	cloud.setPosition(mTopLeftCorner);
	if (mIsCloud)
	{
		cloud.setFillColor(sf::Color(191, 191, 191));
	}
	else
	{
		cloud.setFillColor(sf::Color(0, 0, 0, 0));
	}
	cloud.setOutlineThickness(1.0f);
	cloud.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(cloud);
	if (mColor != Enums::eColor::NoColor)
	{
		//std::cout << "Drawing CloudSquare : mColor." << std::endl;

		sf::CircleShape light(mBoundingBox.x / 2.0f);
		light.setPosition(mTopLeftCorner);
		sf::Color col = Enums::getColor(mColor);
		col.a /= 2;
		light.setFillColor(col);
		target.draw(light);
	}
}
