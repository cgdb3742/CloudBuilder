#include <iostream>
#include "State.h"



State::State(GameContext& gameContext, StateMachine & machine):
	GameEntity(gameContext),
	mMachine(machine),
	mName(Enums::eState::Undefined)
{
	std::cout << "Creating GameEntity : State." << std::endl;
}

State::State(GameContext & gameContext, StateMachine & machine, Enums::eState name) :
	GameEntity(gameContext),
	mMachine(machine),
	mName(name)
{
}

State::~State()
{
}

void State::enter()
{
	updateChildsVectorAll();
	setActive();
}

void State::exit()
{
	if (mIsActive)
	{
		setInactive();
	}
}

void State::setActive()
{
	mIsActive = true;
}

void State::setInactive()
{
	mIsActive = false;
}

bool State::getIsActive()
{
	return mIsActive;
}
