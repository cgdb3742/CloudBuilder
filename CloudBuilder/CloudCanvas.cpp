// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>
#include "CloudCanvas.h"
#include "CloudPicture.h"



CloudCanvas::CloudCanvas():
	mWidth(1),
	mHeight(1),
	mCanvas(mWidth, std::vector<CloudSquare>(mHeight, CloudSquare()))
{
	std::cout << "Creating GameEntity : CloudCanvas ( " << mWidth << " * " << mHeight <<" )." << std::endl;
}

CloudCanvas::CloudCanvas(unsigned int width, unsigned int height):
	mWidth(width),
	mHeight(height),
	mCanvas(width, std::vector<CloudSquare>(height, CloudSquare()))
{
	std::cout << "Creating GameEntity : CloudCanvas ( " << mWidth << " * " << mHeight << " )." << std::endl;

	mCanvas[2][3].setIsCloud(true);
	mCanvas[9][4].setIsCloud(true);
	mCanvas[5][0].setIsCloud(true);
	mCanvas[1][7].setIsCloud(true);
	mCanvas[7][6].setIsCloud(true);
	mCanvas[0][3].setIsCloud(true);
	mCanvas[4][2].setIsCloud(true);
	mCanvas[1][9].setIsCloud(true);
	mCanvas[8][3].setIsCloud(true);
	//mCanvas[2][3].setColor(Enums::eColor::Green);
	//mCanvas[4][5].setColor(Enums::eColor::Yellow);
	//mCanvas[9][1].setColor(Enums::eColor::Red);

	//std::cout << mCanvas[2][3].getIsCloud() << std::endl;
	//std::cout << mCanvas[4][5].getIsCloud() << std::endl;
}

CloudCanvas::CloudCanvas(CloudPicture & picture):
	mWidth(picture.getWidth()),
	mHeight(picture.getHeight()),
	mCanvas(mWidth, std::vector<CloudSquare>(mHeight, CloudSquare()))
{
	std::cout << "Creating GameEntity : CloudCanvas ( " << mWidth << " * " << mHeight << " )." << std::endl;

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			mCanvas[i][j].setIsCloud(picture.get(i, j));
		}
	}
}

CloudCanvas::~CloudCanvas()
{
}

bool CloudCanvas::exists(unsigned int i, unsigned int j)
{
	return (i >= 0 && i < mHeight && j >= 0 && j < mWidth);
}

CloudSquare& CloudCanvas::get(unsigned int i, unsigned int j)
{
	assert(exists(i, j));
	
	return mCanvas[i][j];
}

CloudSquare& CloudCanvas::getLeft(unsigned int i, unsigned int j)
{
	return get(i - 1, j);
}

CloudSquare& CloudCanvas::getRight(unsigned int i, unsigned int j)
{
	return get(i + 1, j);
}

CloudSquare& CloudCanvas::getUp(unsigned int i, unsigned int j)
{
	return get(i, j - 1);
}

CloudSquare& CloudCanvas::getDown(unsigned int i, unsigned int j)
{
	return get(i, j + 1);
}

unsigned int CloudCanvas::getWidth()
{
	return mWidth;
}

unsigned int CloudCanvas::getHeight()
{
	return mHeight;
}

Enums::eColor CloudCanvas::getColor(unsigned int i, unsigned int j)
{
	if (exists(i, j))
	{
		return mCanvas[i][j].getColor();
	}
	else
	{
		return Enums::eColor::NoColor;
	}
}

bool CloudCanvas::getIsCloud(unsigned int i, unsigned int j)
{
	if (exists(i, j))
	{
		return mCanvas[i][j].getIsCloud();
	}
	else
	{
		return false;
	}
}

bool CloudCanvas::getIsBorder(unsigned int i, unsigned int j, Enums::eDir dir)
{
	switch (dir)
	{
	case Enums::eDir::Center: return (getIsBorder(i, j, Enums::eDir::Left) || getIsBorder(i, j, Enums::eDir::Right) || getIsBorder(i, j, Enums::eDir::Up) || getIsBorder(i, j, Enums::eDir::Down));
	case Enums::eDir::Left: return (i <= 0);
	case Enums::eDir::Right: return (i >= mWidth - 1);
	case Enums::eDir::Up: return (j <= 0);
	case Enums::eDir::Down: return (i >= mHeight - 1);
	default: return false;
	}
}

bool CloudCanvas::convertFromPicture(CloudPicture & picture)
{
	mWidth = picture.getWidth();
	mHeight = picture.getHeight();
	mCanvas = std::vector<std::vector<CloudSquare>>(mWidth, std::vector<CloudSquare>(mHeight, CloudSquare()));

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			mCanvas[i][j].setIsCloud(picture.get(i, j));
		}
	}

	return true;
}

std::string CloudCanvas::convertToString()
{
	CloudPicture pic(*this);

	return pic.convertToString();
}

bool CloudCanvas::convertFromString(std::string & source)
{
	CloudPicture pic;

	if (pic.convertFromString(source))
	{
		return convertFromPicture(pic);
	}

	return false;
}

//void CloudCanvas::drawCurrent(sf::RenderTarget & target)
//{
//	//std::cout << "Drawing CloudCanvas." << std::endl;
//
//	for (unsigned int i = 0; i <= mWidth; i++)
//	{
//		sf::RectangleShape line(sf::Vector2f(1.0f, mBoundingBox.y));
//		line.setPosition(sf::Vector2f(mTopLeftCorner.x + mBoundingBox.x * i / mWidth, mTopLeftCorner.y));
//		line.setFillColor(sf::Color(127, 127, 127));
//		target.draw(line);
//	}
//
//	for (unsigned int j = 0; j <= mHeight; j++)
//	{
//		sf::RectangleShape line(sf::Vector2f(mBoundingBox.x, 1.0f));
//		line.setPosition(sf::Vector2f(mTopLeftCorner.x, mTopLeftCorner.y + mBoundingBox.y * j / mHeight));
//		line.setFillColor(sf::Color(127, 127, 127));
//		target.draw(line);
//	}
//}

void CloudCanvas::setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	float squareSize = mBoundingBox.x / mWidth;

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			mCanvas[i][j].setPositionAll(sf::Vector2f(mTopLeftCorner.x + i * squareSize, mTopLeftCorner.y + j *squareSize), sf::Vector2f(squareSize, squareSize));
		}
	}
}

void CloudCanvas::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	float squareSize = std::min(maxBox.x / mWidth, maxBox.y / mHeight);
	float spaceX = maxBox.x - (squareSize * mWidth);
	float spaceY = maxBox.y - (squareSize * mHeight);
	float cornerX = minCorner.x + spaceX / 2.0f;
	float cornerY = minCorner.y + spaceY / 2.0f;

	mTopLeftCorner = sf::Vector2f(cornerX, cornerY);
	mBoundingBox = sf::Vector2f(squareSize*mWidth, squareSize*mHeight);
}

void CloudCanvas::updateChildsVector()
{
	mChilds.clear();

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			mChilds.push_back(mCanvas[i][j]);
		}
	}
}
