#include "StateRequestStack.h"



StateRequestStack::StateRequestStack()
{
}


StateRequestStack::~StateRequestStack()
{
}

bool StateRequestStack::addStartRequest(Enums::eState state)
{
	if (state == Enums::eState::Undefined)
	{
		return false;
	}

	auto res = mRequestedStart.insert(state);
	return (res.second);
}

bool StateRequestStack::addStopRequest(Enums::eState state)
{
	if (state == Enums::eState::Undefined)
	{
		return false;
	}

	auto res = mRequestedStop.insert(state);
	return (res.second);
}

bool StateRequestStack::addActivateRequest(Enums::eState state)
{
	if (state == Enums::eState::Undefined)
	{
		return false;
	}

	auto res = mRequestedActivate.insert(state);
	return (res.second);
}

bool StateRequestStack::addDeactivateRequest(Enums::eState state)
{
	if (state == Enums::eState::Undefined)
	{
		return false;
	}

	auto res = mRequestedDeactivate.insert(state);
	return (res.second);
}

bool StateRequestStack::addFullFocusRequest(Enums::eState state)
{
	if (state == Enums::eState::Undefined)
	{
		return false;
	}

	auto res = mRequestedFullFocus.insert(state);
	return (res.second);
}

Enums::eState StateRequestStack::popStartRequest()
{
	if (mRequestedStart.empty())
	{
		return Enums::eState::Undefined;
	}

	Enums::eState firstState = *(mRequestedStart.rbegin());
	mRequestedStart.erase(firstState);

	if (firstState == Enums::eState::Undefined)
	{
		return popStartRequest();
	}
	else
	{
		return firstState;
	}
}

Enums::eState StateRequestStack::popStopRequest()
{
	if (mRequestedStop.empty())
	{
		return Enums::eState::Undefined;
	}

	Enums::eState firstState = *(mRequestedStop.rbegin());
	mRequestedStop.erase(firstState);

	if (firstState == Enums::eState::Undefined)
	{
		return popStopRequest();
	}
	else
	{
		return firstState;
	}
}

Enums::eState StateRequestStack::popActivateRequest()
{
	if (mRequestedActivate.empty())
	{
		return Enums::eState::Undefined;
	}

	Enums::eState firstState = *(mRequestedActivate.rbegin());
	mRequestedActivate.erase(firstState);

	if (firstState == Enums::eState::Undefined)
	{
		return popActivateRequest();
	}
	else
	{
		return firstState;
	}
}

Enums::eState StateRequestStack::popDeactivateRequest()
{
	if (mRequestedDeactivate.empty())
	{
		return Enums::eState::Undefined;
	}

	Enums::eState firstState = *(mRequestedDeactivate.rbegin());
	mRequestedDeactivate.erase(firstState);

	if (firstState == Enums::eState::Undefined)
	{
		return popDeactivateRequest();
	}
	else
	{
		return firstState;
	}
}

Enums::eState StateRequestStack::popFullFocusRequest()
{
	if (mRequestedFullFocus.empty())
	{
		return Enums::eState::Undefined;
	}

	Enums::eState firstState = *(mRequestedFullFocus.rbegin());
	mRequestedFullFocus.erase(firstState);

	if (firstState == Enums::eState::Undefined)
	{
		return popFullFocusRequest();
	}
	else
	{
		return firstState;
	}
}

void StateRequestStack::clearRequests()
{
	mRequestedStart.clear();
	mRequestedStop.clear();
	mRequestedActivate.clear();
	mRequestedDeactivate.clear();
	mRequestedFullFocus.clear();
}
