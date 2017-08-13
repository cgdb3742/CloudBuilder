// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>
#include "StateMachine.h"
#include "StateLevel.h"
#include "StateTitleScreen.h"


StateMachine::StateMachine()
{
	std::cout << "Creating StateMachine." << std::endl;
}


StateMachine::~StateMachine()
{
}

bool StateMachine::startState(Enums::eState state)
{
	if (exists(state))
	{
		return false;
	}
	else
	{
		assignNewState(state);
		std::cout << "Assigned new State in StateMachine." << std::endl;
		//mStates.insert(std::pair<Enums::eState, State::StateRef>(state, createNewState(state)));
		//mStates[state] = createNewState(state);
		//mStates[state].get().enter();
		updateChildsVectorAll(); //TODO Overkill
		getState(state).enter();
		getState(state).setPositionAll(mTopLeftCorner, mBoundingBox);
		return true;
	}
}

bool StateMachine::stopState(Enums::eState state)
{
	if (!exists(state))
	{
		return false;
	}
	else
	{
		//mStates[state].get().exit();
		getState(state).exit();
		mStates.erase(state);
		updateChildsVectorAll(); //TODO Overkill
		return true;
	}
}

bool StateMachine::exists(Enums::eState state)
{
	return (mStates.find(state) != mStates.end());
}

bool StateMachine::isActive(Enums::eState state)
{
	if (exists(state))
	{
		//return mStates[state].get().getIsActive();
		return getState(state).getIsActive();
	}
	else
	{
		return false;
	}
}

void StateMachine::handleEventChilds(const sf::Event & event)
{
	for (auto &state : mStates)
	{
		if (state.second->getIsActive())
		//if (state.second.getIsActive())
		{
			state.second->handleEventAll(event);
			//state.second.handleEventAll(event);
		}
	}
}

void StateMachine::drawChilds(sf::RenderTarget & target)
{
	//std::cout << "StateMachine is drawing." << std::endl;

	std::map<Enums::eState, State::StatePtr>::reverse_iterator rit;
	//std::map<Enums::eState, State>::reverse_iterator rit;
	for (rit = mStates.rbegin(); rit != mStates.rend(); ++rit){
		// iterator->first = key
		// iterator->second = value
		rit->second->drawAll(target);
		//rit->second.drawAll(target);
	}

	drawCurrent(target);
}

void StateMachine::updateChildsVector()
{
	mChilds.clear();

	for (auto &state : mStates)
	{
		mChilds.push_back(*(state.second));
		//mChilds.push_back(state.second);
	}

	std::cout << "Updated childs in StateMachine." << std::endl;

	//for (auto it = mStates.begin(); it != mStates.end(); ++it) {
	//	// iterator->first = key
	//	// iterator->second = value
	//	mChilds.push_back(it->second);
	//}
}

bool StateMachine::assignNewState(Enums::eState state)
{
	if (!exists(state))
	{
		//mStates.insert(std::pair<Enums::eState, State::StatePtr>(state, std::move(createNewState(state))));
		//mStates.insert(std::pair<Enums::eState, State::StatePtr>(state, std::make_unique<State>(createNewState(state))));
		mStates.insert(std::pair<Enums::eState, State::StatePtr>(state, createNewState(state)));
		//mStates.insert(std::pair<Enums::eState, State>(state, createNewState(state)));

		return true;
	}
	else
	{
		return false;
	}
}

State& StateMachine::getState(Enums::eState state)
{
	auto it = mStates.find(state);

	assert(it != mStates.end());

	return *(it->second);
	//return (it->second);
}

State::StatePtr StateMachine::createNewState(Enums::eState state)
//State StateMachine::createNewState(Enums::eState state)
{
	//switch (state)
	//{
	//case Enums::eState::Undefined: return State();
	//case Enums::eState::Level: return StateLevel();
	//default: return State();
	//}

	switch (state)
	{
	case Enums::eState::Undefined: return std::unique_ptr<State>(new State(*this));
	case Enums::eState::Level: return std::unique_ptr<State>(new StateLevel(*this)); //make_unique return pointer to object of parent type but new return pointer to object of derived type !
	case Enums::eState::TitleScreen: return std::unique_ptr<State>(new StateTitleScreen(*this));
	default: return std::unique_ptr<State>(new State(*this));
	}

	//switch (state)
	//{
	//case Enums::eState::Undefined: return std::make_unique<State>(State());
	//case Enums::eState::Level: return std::move(std::make_unique<StateLevel>(StateLevel())); //std::move not working if not copiable
	////case Enums::eState::Level: return State::StatePtr(std::make_unique<StateLevel>(StateLevel()));
	////case Enums::eState::Level: return State::StatePtr(static_cast<State*>((std::make_unique<StateLevel>(StateLevel())).release()));
	//default: return std::make_unique<State>(State());
	//}
}
