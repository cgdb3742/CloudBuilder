// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>
#include "CloudCanvas.h"
#include "CloudPicture.h"



CloudCanvas::CloudCanvas(GameContext& gameContext):
	GameEntity(gameContext),
	mWidth(1),
	mHeight(1),
	mCanvas(mWidth, std::vector<CloudSquare>(mHeight, CloudSquare(gameContext)))
{
	std::cout << "Creating GameEntity : CloudCanvas ( " << mWidth << " * " << mHeight <<" )." << std::endl;
}

CloudCanvas::CloudCanvas(GameContext & gameContext, std::wstring source) :
	GameEntity(gameContext),
	mWidth(1),
	mHeight(1),
	mCanvas(mWidth, std::vector<CloudSquare>(mHeight, CloudSquare(gameContext)))
{
	convertFromString(source);
}

CloudCanvas::CloudCanvas(GameContext& gameContext, unsigned int width, unsigned int height):
	GameEntity(gameContext),
	mWidth(width),
	mHeight(height),
	mCanvas(width, std::vector<CloudSquare>(height, CloudSquare(gameContext)))
{
	std::cout << "Creating GameEntity : CloudCanvas ( " << mWidth << " * " << mHeight << " )." << std::endl;

	//mCanvas[2][3].setIsCloud(true);
	//mCanvas[9][4].setIsCloud(true);
	//mCanvas[5][0].setIsCloud(true);
	//mCanvas[1][7].setIsCloud(true);
	//mCanvas[7][6].setIsCloud(true);
	//mCanvas[0][3].setIsCloud(true);
	//mCanvas[4][2].setIsCloud(true);
	//mCanvas[1][9].setIsCloud(true);
	//mCanvas[8][3].setIsCloud(true);
	//mCanvas[2][3].setColor(Enums::eColor::Green);
	//mCanvas[4][5].setColor(Enums::eColor::Yellow);
	//mCanvas[9][1].setColor(Enums::eColor::Red);

	//std::cout << mCanvas[2][3].getIsCloud() << std::endl;
	//std::cout << mCanvas[4][5].getIsCloud() << std::endl;
}

CloudCanvas::CloudCanvas(GameContext& gameContext, CloudPicture & picture):
	GameEntity(gameContext),
	mWidth(picture.getWidth()),
	mHeight(picture.getHeight()),
	mCanvas(mWidth, std::vector<CloudSquare>(mHeight, CloudSquare(mGameContext)))
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
	return (i >= 0 && i < mWidth && j >= 0 && j < mHeight);
}

CloudSquare& CloudCanvas::get(unsigned int i, unsigned int j)
{
	assert(exists(i, j));
	
	//std::cout << "i " << i << " j " << j << std::endl;

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
	case Enums::eDir::Down: return (j >= mHeight - 1);
	default: return false;
	}
}

void CloudCanvas::addColumn()
{
	mWidth++;

	mCanvas.push_back(std::vector<CloudSquare>(mHeight, CloudSquare(mGameContext)));

	updateChildsVectorAll();
	//setPositionAll(mTopLeftCorner, mBoundingBox);
}

void CloudCanvas::removeColumn()
{
	if (mWidth <= 1)
	{
		return;
	}

	mWidth--;

	mCanvas.pop_back();

	updateChildsVectorAll();
	//setPositionAll(mTopLeftCorner, mBoundingBox);
}

void CloudCanvas::addRow()
{
	mHeight++;

	for (unsigned int i = 0; i < mWidth; i++)
	{
		mCanvas[i].push_back(CloudSquare(mGameContext));
	}

	updateChildsVectorAll();
	//setPositionAll(mTopLeftCorner, mBoundingBox);
}

void CloudCanvas::removeRow()
{
	if (mHeight <= 1)
	{
		return;
	}

	mHeight--;

	for (unsigned int i = 0; i < mWidth; i++)
	{
		mCanvas[i].pop_back();
	}

	updateChildsVectorAll();
	//setPositionAll(mTopLeftCorner, mBoundingBox);
}

bool CloudCanvas::convertFromPicture(CloudPicture & picture)
{
	mWidth = picture.getWidth();
	mHeight = picture.getHeight();
	mCanvas = std::vector<std::vector<CloudSquare>>(mWidth, std::vector<CloudSquare>(mHeight, CloudSquare(mGameContext)));

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			mCanvas[i][j].setIsCloud(picture.get(i, j));
		}
	}

	updateChildsVectorAll();
	setPositionChilds(mTopLeftCorner, mBoundingBox);

	return true;
}

std::wstring CloudCanvas::convertToString()
{
	CloudPicture pic(mGameContext, *this);

	return pic.convertToString();
}

bool CloudCanvas::convertFromString(std::wstring & source)
{
	CloudPicture pic(mGameContext);

	if (pic.convertFromString(source))
	{
		return convertFromPicture(pic);
	}

	return false;
}

void CloudCanvas::drawCurrent(sf::RenderTarget & target)
{
	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			if (getIsCloud(i, j))
			{
				if (!getIsCloud(i - 1, j))
				{
					drawCloudEdge(i - 1, j, Enums::eDir::Right, target);
				}
				if (!getIsCloud(i + 1, j))
				{
					drawCloudEdge(i + 1, j, Enums::eDir::Left, target);
				}
				if (!getIsCloud(i, j - 1))
				{
					drawCloudEdge(i, j - 1, Enums::eDir::Down, target);
				}
				if (!getIsCloud(i, j + 1))
				{
					drawCloudEdge(i, j + 1, Enums::eDir::Up, target);
				}
			}
		}
	}
}

