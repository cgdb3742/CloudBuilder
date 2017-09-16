#include "LevelSelectDescription.h"
#include "Game.h"



LevelSelectDescription::LevelSelectDescription(GameContext & gameContext, sf::Vector2f positionRatio):
	GUIButton(gameContext, positionRatio),
	mText(L""),
	mWrappedText(L""),
	mFont(gameContext.resourceHandler.getFont(FontHandler::Arial))
{
}


LevelSelectDescription::~LevelSelectDescription()
{
}

void LevelSelectDescription::setLevelText(unsigned int worldId, unsigned int levelId)
{
	if (levelId == 0)
	{
		mText = L"";
		mWrappedText = L"";
	}
	else
	{
		mText = mGameContext.gameData.levelDescription[worldId - 1][levelId - 1];
		wrapDescription(mText);
	}
}

void LevelSelectDescription::wrapDescription(std::wstring & desc) //TODO Why wrapped text begin by /n ?
{
	size_t nextSpace = desc.find(L" ");

	std::wstring res = L"";
	std::wstring currentLine = desc.substr(0, nextSpace);
	size_t prevSpace = nextSpace;
	nextSpace = desc.find(L" ", nextSpace + 1);

	sf::Text text;
	text.setFont(mFont);
	text.setString(res);
	text.setCharacterSize(32);
	text.scale(mBoundingBox / 480.0f); //Note : only width is useful here

	while (prevSpace != std::wstring::npos)
	{
		std::wstring currentWord = desc.substr(prevSpace + 1, nextSpace - prevSpace - 1);
		text.setString(currentLine + L" " + currentWord);

		sf::FloatRect textRect = text.getGlobalBounds();

		if (textRect.width >= mBoundingBox.x * 0.95f)
		{
			//std::cout << textRect.width << std::endl;
			res += L"\n" + currentLine;
			currentLine = currentWord;
		}
		else
		{
			currentLine += L" " + currentWord;
		}

		prevSpace = nextSpace;
		nextSpace = desc.find(L" ", nextSpace + 1);
	}

	res += L"\n" + currentLine;
	mWrappedText = res;

	//std::cout << res << std::endl;
}

void LevelSelectDescription::drawCurrent(sf::RenderTarget & target)
{
	//sf::RectangleShape background(mBoundingBox);
	//background.setPosition(mTopLeftCorner);
	//background.setFillColor(sf::Color(191, 191, 191));
	//background.setOutlineThickness(1.0f);
	//background.setOutlineColor(sf::Color(0, 0, 0));

	//target.draw(background);

	sf::Text text;
	text.setFont(mFont);
	text.setString(mWrappedText);
	text.setCharacterSize(32);
	text.setFillColor(sf::Color(0, 0, 0));
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top);
	//float scale = mBoundingBox.x / 480.0f;
	float scale = std::min(mBoundingBox.x / 480.0f, mBoundingBox.y / textRect.height);
	text.scale(sf::Vector2f(scale, scale) * 0.95f);
	text.setPosition(mTopLeftCorner + sf::Vector2f(mBoundingBox.x / 2.0f, mBoundingBox.y / 8.0f));
	text.setString(mWrappedText);
	target.draw(text);
}

void LevelSelectDescription::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	GUIButton::setPositionCurrent(minCorner, maxBox);
	wrapDescription(mText);
}
