#pragma once
#include <vector>
#include <memory>
#include "GameEntity.h"
#include "BuildLockable.h"
#include "GUILevelMenuTab.h"
#include "GUIInstructionCreatorContainer.h"
#include "GUIInstructionModifierContainer.h"
#include "GUIPlayerContainer.h"
#include "GUIInfosContainer.h"
#include "GUITestsContainer.h"
#include "GUIOptionsContainer.h"

class Level;
class InstructionBoard;
class InstructionPlayer;

class GUILevelMenu :
	public GameEntity,
	public BuildLockable
{
public:
	GUILevelMenu(GameContext& gameContext, Level& level, InstructionBoard& board, InstructionPlayer& player);
	~GUILevelMenu();

	void createTabs(InstructionBoard& board, InstructionPlayer& player);

	bool changeSelection(unsigned int i);

	GameEntity& getMenu();
	GameEntity& getMenu(unsigned int i);
	GUIInstructionCreatorContainer& getCreator();

	virtual void updateCurrent(sf::Time dt);

	//virtual void handleEventCurrent(const sf::Event & event);
	virtual void handleEventChilds(const sf::Event& event);
	virtual void updateChilds(sf::Time dt);
	virtual void drawChilds(sf::RenderTarget& target);

	virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
protected:
	virtual void updateChildsVector();

private:
	std::vector<GUILevelMenuTab> mMenuTabs;
	GUIInstructionCreatorContainer mMenuCreator;
	GUIInstructionModifierContainer mMenuModifier;
	GUIPlayerContainer mMenuPlayer;
	GUIInfosContainer mMenuInfos;
	GUITestsContainer mMenuTests;
	GUIOptionsContainer mMenuOptions;

	InstructionBoard& mBoard;

	unsigned int mSelected;
};

