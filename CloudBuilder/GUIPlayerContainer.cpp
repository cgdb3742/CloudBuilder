#include "GUIPlayerContainer.h"



GUIPlayerContainer::GUIPlayerContainer(InstructionPlayer& player)
{
	mButtons.push_back(GUIPlayerButton(player, Enums::eInstructionPlayerCommand::CmdPause, Enums::eInstructionPlayerCommand::CmdPlay, Enums::eInstructionPlayerCommand::CmdPlay, sf::Vector2f(0.2f,0.25f))); //Play/Pause
	mButtons.push_back(GUIPlayerButton(player, Enums::eInstructionPlayerCommand::CmdStep, sf::Vector2f(0.4f, 0.25f))); //Play step
	mButtons.push_back(GUIPlayerButton(player, Enums::eInstructionPlayerCommand::CmdStop, Enums::eInstructionPlayerCommand::CmdStop, Enums::eInstructionPlayerCommand::CmdUnknown, sf::Vector2f(0.6f, 0.25f))); //Stop
	mButtons.push_back(GUIPlayerButton(player, Enums::eInstructionPlayerCommand::CmdSpeedSlow, sf::Vector2f(0.2f, 0.75f))); //Speed : slow
	mButtons.push_back(GUIPlayerButton(player, Enums::eInstructionPlayerCommand::CmdSpeedMedium, sf::Vector2f(0.4f, 0.75f))); //Speed : medium
	mButtons.push_back(GUIPlayerButton(player, Enums::eInstructionPlayerCommand::CmdSpeedFast, sf::Vector2f(0.6f, 0.75f))); //Speed : fast
	mButtons.push_back(GUIPlayerButton(player, Enums::eInstructionPlayerCommand::CmdSpeedInstant, sf::Vector2f(0.8f, 0.75f))); //Speed : instant
}


GUIPlayerContainer::~GUIPlayerContainer()
{
}

void GUIPlayerContainer::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape background(mBoundingBox);
	background.setPosition(mTopLeftCorner);
	background.setFillColor(sf::Color(0, 0, 191, 127));
	target.draw(background);
}

void GUIPlayerContainer::setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	float minSize = std::min(maxBox.x / 4.0f, maxBox.y / 2.0f);
	float margin = minSize * 0.1f;
	sf::Vector2f size(minSize - 2.0f * margin, minSize - 2.0f * margin); //TODO set square size

	for (GUIPlayerButton& button : mButtons)
	{
		button.setBoundingBoxCurrent(size);
		button.setPositionAll(minCorner + sf::Vector2f(margin, margin), maxBox - 2.0f * sf::Vector2f(margin, margin));
	}
}

void GUIPlayerContainer::updateChildsVector()
{
	mChilds.clear();

	for (GUIPlayerButton& button : mButtons)
	{
		mChilds.push_back(button);
	}
}
