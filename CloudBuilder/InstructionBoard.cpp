// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>
#include "InstructionBoard.h"
#include "Game.h"

// /!\ i varies along x and j varies along y

static std::vector<InstructionSquare::InstructionSquarePtr> generate(size_t sz)
{
	std::vector<InstructionSquare::InstructionSquarePtr> result;
	result.reserve(sz);
	for (size_t i = 0; i < sz; ++i)
		result.emplace_back(nullptr);

	return result;
}

InstructionBoard::InstructionBoard(GameContext& gameContext) :
	GameEntity(gameContext),
	mWidth(1),
	mHeight(1),
	mBoard(generate(1 * 1)),
	mFlow(gameContext, *this),
	mSelected(0, 0),
	mStartPointsUpdated(false),
	mSelectionUpdated(false)
{
	std::cout << "Creating GameEntity : InstructionBoard ( " << mWidth << " * " << mHeight << " )." << std::endl;

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			mBoard[i + j*mWidth] = std::make_unique<InstructionSquare>(InstructionSquare(gameContext));
		}
	}

	//setSelection(0, 0);

	updateBordFlow();
}

InstructionBoard::InstructionBoard(GameContext & gameContext, std::wstring source) :
	GameEntity(gameContext),
	mWidth(1),
	mHeight(1),
	mBoard(generate(1 * 1)),
	mFlow(gameContext, *this),
	mSelected(0, 0),
	mStartPointsUpdated(false),
	mSelectionUpdated(false)
{
	std::cout << "Creating GameEntity : InstructionBoard" << std::endl;
	convertFromString(source);
	updateBordFlow();
	std::cout << "Loaded GameEntity : InstructionBoard ( " << mWidth << " * " << mHeight << " )." << std::endl;

}

InstructionBoard::InstructionBoard(GameContext& gameContext, unsigned int width, unsigned int height) :
	GameEntity(gameContext),
	mWidth(width),
	mHeight(height),
	mBoard(generate(width*height)),
	mFlow(gameContext, *this),
	mSelected(0, 0),
	mStartPointsUpdated(false),
	mSelectionUpdated(false)
{
	std::cout << "Creating GameEntity : InstructionBoard ( " << mWidth << " * " << mHeight << " )." << std::endl;

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			mBoard[i + j*mWidth] = std::make_unique<InstructionSquare>(InstructionSquare(gameContext));
		}
	}

	updateBordFlow();

	//mBoard[5 + 2*mHeight]->setNextDir(Enums::eDir::Down);

	//insert(2, 5, InstructionSquare::createNewInstructionSquare(gameContext, Enums::eInstruction::ActMove));
	//insert(6, 4, InstructionSquare::createNewInstructionSquare(gameContext, Enums::eInstruction::ActMove));
	//insert(3, 7, InstructionSquare::createNewInstructionSquare(gameContext, Enums::eInstruction::CheckCloud));
	//insert(1, 1, InstructionSquare::createNewInstructionSquare(gameContext, Enums::eInstruction::SpeStart, Enums::eColor::Red));
	//insert(7, 1, InstructionSquare::createNewInstructionSquare(gameContext, Enums::eInstruction::SpeStart, Enums::eColor::Blue));
	//insert(6, 1, InstructionSquare::createNewInstructionSquare(Enums::eInstruction::SpeStart, Enums::eColor::Green));
	//insert(5, 1, InstructionSquare::createNewInstructionSquare(Enums::eInstruction::SpeStart, Enums::eColor::Yellow));
	//mSelectionUpdated = false;
	//setSelection(0, 0);
	//insert(2, 1, InstructionSquare::createNewInstructionSquare(gameContext, Enums::eInstruction::ActMove));
	//insert(1, 1, InstructionSquare::createNewInstructionSquare(gameContext, Enums::eInstruction::SpeStart, Enums::eColor::Red));
	//std::cout << convertToString() << std::endl;
}

InstructionBoard::~InstructionBoard()
{
}

