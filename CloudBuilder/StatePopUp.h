#pragma once
#include "State.h"
#include "PopUpStack.h"
#include "PopUpMessage.h"
class StatePopUp :
	public State
{
public:
	StatePopUp(GameContext& gameContext, StateMachine & machine);
	~StatePopUp();

	//virtual void setActive();

	//virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
	virtual sf::Vector2f computeChildsBoundingBox();

	virtual void drawCurrent(sf::RenderTarget& target);

	virtual void updateChildsVector();
private:
	PopUpData mMessageData;
	PopUpMessage mMessage;
};

