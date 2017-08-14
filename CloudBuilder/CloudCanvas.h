#pragma once

#include <vector>
//#include <SFML/Graphics.hpp>
#include "GameEntity.h"
#include "StringConvertible.h"
#include "CloudSquare.h"

class CloudPicture;

class CloudCanvas :
	public GameEntity,
	public StringConvertible
{
public:
	CloudCanvas(GameContext& gameContext);
	CloudCanvas(GameContext& gameContext, std::string source);
	CloudCanvas(GameContext& gameContext, unsigned int width, unsigned int height);
	CloudCanvas(GameContext& gameContext, CloudPicture& picture);
	~CloudCanvas();

	bool exists(unsigned int i, unsigned int j);
	CloudSquare& get(unsigned int i, unsigned int j);
	CloudSquare& getLeft(unsigned int i, unsigned int j);
	CloudSquare& getRight(unsigned int i, unsigned int j);
	CloudSquare& getUp(unsigned int i, unsigned int j);
	CloudSquare& getDown(unsigned int i, unsigned int j);

	unsigned int getWidth();
	unsigned int getHeight();

	Enums::eColor getColor(unsigned int i, unsigned int j);
	bool getIsCloud(unsigned int i, unsigned int j);
	bool getIsBorder(unsigned int i, unsigned int j, Enums::eDir dir);

	bool convertFromPicture(CloudPicture& picture);
	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);
	
	//virtual void drawCurrent(sf::RenderTarget & target);
	virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
	virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);
protected:
	virtual void updateChildsVector();
private:
	unsigned int mWidth;
	unsigned int mHeight;
	std::vector<std::vector<CloudSquare>> mCanvas; //TODO: Convert CloudSquare to unique_ptr<CloudSquare> ?

	//sf::Vector2f mCornerPos;
	//sf::Vector2f mSquareSize;
};

