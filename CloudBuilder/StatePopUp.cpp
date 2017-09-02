#include "StatePopUp.h"
#include "StateMachine.h"
#include "Game.h"



StatePopUp::StatePopUp(GameContext& gameContext):
	State(gameContext, Enums::eState::PopUp),
	mMessageData(gameContext.popUpStack.popMessage()),
	mMessage(gameContext, sf::Vector2f(0.5f,0.5f), mMessageData)
{
}


StatePopUp::~StatePopUp()
{
}

sf::Vector2f StatePopUp::computeChildsBoundingBox()
{
	return sf::Vector2f(mBoundingBox.x / 2.0f, mBoundingBox.y / 3.0f);
}

void StatePopUp::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape screenCover(mBoundingBox);
	screenCover.setPosition(mTopLeftCorner);
	screenCover.setFillColor(sf::Color(0, 0, 0, 127));
	target.draw(screenCover);
}

void StatePopUp::updateChildsVector()
{
	mChilds.clear();

	mChilds.push_back(mMessage);
}

//void StatePopUp::setActive()
//{
//	State::setActive();
//
//	mMachine.requestFullFocus(mName);
//}