//InstructionBoard::InstructionBoard(const InstructionBoard & toCopy):
//	mWidth(toCopy.mWidth),
//	mHeight(toCopy.mHeight),
//	mBoard(generate(toCopy.mWidth*toCopy.mHeight))
//{
//	for (unsigned int i = 0; i < mWidth; i++)
//	{
//		for (unsigned int j = 0; j < mHeight; j++)
//		{
//			mBoard[i + j*mHeight] = std::move(InstructionSquare::createNewInstructionSquare(*toCopy.mBoard[i + j*mHeight].type)),
//			*mBoard[i + j*mHeight] = *(toCopy.mBoard[i + j*mHeight])
//		}
//	}
//}

//TODO : use this when getting board from string to ensure there's no error
//Take special care for one and only one Start square per color
bool InstructionBoard::isValid()
{
	bool redNeeded = (mGameContext.levelData.nbRobots >= 1);
	bool blueNeeded = (mGameContext.levelData.nbRobots >= 2);
	bool greenNeeded = (mGameContext.levelData.nbRobots >= 3);
	bool yellowNeeded = (mGameContext.levelData.nbRobots >= 4);

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			if (!get(i, j).isValid())
			{
				return false;
			}

			if (get(i, j).getType() == Enums::eInstruction::SpeStart)
			{
				switch (get(i, j).getStartColor())
				{
				case Enums::eColor::Red:
				{
					if (redNeeded)
					{
						redNeeded = false;
					}
					else //Second start of the same color or start of an unused color
					{
						return false;
					}
				}; break;
				case Enums::eColor::Blue:
				{
					if (blueNeeded)
					{
						blueNeeded = false;
					}
					else //Second start of the same color or start of an unused color
					{
						return false;
					}
				}; break;
				case Enums::eColor::Green:
				{
					if (greenNeeded)
					{
						greenNeeded = false;
					}
					else //Second start of the same color or start of an unused color
					{
						return false;
					}
				}; break;
				case Enums::eColor::Yellow:
				{
					if (yellowNeeded)
					{
						yellowNeeded = false;
					}
					else //Second start of the same color or start of an unused color
					{
						return false;
					}
				}; break;
				}
			}
		}
	}

	return !(redNeeded || blueNeeded || greenNeeded || yellowNeeded);
}

void InstructionBoard::loadLevelBoard(unsigned int world, unsigned int level)
{
	if (mGameContext.saveData.savedBoard[world - 1][level - 1] == L"NONE")
	{
		convertFromString(mGameContext.levelData.startingBoard);
	}
	else
	{
		convertFromString(mGameContext.saveData.savedBoard[world - 1][level - 1]);
	}

	//mFlow.computeLinks();
}

std::wstring InstructionBoard::convertToString() //Sparse definition, TODO do full definition too ?
{
	std::wstring values = L"";

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			if (get(i, j).getType() != Enums::eInstruction::Unassigned)
			{
				values += L"i" + std::to_wstring(i) + L"j" + std::to_wstring(j) + L"v" + get(i, j).convertToString();
			}
		}
	}

	return L"w" + std::to_wstring(mWidth) + L"h" + std::to_wstring(mHeight) + values;
}

