#pragma once
#include <set>
#include "Enums.h"

class StateRequestStack
{
public:
	StateRequestStack();
	~StateRequestStack();

	bool addStartRequest(Enums::eState state);
	bool addStopRequest(Enums::eState state);
	bool addActivateRequest(Enums::eState state);
	bool addDeactivateRequest(Enums::eState state);
	bool addFullFocusRequest(Enums::eState state);
	Enums::eState popStartRequest();
	Enums::eState popStopRequest();
	Enums::eState popActivateRequest();
	Enums::eState popDeactivateRequest();
	Enums::eState popFullFocusRequest();
	void clearRequests();
private:
	std::set<Enums::eState> mRequestedStart;
	std::set<Enums::eState> mRequestedStop;
	std::set<Enums::eState> mRequestedActivate;
	std::set<Enums::eState> mRequestedDeactivate;
	std::set<Enums::eState> mRequestedFullFocus;
};

