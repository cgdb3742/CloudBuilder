#include <iostream>
#include "StateLevel.h"
#include "Game.h"



StateLevel::StateLevel(GameContext& gameContext, StateMachine & machine):
	State(gameContext, machine, Enums::eState::Level),
	mLevel(gameContext, gameContext.levelData)
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
