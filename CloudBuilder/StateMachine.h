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

	void processStartRequests();
	void processStopRequests();
	void processActivateRequests();
	void processDeactivateRequests();
	void processFullFocusRequests();

	bool startState(Enums::eState state);
	bool stopState(Enums::eState state);
	bool activateState(Enums::eState state);
	bool deactivateState(Enums::eState state);
	bool fullFocusState(Enums::eState state);
	bool exists(Enums::eState state);
	bool isActive(Enums::eState state);
	bool preventGameDeactivation();

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

