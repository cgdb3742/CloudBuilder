#pragma once

#include <map>
#include <list>
#include "State.h"
#include "Enums.h"

class ResourceHandler;

class StateMachine:
	public GameEntity
{
public:
	StateMachine(GameContext& gameContext);
	~StateMachine();

	virtual void updateCurrent(sf::Time dt);

	bool startState(Enums::eState state);
	bool stopState(Enums::eState state);
	bool activateState(Enums::eState state);
	bool deactivateState(Enums::eState state);
	bool fullFocusState(Enums::eState state);
	bool exists(Enums::eState state);
	bool isActive(Enums::eState state);
	bool preventGameDeactivation();

	bool requestStart(Enums::eState state);
	bool requestStop(Enums::eState state);
	bool requestActivate(Enums::eState state);
	bool requestDeactivate(Enums::eState state);
	bool requestFullFocus(Enums::eState state);

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
	std::list<Enums::eState> mRequestedStart;
	std::list<Enums::eState> mRequestedStop;
	std::list<Enums::eState> mRequestedActivate;
	std::list<Enums::eState> mRequestedDeactivate;
	std::list<Enums::eState> mRequestedFullFocus;
};

