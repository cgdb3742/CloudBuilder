#pragma once
#include "GameEntity.h"
#include "GUITestsButton.h"
#include "GUITestsModel.h"

class GUITestsContainer :
	public GameEntity
{
public:
	GUITestsContainer(GameContext& gameContext, Level& level);
	~GUITestsContainer();

	virtual void drawCurrent(sf::RenderTarget& target);

	virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
protected:
	virtual void updateChildsVector();
private:
	GUITestsButton mButtonUp;
	GUITestsButton mButtonDown;
	GUITestsModel mModel;
};

