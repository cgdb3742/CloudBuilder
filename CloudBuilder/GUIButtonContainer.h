#pragma once
#include "GameEntity.h"
class GUIButtonContainer :
	public GameEntity
{
public:
	GUIButtonContainer();
	~GUIButtonContainer();

	virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
};

