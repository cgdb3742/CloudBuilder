#pragma once
#include <vector>
#include "State.h"
#include "GUITitleScreenButton.h"

class StateTitleScreen :
	public State
{
public:
	StateTitleScreen(GameContext& gameContext);
	~StateTitleScreen();
protected:
	virtual void updateChildsVector();
private:
	std::vector<GUITitleScreenButton> mButtons;
};