bool InstructionBoard::convertFromString(std::wstring & source)
{
	try
	{
		size_t wFound = source.find(L"w");
		size_t hFound = source.find(L"h");
		size_t iFound = source.find(L"i");
		size_t jFound = source.find(L"j");
		size_t vFound = source.find(L"v");

		if (wFound == std::wstring::npos || hFound == std::wstring::npos || iFound == std::wstring::npos || jFound == std::wstring::npos || vFound == std::wstring::npos)
		{
			return false;
		}

		mWidth = stoul(source.substr(wFound + 1, hFound - wFound - 1));
		mHeight = stoul(source.substr(hFound + 1, iFound - hFound - 1));
		mBoard.clear();
		mBoard = generate(mWidth * mHeight);

		for (unsigned int i = 0; i < mWidth; i++)
		{
			for (unsigned int j = 0; j < mHeight; j++)
			{
				mBoard[i + j*mWidth] = std::make_unique<InstructionSquare>(InstructionSquare(mGameContext));
			}
		}

		while (iFound != std::wstring::npos)
		{
			unsigned int i = stoul(source.substr(iFound + 1, iFound - jFound - 1));
			unsigned int j = stoul(source.substr(jFound + 1, jFound - vFound - 1));
			iFound = source.find(L"i", iFound + 1);
			InstructionSquare::InstructionSquarePtr newSquare;

			if (iFound != std::wstring::npos)
			{
				newSquare = InstructionSquare::createNewInstructionSquare(mGameContext, source.substr(vFound + 1, vFound - iFound - 1));
			}
			else
			{
				newSquare = InstructionSquare::createNewInstructionSquare(mGameContext, source.substr(vFound + 1));
			}

			if (newSquare == nullptr)
			{
				return false;
			}

			insert(i, j, std::move(newSquare));

			jFound = source.find(L"j", jFound + 1);
			vFound = source.find(L"v", vFound + 1);
		}

		//TODO use isValid() to check whether the loaded board is correct for the current level

		updateBordFlow();

		return true;
	}
	catch (...)
	{
		//TODO Handle exception
	}

	return false;
}

bool InstructionBoard::exists(unsigned int i, unsigned int j)
{
	return (i >= 0 && i < mWidth && j >= 0 && j < mHeight);
}

InstructionSquare& InstructionBoard::get(unsigned int i, unsigned int j)
{
	assert(exists(i, j));

	return *(mBoard[i + j*mWidth].get());
}

bool InstructionBoard::canMove(unsigned int i, unsigned int j, Enums::eDir dir)
{
	if (!exists(i, j)) return false;

	switch (dir)
	{
	case Enums::eDir::Center: return true;
	case Enums::eDir::Right: return (i < mWidth - 1);
	case Enums::eDir::Up: return (j > 0);
	case Enums::eDir::Left: return (i > 0);
	case Enums::eDir::Down: return (j < mHeight - 1);
	default: return false;
	}
}

unsigned int InstructionBoard::getWidth()
{
	return mWidth;
}

unsigned int InstructionBoard::getHeight()
{
	return mHeight;
}

sf::Vector2f InstructionBoard::getSquareSize()
{
	return sf::Vector2f(mBoundingBox.x / mWidth, mBoundingBox.y / mHeight);
}

InstructionSquare::InstructionSquarePtr InstructionBoard::giveToDrag(sf::Vector2f mousePos)
{
	float i = (mousePos.x - mTopLeftCorner.x) * mWidth / mBoundingBox.x;
	float j = (mousePos.y - mTopLeftCorner.y) * mHeight / mBoundingBox.y;

	if (i >= 0.0f && i < mWidth && j >= 0.0f && j < mHeight)
	{
		return giveToDrag(static_cast<unsigned int>(i), static_cast<unsigned int>(j));
	}
	else
	{
		return nullptr;
	}
}

bool InstructionBoard::canGetFromDrag(sf::Vector2f mousePos)
{
	float i = (mousePos.x - mTopLeftCorner.x) * mWidth / mBoundingBox.x;
	float j = (mousePos.y - mTopLeftCorner.y) * mHeight / mBoundingBox.y;

	if (i >= 0.0f && i < mWidth && j >= 0.0f && j < mHeight)
	{
		return mBoard[static_cast<unsigned int>(i) + static_cast<unsigned int>(j)*mWidth]->IsErasable();
	}
	else
	{
		return false;
	}
}

InstructionSquare::InstructionSquarePtr InstructionBoard::getFromDrag(sf::Vector2f mousePos, InstructionSquare::InstructionSquarePtr ptr)
{
	float i = (mousePos.x - mTopLeftCorner.x) * mWidth / mBoundingBox.x;
	float j = (mousePos.y - mTopLeftCorner.y) * mHeight / mBoundingBox.y;

	if (i >= 0.0f && i < mWidth && j >= 0.0f && j < mHeight)
	{
		return getFromDrag(static_cast<unsigned int>(i), static_cast<unsigned int>(j), std::move(ptr));
	}
	else
	{
		return ptr;
	}
}

