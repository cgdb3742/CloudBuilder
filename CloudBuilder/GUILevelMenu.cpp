#include <iostream>
#include "GUILevelMenu.h"
#include "InstructionBoard.h"



GUILevelMenu::GUILevelMenu(GameContext& gameContext, Level& level, InstructionBoard& board, InstructionPlayer& player) :
	GameEntity(gameContext),
	mSelected(0),
	mMenuCreator(GUIInstructionCreatorContainer(gameContext, level, board)),
	mMenuModifier(GUIInstructionModifierContainer(gameContext, board)),
	mMenuPlayer(GUIPlayerContainer(gameContext, player)),
	mMenuInfos(GUIInfosContainer(gameContext)),
	mMenuTests(GUITestsContainer(gameContext, level)),
	mMenuOptions(GUIOptionsContainer(gameContext)),
	mBoard(board)
{
	std::cout << "Creating GameEntity : GUILevelMenu." << std::endl;
	createTabs(board, player);
	std::cout << "GUIMenuTabs created." << std::endl;
}


GUILevelMenu::~GUILevelMenu()
{
}

void GUILevelMenu::createTabs(InstructionBoard& board, InstructionPlayer& player)
{
	//mMenuTabs.push_back(GUILevelMenuTab(mGameContext, "Infos", 0, *this));
	////mMenuCreator(GUIInstructionCreatorContainer(board));
	//mMenuTabs.push_back(GUILevelMenuTab(mGameContext, "New", 1, *this));
	////mMenuModifier(GUIInstructionModifierContainer(board));
	//mMenuTabs.push_back(GUILevelMenuTab(mGameContext, "Modify", 2, *this));
	//mMenuTabs.push_back(GUILevelMenuTab(mGameContext, "Play", 3, *this));

	mMenuTabs.push_back(GUILevelMenuTab(mGameContext, 0, *this));
	mMenuTabs.push_back(GUILevelMenuTab(mGameContext, 1, *this));
	mMenuTabs.push_back(GUILevelMenuTab(mGameContext, 2, *this));
	mMenuTabs.push_back(GUILevelMenuTab(mGameContext, 3, *this));
	mMenuTabs.push_back(GUILevelMenuTab(mGameContext, 4, *this));
	mMenuTabs.push_back(GUILevelMenuTab(mGameContext, 5, *this));
}

bool GUILevelMenu::changeSelection(unsigned int i)
{
	if (i<0 || i>mMenuTabs.size() || i == mSelected)
	{
		return false;
	}

	if (mLocked && (i == 1 || i == 2))
	{
		return false;
	}

	mSelected = i;

	setPositionChilds(mTopLeftCorner, mBoundingBox);

	std::cout << "Changed selection to menu " << mSelected << std::endl;

	return true;
}

GameEntity & GUILevelMenu::getMenu()
{
	return getMenu(mSelected);
}

GameEntity & GUILevelMenu::getMenu(unsigned int i)
{
	switch (i)
	{
	case 0: return mMenuInfos;
	case 1: return mMenuCreator;
	case 2: return mMenuModifier;
	case 3: return mMenuPlayer;
	case 4: return mMenuTests;
	case 5: return mMenuOptions;
	default: return mMenuCreator;
	}
}

GUIInstructionCreatorContainer & GUILevelMenu::getCreator()
{
	return mMenuCreator; //Feels like a hack...
}

void GUILevelMenu::updateCurrent(sf::Time dt)
{
	if (mBoard.hasUpdatedSelection()) //Note : can only happen in build mode
	{
		mMenuModifier.setUpModifiers();
		//changeSelection(1);
	}
}

//void GUILevelMenu::handleEventCurrent(const sf::Event & event)
//{
//	switch (event.type)
//	{
//	case sf::Event::MouseButtonReleased:
//		if (event.mouseButton.button == sf::Mouse::Button::Right)
//		{
//			changeSelection(1);
//		}
//		break;
//	}
//}

void GUILevelMenu::handleEventChilds(const sf::Event & event)
{
	for (unsigned int i = 0; i < mMenuTabs.size(); i++)
	{
		mMenuTabs[i].handleEventAll(event);
	}

	getMenu(mSelected).handleEventAll(event);
}

void GUILevelMenu::updateChilds(sf::Time dt)
{
	for (unsigned int i = 0; i < mMenuTabs.size(); i++)
	{
		mMenuTabs[i].updateAll(dt);
	}

	getMenu(mSelected).updateAll(dt);
}

void GUILevelMenu::drawChilds(sf::RenderTarget & target)
{
	for (unsigned int i = 0; i < mMenuTabs.size(); i++)
	{
		mMenuTabs[i].drawAll(target);
	}

	getMenu(mSelected).drawAll(target);
}

void GUILevelMenu::setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	float tabsMargin = maxBox.y / 8.0f;

	for (unsigned int i = 0; i < mMenuTabs.size(); i++)
	{
		mMenuTabs[i].setPositionAll(minCorner + sf::Vector2f(maxBox.x * i / mMenuTabs.size(), 0.0f), sf::Vector2f(maxBox.x / mMenuTabs.size(), tabsMargin));
	}

	for (unsigned int i = 0; i < mMenuTabs.size(); i++)
	{
		if (i == mSelected)
		{
			getMenu(i).setPositionAll(sf::Vector2f(minCorner.x, minCorner.y + tabsMargin), sf::Vector2f(maxBox.x, maxBox.y - tabsMargin));
		}
		else
		{
			getMenu(i).setPositionAll(sf::Vector2f(-1.0f, -1.0f) - maxBox * 2.0f, sf::Vector2f(0.0f, 0.0f));
		}
	}
}

void GUILevelMenu::updateChildsVector()
{
	mChilds.clear();

	for (GUILevelMenuTab& menuTab : mMenuTabs)
	{
		mChilds.push_back(menuTab);
	}

	for (unsigned int i = 0; i < mMenuTabs.size(); i++)
	{
		mChilds.push_back(getMenu(i));
	}

	//for (GameEntityPtr& menu : mMenus)
	//{
	//	mChilds.push_back(*menu);
	//}
}
