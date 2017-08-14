#pragma once

#include <map>
#include "State.h"
#include "Enums.h"

class ResourceHandler;

class StateMachine:
	public GameEntity
{
public:
	StateMachine(GameContext& gameContext);
	~StateMachine();

	bool startState(Enums::eState state);
	bool stopState(Enums::eState state);
	bool exists(Enums::eState state);
	bool isActive(Enums::eState state);

	virtual void handleEventChilds(const sf::Event& event);
	virtual void drawChilds(sf::RenderTarget& target);
protected:
	virtual void updateChildsVector();
private:
	bool assignNewState(Enums::eState state);
	State& getState(Enums::eState state);
	State::StatePtr createNewState(Enums::eState state);
	//State createNewState(Enums::eState state);

	std::map<Enums::eState,State::StatePtr> mStates;
	//std::map<Enums::eState, State> mStates;

};

