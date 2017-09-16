#include "PopUpStack.h"
#include "StateRequestStack.h"


PopUpStack::PopUpStack(StateRequestStack & stateStack):
	mStateStack(stateStack)
{
}


PopUpStack::~PopUpStack()
{
}

bool PopUpStack::isEmpty()
{
	return mStack.empty();
}

void PopUpStack::addMessage(PopUpData message)
{
	mStack.push_back(message);
	mStateStack.addStartRequest(Enums::eState::PopUp);
	mStateStack.addFullFocusRequest(Enums::eState::PopUp);
}

void PopUpStack::addMessage(std::wstring mainMessage, std::wstring buttonMessage)
{
	addMessage(PopUpData(mainMessage, buttonMessage));
}

PopUpData PopUpStack::popMessage()
{
	if (isEmpty())
	{
		return PopUpData();
	}

	PopUpData toReturn(mStack.front());
	mStack.pop_front();
	return toReturn;
}
