#include "StateTitleScreen.h"



StateTitleScreen::StateTitleScreen(GameContext& gameContext, StateMachine & machine):
	State(gameContext, machine, Enums::eState::TitleScreen)
{
}


StateTitleScreen::~StateTitleScreen()
{
}

void StateTitleScreen::updateChildsVector()
{
}
