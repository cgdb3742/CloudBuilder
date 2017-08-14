#pragma once

#include <memory>
#include "GameEntity.h"

class StateMachine;

class State :
	public GameEntity
{
public:
	typedef std::unique_ptr<State> StatePtr;
	//typedef std::reference_wrapper<State> StateRef;

	State(GameContext& gameContext, StateMachine& machine);
	~State();

	virtual void enter();
	virtual void exit();
	virtual void setActive();
	virtual void setInactive();
	virtual bool getIsActive();
protected:
	bool mIsActive;
	StateMachine& mMachine;
};

