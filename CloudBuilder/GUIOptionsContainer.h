#pragma once
#include "GameEntity.h"
#include "GUIButtonChangeState.h"
class GUIOptionsContainer :
	public GameEntity
{
public:
	GUIOptionsContainer(GameContext& gameContext);
	~GUIOptionsContainer();

	virtual void drawCurrent(sf::RenderTarget& target);

	virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
protected:
	virtual void updateChildsVector();
private:
	GUIButtonChangeState mToLevelSelect;
};

