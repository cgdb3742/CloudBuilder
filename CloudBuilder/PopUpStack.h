#pragma once
#include <string>
#include <list>

class StateRequestStack;

struct PopUpData
{
	PopUpData() : mainMessage(L"error"), buttonMessage(L"error") {}
	PopUpData(std::wstring mainMess, std::wstring buttonMess) : mainMessage(mainMess), buttonMessage(buttonMess) {}

	std::wstring mainMessage;
	std::wstring buttonMessage;
};

class PopUpStack
{
public:
	PopUpStack(StateRequestStack& stateStack);
	~PopUpStack();

	bool isEmpty();
	void addMessage(PopUpData message);
	void addMessage(std::wstring mainMessage, std::wstring buttonMessage);
	PopUpData popMessage();
private:
	std::list<PopUpData> mStack;

	StateRequestStack& mStateStack;
};

