#pragma once

#include <vector>
#include <string>
#include "GameEntity.h"
#include "StringConvertible.h"

class CloudCanvas;

class CloudPicture :
	public GameEntity,
	public StringConvertible
{
public:
	CloudPicture(GameContext& gameContext);
	CloudPicture(GameContext& gameContext, unsigned int width, unsigned int height);
	CloudPicture(GameContext& gameContext, unsigned int width, unsigned int height, std::string values);
	CloudPicture(GameContext& gameContext, CloudCanvas& canvas);
	~CloudPicture();

	bool get(unsigned int i, unsigned int j);
	std::string getPicture();
	bool getPictureFromString(unsigned int width, unsigned int height, std::string values);
	bool getPictureFromString(std::string values);

	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);

	unsigned int getWidth();
	unsigned int getHeight();

	virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);
private:
	unsigned int mWidth;
	unsigned int mHeight;
	std::vector<std::vector<bool>> mPicture;
};