void CloudCanvas::drawCloudEdge(int i,  int j, Enums::eDir dir, sf::RenderTarget & target)
{
	if (dir == Enums::eDir::Center)
	{
		return;
	}

	sf::Vector2f squareSize = mCanvas[0][0].getBoundingBox();

	sf::ConvexShape edge1;
	edge1.setPointCount(6);
	sf::ConvexShape edge2;
	edge2.setPointCount(6);
	sf::ConvexShape edge3;
	edge3.setPointCount(6);
	sf::ConvexShape edge4;
	edge4.setPointCount(6);

	switch (dir)
	{
	case Enums::eDir::Left:
		edge1.setPoint(0, sf::Vector2f(0.0f, 0.0f));
		edge1.setPoint(1, sf::Vector2f(0.02f, 0.05f));
		edge1.setPoint(2, sf::Vector2f(0.03f, 0.10f));
		edge1.setPoint(3, sf::Vector2f(0.03f, 0.15f));
		edge1.setPoint(4, sf::Vector2f(0.02f, 0.20f));
		edge1.setPoint(5, sf::Vector2f(0.0f, 0.25f));
		for (unsigned int i = 0; i < 6; i++)
		{
			edge2.setPoint(i, edge1.getPoint(i) + sf::Vector2f(0.0f, 0.25f));
			edge3.setPoint(i, edge1.getPoint(i) + sf::Vector2f(0.0f, 0.5f));
			edge4.setPoint(i, edge1.getPoint(i) + sf::Vector2f(0.0f, 0.75f));
		}
		break;
	case Enums::eDir::Right:
		edge1.setPoint(0, sf::Vector2f(1.0f, 0.0f));
		edge1.setPoint(1, sf::Vector2f(0.98f, 0.05f));
		edge1.setPoint(2, sf::Vector2f(0.97f, 0.10f));
		edge1.setPoint(3, sf::Vector2f(0.97f, 0.15f));
		edge1.setPoint(4, sf::Vector2f(0.98f, 0.20f));
		edge1.setPoint(5, sf::Vector2f(1.0f, 0.25f));
		for (unsigned int i = 0; i < 6; i++)
		{
			edge2.setPoint(i, edge1.getPoint(i) + sf::Vector2f(0.0f, 0.25f));
			edge3.setPoint(i, edge1.getPoint(i) + sf::Vector2f(0.0f, 0.5f));
			edge4.setPoint(i, edge1.getPoint(i) + sf::Vector2f(0.0f, 0.75f));
		}
		break;
	case Enums::eDir::Up:
		edge1.setPoint(0, sf::Vector2f(0.0f, 0.0f));
		edge1.setPoint(1, sf::Vector2f(0.05f, 0.02f));
		edge1.setPoint(2, sf::Vector2f(0.1f, 0.03f));
		edge1.setPoint(3, sf::Vector2f(0.15f, 0.03f));
		edge1.setPoint(4, sf::Vector2f(0.2f, 0.02f));
		edge1.setPoint(5, sf::Vector2f(0.25f, 0.0f));
		for (unsigned int i = 0; i < 6; i++)
		{
			edge2.setPoint(i, edge1.getPoint(i) + sf::Vector2f(0.25f, 0.0f));
			edge3.setPoint(i, edge1.getPoint(i) + sf::Vector2f(0.5f, 0.0f));
			edge4.setPoint(i, edge1.getPoint(i) + sf::Vector2f(0.75f, 0.0f));
		}
		break;
	case Enums::eDir::Down:
		edge1.setPoint(0, sf::Vector2f(0.0f, 1.0f));
		edge1.setPoint(1, sf::Vector2f(0.05f, 0.98f));
		edge1.setPoint(2, sf::Vector2f(0.1f, 0.97f));
		edge1.setPoint(3, sf::Vector2f(0.15f, 0.97f));
		edge1.setPoint(4, sf::Vector2f(0.2f, 0.98f));
		edge1.setPoint(5, sf::Vector2f(0.25f, 1.0f));
		for (unsigned int i = 0; i < 6; i++)
		{
			edge2.setPoint(i, edge1.getPoint(i) + sf::Vector2f(0.25f, 0.0f));
			edge3.setPoint(i, edge1.getPoint(i) + sf::Vector2f(0.5f, 0.0f));
			edge4.setPoint(i, edge1.getPoint(i) + sf::Vector2f(0.75f, 0.0f));
		}
		break;
	}

	edge1.setScale(squareSize);
	edge1.setPosition(mTopLeftCorner + sf::Vector2f(static_cast<float>(i) * squareSize.x, static_cast<float>(j) * squareSize.y));
	edge1.setFillColor(sf::Color(191, 191, 191));
	target.draw(edge1);
	edge2.setScale(squareSize);
	edge2.setPosition(mTopLeftCorner + sf::Vector2f(static_cast<float>(i) * squareSize.x, static_cast<float>(j) * squareSize.y));
	edge2.setFillColor(sf::Color(191, 191, 191));
	target.draw(edge2);
	edge3.setScale(squareSize);
	edge3.setPosition(mTopLeftCorner + sf::Vector2f(static_cast<float>(i) * squareSize.x, static_cast<float>(j) * squareSize.y));
	edge3.setFillColor(sf::Color(191, 191, 191));
	target.draw(edge3);
	edge4.setScale(squareSize);
	edge4.setPosition(mTopLeftCorner + sf::Vector2f(static_cast<float>(i) * squareSize.x, static_cast<float>(j) * squareSize.y));
	edge4.setFillColor(sf::Color(191, 191, 191));
	target.draw(edge4);
}

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
