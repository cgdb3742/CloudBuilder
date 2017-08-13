#pragma once
#include <vector>
#include "State.h"
#include "GUITitleScreenButton.h"

class StateTitleScreen :
	public State
{
public:
	StateTitleScreen(StateMachine & machine);
	~StateTitleScreen();
protected:
	virtual void updateChildsVector();
private:
	std::vector<GUITitleScreenButton> mButtons;
};

