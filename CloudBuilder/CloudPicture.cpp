#include <iostream>
#include "CloudPicture.h"
#include "CloudCanvas.h"

CloudPicture::CloudPicture(GameContext& gameContext):
	GameEntity(gameContext),
	mWidth(1),
	mHeight(1),
	mPicture(mWidth, std::vector<bool>(mHeight, false))
{
	std::cout << "Creating GameEntity : CloudPicture." << std::endl;
}

CloudPicture::CloudPicture(GameContext & gameContext, std::wstring source) :
	GameEntity(gameContext),
	mWidth(1),
	mHeight(1),
	mPicture(mWidth, std::vector<bool>(mHeight, false))
{
	convertFromString(source);
}

CloudPicture::CloudPicture(GameContext& gameContext, unsigned int width, unsigned int height):
	GameEntity(gameContext),
	mWidth(width),
	mHeight(height),
	mPicture(width, std::vector<bool>(height, false))
{
	std::cout << "Creating GameEntity : CloudPicture." << std::endl;
}

CloudPicture::CloudPicture(GameContext& gameContext, unsigned int width, unsigned int height, std::string values) :
	GameEntity(gameContext),
	mWidth(width),
	mHeight(height),
	mPicture(width, std::vector<bool>(height, false))
{
	unsigned int l = values.length();

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			if (i + j*mHeight < l)
			{
				mPicture[i][j] = (values[i + j*mWidth] ==  '1');
			}
		}
	}
}

CloudPicture::CloudPicture(GameContext& gameContext, CloudCanvas & canvas):
	GameEntity(gameContext),
	mWidth(canvas.getWidth()),
	mHeight(canvas.getHeight()),
	mPicture(mWidth, std::vector<bool>(mHeight, false))
{
	convertFromCanvas(canvas);
}

CloudPicture::CloudPicture(const CloudPicture & toCopy) :
	GameEntity(toCopy.mGameContext),
	mWidth(toCopy.mWidth),
	mHeight(toCopy.mHeight),
	mPicture(toCopy.mPicture)
{
}

CloudPicture CloudPicture::operator=(const CloudPicture & toCopy)
{
	return CloudPicture(toCopy);
}


CloudPicture::~CloudPicture()
{
}

bool CloudPicture::get(unsigned int i, unsigned int j)
{
	if (i >= 0 && i < mWidth && j >= 0 && j < mHeight)
	{
		return mPicture[i][j];
	}
	else
	{
		return false;
	}
}

bool CloudPicture::compare(CloudPicture & picture)
{
	if (picture.getWidth() != getWidth() || picture.getHeight() != getHeight())
	{
		return false;
	}

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			if (picture.get(i, j) != get(i, j))
			{
				return false;
			}
		}
	}

	return true;
}

std::wstring CloudPicture::getPicture()
{
	std::wstring res(mWidth*mHeight, L'0');

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			if (mPicture[i][j])
			{
				res[i + j*mWidth] = L'1';
			}
		}
	}

	return res;
}

bool CloudPicture::getPictureFromString(unsigned int width, unsigned int height, std::wstring values)
{
	if (values.length() != width * height)
	{
		return false;
	}
	else
	{
		mWidth = width;
		mHeight = height;
		mPicture = std::vector<std::vector<bool>>(mWidth, std::vector<bool>(mHeight, false));
		return getPictureFromString(values);
	}
}

bool CloudPicture::getPictureFromString(std::wstring values)
{
	if (values.length() != mWidth * mHeight)
	{
		return false;
	}
	else
	{
		unsigned int l = values.length();

		for (unsigned int i = 0; i < mWidth; i++)
		{
			for (unsigned int j = 0; j < mHeight; j++)
			{
				if (i + j*mWidth< l)
				{
					mPicture[i][j] = (values[i + j*mWidth] == L'1');
				}
			}
		}

		return true;
	}
}

std::wstring CloudPicture::convertToString()
{
	return L"w" + std::to_wstring(mWidth) + L"h" + std::to_wstring(mHeight) + L"p" + getPicture();
}

bool CloudPicture::convertFromString(std::wstring & source)
{
	size_t wFound = source.find(L"w");
	size_t hFound = source.find(L"h");
	size_t pFound = source.find(L"p");

	if (wFound == std::wstring::npos || hFound == std::wstring::npos || pFound == std::wstring::npos)
	{
		return false;
	}

	try
	{
		unsigned int width = stoul(source.substr(wFound + 1, hFound - wFound - 1));
		unsigned int height = stoul(source.substr(hFound + 1, pFound - hFound - 1));
		std::wstring values = source.substr(pFound + 1, width * height);

		return getPictureFromString(width, height, values);
	}
	catch (...)
	{
		//TODO Handle exception
	}
	
	return false;
}

void CloudPicture::convertFromCanvas(CloudCanvas & canvas)
{
	mWidth = canvas.getWidth();
	mHeight = canvas.getHeight();
	mPicture = std::vector<std::vector<bool>>(mWidth, std::vector<bool>(mHeight, false));

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			mPicture[i][j] = canvas.get(i, j).getIsCloud();
		}
	}
}

unsigned int CloudPicture::getWidth()
{
	return mWidth;
}

unsigned int CloudPicture::getHeight()
{
	return mHeight;
}

void CloudPicture::drawTo(sf::RenderTarget & target, sf::Vector2f topLeftCorner, sf::Vector2f boundingBox)
{
	float xsize = boundingBox.x / mWidth;
	float ysize = boundingBox.y / mHeight;
	float size = std::min(xsize, ysize);
	float xmargin = (boundingBox.x - (size * mWidth)) / 2.0f;
	float ymargin = (boundingBox.y - (size * mHeight)) / 2.0f;

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			sf::RectangleShape space(sf::Vector2f(size, size));
			space.setPosition(topLeftCorner + sf::Vector2f(xmargin + i * size, ymargin + j * size));

			if (mPicture[i][j])
			{
				space.setFillColor(sf::Color(255, 255, 255));
			}
			else
			{
				space.setFillColor(sf::Color(0, 0, 0, 0));
				space.setOutlineThickness(1.0f);
				space.setOutlineColor(sf::Color(255, 255, 255));
			}

			target.draw(space);
		}
	}
}

void CloudPicture::drawCurrent(sf::RenderTarget & target)
{
	drawTo(target, mTopLeftCorner, mBoundingBox);
}

void CloudPicture::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	float squareSize = std::min(maxBox.x / mWidth, maxBox.y / mHeight);
	float spaceX = maxBox.x - (squareSize * mWidth);
	float spaceY = maxBox.y - (squareSize * mHeight);
	float cornerX = minCorner.x + spaceX / 2.0f;
	float cornerY = minCorner.x + spaceX / 2.0f;

	mTopLeftCorner = sf::Vector2f(cornerX, cornerY);
	mBoundingBox = sf::Vector2f(squareSize*mWidth, squareSize*mHeight);
}
