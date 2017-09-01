// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>
#include "StateMachine.h"
#include "Game.h"
#include "PopUpStack.h"

#include "StateLevel.h"
#include "StateLevelSelect.h"
#include "StateTitleScreen.h"
#include "StatePopUp.h"


StateMachine::StateMachine(GameContext& gameContext):
	GameEntity(gameContext)
{
	std::cout << "Creating StateMachine." << std::endl;
}


StateMachine::~StateMachine()
{
}

void StateMachine::updateCurrent(sf::Time dt) //TODO Screens/States transitions ?
{
	//Don't start anything if a pop-up is active
	if (!exists(Enums::eState::PopUp) && mGameContext.popUpStack.isEmpty()) //Pop-ups freeze game
	{
		for (Enums::eState state : mRequestedStart)
		{
			startState(state);
		}
		mRequestedStart.clear();

		for (Enums::eState state : mRequestedActivate)
		{
			activateState(state);
		}
		mRequestedActivate.clear();

		for (Enums::eState state : mRequestedFullFocus)
		{
			fullFocusState(state);
		}
		mRequestedFullFocus.clear();
	}

	for (Enums::eState state : mRequestedDeactivate)
	{
		deactivateState(state);
	}
	mRequestedDeactivate.clear();

	for (Enums::eState state : mRequestedStop)
	{
		stopState(state);
	}
	mRequestedStop.clear();

	if (!exists(Enums::eState::PopUp) && !mGameContext.popUpStack.isEmpty())
	{
		startState(Enums::eState::PopUp);
		fullFocusState(Enums::eState::PopUp);
	}
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
		preventGameDeactivation();
		return true;
	}
}

bool StateMachine::activateState(Enums::eState state)
{
	if (!exists(state))
	{
		return false;
	}
	else
	{
		if (getState(state).getIsActive())
		{
			return false;
		}
		else
		{
			getState(state).setActive();
			getState(state).setPositionAll(mTopLeftCorner, mBoundingBox); //TODO Necessary ?
			return true;
		}
	}
}

bool StateMachine::deactivateState(Enums::eState state)
{
	if (!exists(state))
	{
		return false;
	}
	else
	{
		if (!getState(state).getIsActive())
		{
			return false;
		}
		else
		{
			getState(state).setInactive();
			preventGameDeactivation();
			return true;
		}
	}
}

bool StateMachine::fullFocusState(Enums::eState state)
{
	if (!exists(state))
	{
		return false;
	}
	else
	{
		if (!getState(state).getIsActive())
		{
			return false;
		}
		else
		{
			for (auto &otherState : mStates)
			{
				if (otherState.first != state)
				{
					deactivateState(otherState.first);
				}
			}

			return true;
		}
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

//If all states inactives, activate all states
//TODO prevent case where no state instancied
bool StateMachine::preventGameDeactivation()
{
	bool atLeastOneActive = false;

	for (auto &state : mStates)
	{
		atLeastOneActive = atLeastOneActive || state.second->getIsActive();
	}

	if (!atLeastOneActive)
	{
		for (auto &state : mStates)
		{
			state.second->setActive();
		}
	}

	return false;
}

bool StateMachine::requestStart(Enums::eState state)
{
	mRequestedStart.push_back(state);
	return true;
}

bool StateMachine::requestStop(Enums::eState state)
{
	mRequestedStop.push_back(state);
	return true;
}

bool StateMachine::requestActivate(Enums::eState state)
{
	mRequestedActivate.push_back(state);
	return true;
}

bool StateMachine::requestDeactivate(Enums::eState state)
{
	mRequestedDeactivate.push_back(state);
	return true;
}

bool StateMachine::requestFullFocus(Enums::eState state)
{
	mRequestedFullFocus.push_back(state);
	return true;
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

	//std::map<Enums::eState, State::StatePtr>::reverse_iterator rit;
	//for (rit = mStates.rbegin(); rit != mStates.rend(); ++rit){
	//	// iterator->first = key
	//	// iterator->second = value
	//	rit->second->drawAll(target);
	//}

	for (auto &state : mStates)
	{
		if (!state.second->getIsActive())
		{
			state.second->drawAll(target);
		}
	}

	for (auto &state : mStates)
	{
		if (state.second->getIsActive())
		{
			state.second->drawAll(target);
		}
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
	case Enums::eState::Undefined: return std::unique_ptr<State>(new State(mGameContext, *this));
	case Enums::eState::Level: return std::unique_ptr<State>(new StateLevel(mGameContext, *this)); //make_unique return pointer to object of parent type but new return pointer to object of derived type !
	case Enums::eState::LevelSelect: return std::unique_ptr<State>(new StateLevelSelect(mGameContext, *this));
	case Enums::eState::TitleScreen: return std::unique_ptr<State>(new StateTitleScreen(mGameContext, *this));
	case Enums::eState::PopUp: return std::unique_ptr<State>(new StatePopUp(mGameContext, *this));
	default: return std::unique_ptr<State>(new State(mGameContext, *this));
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
