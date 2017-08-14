#pragma once
#include <list>
#include "GameEntity.h"
#include "GUIPlayerButton.h"

class InstructionPlayer;

class GUIPlayerContainer :
	public GameEntity
{
public:
	GUIPlayerContainer(GameContext& gameContext, InstructionPlayer& player);
	~GUIPlayerContainer();

	virtual void drawCurrent(sf::RenderTarget& target);

	virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
protected:
	virtual void updateChildsVector();
private:
	std::list<GUIPlayerButton> mButtons;
};

