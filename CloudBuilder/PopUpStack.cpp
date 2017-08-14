#include "PopUpStack.h"



PopUpStack::PopUpStack()
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
}

void PopUpStack::addMessage(std::string mainMessage, std::string buttonMessage)
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
