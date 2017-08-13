#include <iostream>
#include "CloudPicture.h"
#include "CloudCanvas.h"

CloudPicture::CloudPicture():
	mWidth(1),
	mHeight(1),
	mPicture(mWidth, std::vector<bool>(mHeight, false))
{
	std::cout << "Creating GameEntity : CloudPicture." << std::endl;
}

CloudPicture::CloudPicture(unsigned int width, unsigned int height):
	mWidth(width),
	mHeight(height),
	mPicture(width, std::vector<bool>(height, false))
{
	std::cout << "Creating GameEntity : CloudPicture." << std::endl;
}

CloudPicture::CloudPicture(unsigned int width, unsigned int height, std::string values) :
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
				mPicture[i][j] = (values[i + j*mHeight] ==  '1');
			}
		}
	}
}

CloudPicture::CloudPicture(CloudCanvas & canvas):
	mWidth(canvas.getWidth()),
	mHeight(canvas.getHeight()),
	mPicture(mWidth, std::vector<bool>(mHeight, false))
{
	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			mPicture[i][j] = canvas.get(i, j).getIsCloud();
		}
	}
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

std::string CloudPicture::getPicture()
{
	std::string res(mWidth*mHeight, '0');

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			if (mPicture[i][j])
			{
				res[i + j*mHeight] = '1';
			}
		}
	}

	return res;
}

bool CloudPicture::getPictureFromString(unsigned int width, unsigned int height, std::string values)
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

bool CloudPicture::getPictureFromString(std::string values)
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
				if (i + j*mHeight < l)
				{
					mPicture[i][j] = (values[i + j*mHeight] == '1');
				}
			}
		}

		return true;
	}
}

std::string CloudPicture::convertToString()
{
	return "w" + std::to_string(mWidth) + "h" + std::to_string(mHeight) + "p" + getPicture();
}

bool CloudPicture::convertFromString(std::string & source)
{
	unsigned int wFound = source.find("w");
	unsigned int hFound = source.find("h");
	unsigned int pFound = source.find("p");

	if (wFound == std::string::npos || hFound == std::string::npos || pFound == std::string::npos)
	{
		return false;
	}

	try
	{
		unsigned int width = stoul(source.substr(wFound + 1, hFound - wFound - 1));
		unsigned int height = stoul(source.substr(hFound + 1, pFound - hFound - 1));
		std::string values = source.substr(pFound + 1, width * height);

		return getPictureFromString(width, height, values);
	}
	catch (...)
	{
		//TODO Handle exception
	}
	
	return false;
}

unsigned int CloudPicture::getWidth()
{
	return mWidth;
}

unsigned int CloudPicture::getHeight()
{
	return mHeight;
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