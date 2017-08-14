#pragma once
#include <string>
#include <list>

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
	PopUpStack();
	~PopUpStack();

	bool isEmpty();
	void addMessage(PopUpData message);
	void addMessage(std::string mainMessage, std::string buttonMessage);
	PopUpData popMessage();
private:
	std::list<PopUpData> mStack;
};

