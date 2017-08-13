#pragma once
#include "State.h"
#include "Level.h"

class StateLevel :
	public State
{
public:
	StateLevel(StateMachine& machine);
	~StateLevel();
protected:
	virtual void updateChildsVector();
private:
	Level mLevel;
};

