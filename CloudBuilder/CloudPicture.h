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
	CloudPicture(GameContext& gameContext, std::wstring source);
	CloudPicture(GameContext& gameContext, unsigned int width, unsigned int height);
	CloudPicture(GameContext& gameContext, unsigned int width, unsigned int height, std::string values);
	CloudPicture(GameContext& gameContext, CloudCanvas& canvas);
	CloudPicture(const CloudPicture & toCopy);
	CloudPicture operator=(const CloudPicture & toCopy);
	~CloudPicture();

	bool get(unsigned int i, unsigned int j);
	bool compare(CloudPicture& picture);

	std::wstring getPicture();
	bool getPictureFromString(unsigned int width, unsigned int height, std::wstring values);
	bool getPictureFromString(std::wstring values);

	virtual std::wstring convertToString();
	virtual bool convertFromString(std::wstring& source);

	virtual void convertFromCanvas(CloudCanvas& canvas);

	unsigned int getWidth();
	unsigned int getHeight();

	virtual void drawTo(sf::RenderTarget& target, sf::Vector2f topLeftCorner, sf::Vector2f boundingBox);
	virtual void drawCurrent(sf::RenderTarget& target);

	virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);
private:
	unsigned int mWidth;
	unsigned int mHeight;
	std::vector<std::vector<bool>> mPicture;
};

