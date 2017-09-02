#pragma once
#include <string>
#include <list>

class StateRequestStack;

struct PopUpData
{
	PopUpData() : mainMessage("error"), buttonMessage("error") {}
	PopUpData(std::string mainMess, std::string buttonMess) : mainMessage(mainMess), buttonMessage(buttonMess) {}

	std::string mainMessage;
	std::string buttonMessage;
};

class PopUpStack
{
public:
	PopUpStack(StateRequestStack& stateStack);
	~PopUpStack();

	bool isEmpty();
	void addMessage(PopUpData message);
	void addMessage(std::string mainMessage, std::string buttonMessage);
	PopUpData popMessage();
private:
	std::list<PopUpData> mStack;

	StateRequestStack& mStateStack;
};