void InstructionBoard::updateBordFlow()
{
	mFlow.computeLinks();
}

void InstructionBoard::drawCurrent(sf::RenderTarget & target)
{
	//std::cout << "Drawing InstructionBoard." << std::endl;

	if (!mLocked && exists(mSelected.first, mSelected.second))
	{
		sf::RectangleShape selection(getSquareSize());
		selection.setPosition(sf::Vector2f(mTopLeftCorner.x + mBoundingBox.x * mSelected.first / mWidth, mTopLeftCorner.y + mBoundingBox.y * mSelected.second / mHeight));
		selection.setFillColor(sf::Color(0, 0, 0, 0));
		selection.setOutlineThickness(1.0f);
		selection.setOutlineColor(sf::Color(255, 63, 63));
		target.draw(selection);
	}

	//for (unsigned int i = 0; i <= mWidth; i++)
	//{
	//	sf::RectangleShape line(sf::Vector2f(1.0f, mBoundingBox.y));
	//	line.setPosition(sf::Vector2f(mTopLeftCorner.x + mBoundingBox.x * i / mWidth, mTopLeftCorner.y));
	//	line.setFillColor(sf::Color(127, 127, 127));
	//	target.draw(line);
	//}

	//for (unsigned int j = 0; j <= mHeight; j++)
	//{
	//	sf::RectangleShape line(sf::Vector2f(mBoundingBox.x, 1.0f));
	//	line.setPosition(sf::Vector2f(mTopLeftCorner.x, mTopLeftCorner.y + mBoundingBox.y * j / mHeight));
	//	line.setFillColor(sf::Color(127, 127, 127));
	//	target.draw(line);
	//}
}

void InstructionBoard::setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	float squareSize = mBoundingBox.x / mWidth;

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			mBoard[i + j*mWidth]->setPositionAll(sf::Vector2f(mTopLeftCorner.x + i * squareSize, mTopLeftCorner.y + j *squareSize), sf::Vector2f(squareSize, squareSize));
		}
	}

	mFlow.setPositionAll(mTopLeftCorner, mBoundingBox);
}

void InstructionBoard::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	float squareSize = std::min(maxBox.x / mWidth, maxBox.y / mHeight);
	float spaceX = maxBox.x - (squareSize * mWidth);
	float spaceY = maxBox.y - (squareSize * mHeight);
	float cornerX = minCorner.x + spaceX / 2.0f;
	float cornerY = minCorner.y + spaceY / 2.0f;

	mTopLeftCorner = sf::Vector2f(cornerX, cornerY);
	mBoundingBox = sf::Vector2f(squareSize*mWidth, squareSize*mHeight);
}

void InstructionBoard::handleEventCurrent(const sf::Event & event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Button::Right)
		{
			float i = (event.mouseButton.x - mTopLeftCorner.x) * mWidth / mBoundingBox.x;
			float j = (event.mouseButton.y - mTopLeftCorner.y) * mHeight / mBoundingBox.y;

			if (i >= 0.0f && i < mWidth && j >= 0.0f && j < mHeight)
			{
				setSelection(static_cast<unsigned int>(i), static_cast<unsigned int>(j));
				//TODO Switch GUILevelMenu to GUIInstructionModifierContainer ?
			}
		}
		break;
	//No touch event needed
	}
}

bool InstructionBoard::hasUpdatedStartPoints()
{
	if (mStartPointsUpdated)
	{
		mStartPointsUpdated = false;
		return true;
	}

	return false;
}

