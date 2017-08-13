#include <iostream>
#include "State.h"



State::State(StateMachine & machine):
	mMachine(machine)
{
	std::cout << "Creating GameEntity : State." << std::endl;
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
