#pragma once

#include <memory>
#include "GameEntity.h"
#include "Enums.h"

class StateMachine;

class State :
	public GameEntity
{
public:
	typedef std::unique_ptr<State> StatePtr;
	//typedef std::reference_wrapper<State> StateRef;

	//State(GameContext& gameContext, StateMachine& machine);
	//State(GameContext& gameContext, StateMachine& machine, Enums::eState name);
	State(GameContext& gameContext);
	State(GameContext& gameContext, Enums::eState name);
	~State();

	virtual void enter();
	virtual void exit();
	virtual void setActive();
	virtual void setInactive();
	virtual bool getIsActive();
protected:
	bool mIsActive;
	//StateMachine& mMachine;
	Enums::eState mName;
};