void InstructionBoard::setStartPosition(Enums::eColor color, unsigned int i, unsigned int j)
{
	auto res = mStartPoints.find(color);

	if (res == mStartPoints.end())
	{
		mStartPoints.insert(std::pair<Enums::eColor, std::pair<unsigned int, unsigned int>>(color, std::pair<unsigned int, unsigned int>(i, j)));
	}
	else
	{
		mStartPoints[color] = std::pair<unsigned int, unsigned int>(i, j);
	}
}

std::pair<unsigned int, unsigned int> InstructionBoard::getStartPosition(Enums::eColor color)
{
	auto res = mStartPoints.find(color);

	if (res == mStartPoints.end())
	{
		return std::pair<unsigned int, unsigned int>(-1, -1);
	}
	else
	{
		return res->second;
	}
}

bool InstructionBoard::hasUpdatedSelection()
{
	if (mSelectionUpdated)
	{
		mSelectionUpdated = false;
		return true;
	}

	return false;
}

void InstructionBoard::setSelection(unsigned int i, unsigned int j)
{
	if (exists(i, j))
	{
		if (get(i, j).getType() != Enums::eInstruction::Unassigned)
		{
			mSelected = std::pair<unsigned int, unsigned int>(i, j);
			mSelectionUpdated = true;
		}
	}
}

InstructionSquare & InstructionBoard::getSelection()
{
	assert(exists(mSelected.first, mSelected.second));

	return get(mSelected.first, mSelected.second);
}

unsigned int InstructionBoard::getSelectionI()
{
	return mSelected.first;
}

unsigned int InstructionBoard::getSelectionJ()
{
	return mSelected.second;
}

void InstructionBoard::updateChildsVector()
{
	mChilds.clear();

	for (unsigned int i = 0; i < mWidth; i++)
	{
		for (unsigned int j = 0; j < mHeight; j++)
		{
			mChilds.push_back(*(mBoard[i + j*mWidth].get()));
		}
	}

	mChilds.push_back(mFlow);
}

InstructionSquare::InstructionSquarePtr InstructionBoard::giveToDrag(unsigned int i, unsigned int j)
{
	if (mBoard[i + j*mWidth]->IsDraggable())
	{
		InstructionSquare::InstructionSquarePtr toReturn = std::move(mBoard[i + j*mWidth]);
		//mBoard[i + j*mHeight] = std::make_unique<InstructionSquare>(InstructionSquare());
		insert(i, j, std::make_unique<InstructionSquare>(InstructionSquare(mGameContext)));

		updateBordFlow();

		return toReturn;
	}
	else
	{
		return nullptr;
	}
}

InstructionSquare::InstructionSquarePtr InstructionBoard::getFromDrag(unsigned int i, unsigned int j, InstructionSquare::InstructionSquarePtr ptr)
{
	if (mBoard[i + j*mWidth]->IsErasable())
	{
		//mBoard[i + j*mHeight] = std::move(ptr);
		//return nullptr;
		return insert(i, j, std::move(ptr));
	}
	else
	{
		return ptr;
	}
}

InstructionSquare::InstructionSquarePtr InstructionBoard::insert(unsigned int i, unsigned int j, InstructionSquare::InstructionSquarePtr ptr)
{
	mBoard[i + j*mWidth] = std::move(ptr);

	//if (mBoard[i + j*mHeight]->getType() != Enums::eInstruction::Unassigned)
	//{
	//	setSelection(i, j);
	//}
	setSelection(i, j);

	if (mBoard[i + j*mWidth]->getType() == Enums::eInstruction::SpeStart)
	{
		setStartPosition(mBoard[i + j*mWidth]->getStartColor(), i, j);
		mStartPointsUpdated = true;
	}

	mBoard[i + j*mWidth]->setUpNextDir(i == 0, i == mWidth - 1, j == 0, j == mHeight - 1);

	updateChildsVectorAll(); //TODO Overkill

	mBoard[i + j*mWidth]->setPositionAll(sf::Vector2f(mTopLeftCorner.x + i * getSquareSize().x, mTopLeftCorner.y + j * getSquareSize().y), getSquareSize());

	updateBordFlow();

	return nullptr;
}
