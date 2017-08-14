#include <iostream>
#include "StateLevel.h"



StateLevel::StateLevel(GameContext& gameContext, StateMachine & machine):
	State(gameContext, machine),
	mLevel(gameContext, 2) //TODO Creation of mLevel
{
	std::cout << "Creating GameEntity : StateLevel." << std::endl;
}


StateLevel::~StateLevel()
{
}

void StateLevel::updateChildsVector()
{
	mChilds.clear();
	mChilds.push_back(mLevel);
	std::cout << "Updated childs in StateLevel." << std::endl;
}
