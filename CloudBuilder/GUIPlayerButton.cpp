#include "GUIPlayerButton.h"
#include "InstructionPlayer.h"



GUIPlayerButton::GUIPlayerButton(InstructionPlayer & player, Enums::eInstructionPlayerCommand command, sf::Vector2f positionRatio) :
	GUIButton(positionRatio),
	mPlayCommand(command),
	mPauseCommand(command),
	mStopCommand(command),
	mPlayer(player)//,
	//mPositionRatio(positionRatio)
{
}

GUIPlayerButton::GUIPlayerButton(InstructionPlayer & player, Enums::eInstructionPlayerCommand playCommand, Enums::eInstructionPlayerCommand pauseCommand, Enums::eInstructionPlayerCommand stopCommand, sf::Vector2f positionRatio):
	GUIButton(positionRatio),
	mPlayCommand(playCommand),
	mPauseCommand(pauseCommand),
	mStopCommand(stopCommand),
	mPlayer(player)//,
	//mPositionRatio(positionRatio)
{
}


GUIPlayerButton::~GUIPlayerButton()
{
}

void GUIPlayerButton::clicked()
{
	mPlayer.processPlayerCommand(getCurrentCommand());
}

Enums::eInstructionPlayerCommand GUIPlayerButton::getCurrentCommand()
{
	switch (mPlayer.getPlayerState())
	{
	case Enums::eInstructionPlayerCommand::CmdPlay: return mPlayCommand;
	case Enums::eInstructionPlayerCommand::CmdPause: return mPauseCommand;
	case Enums::eInstructionPlayerCommand::CmdStop: return mStopCommand;
	default: return Enums::eInstructionPlayerCommand::CmdUnknown;
	}
}

//void GUIPlayerButton::handleEventCurrent(const sf::Event & event)
//{
//	switch (event.type)
//	{
//	case sf::Event::MouseButtonReleased:
//		if (event.mouseButton.button == sf::Mouse::Button::Left && event.mouseButton.x > mTopLeftCorner.x && event.mouseButton.x < mTopLeftCorner.x + mBoundingBox.x && event.mouseButton.y > mTopLeftCorner.y && event.mouseButton.y < mTopLeftCorner.y + mBoundingBox.y)
//		{
//			mPlayer.processPlayerCommand(getCurrentCommand());
//		}
//		break;
//	}
//}

void GUIPlayerButton::drawCurrent(sf::RenderTarget & target)
{
	if (getCurrentCommand() != Enums::eInstructionPlayerCommand::CmdUnknown)
	{
		sf::RectangleShape background(mBoundingBox);
		background.setPosition(mTopLeftCorner);

		if (getCurrentCommand() == mPlayer.getPlayerSpeed())
		{
			background.setFillColor(sf::Color(63, 63, 255));
		}
		else
		{
			background.setFillColor(sf::Color(0, 0, 255));
		}
		
		target.draw(background);

		drawIcon(target);
	}	
}

void GUIPlayerButton::drawIcon(sf::RenderTarget & target)
{
	std::list<sf::ConvexShape> icons;

	switch (getCurrentCommand())
	{
	case Enums::eInstructionPlayerCommand::CmdPlay:
	{
		sf::ConvexShape iconPlay;
		iconPlay.setPointCount(3);
		iconPlay.setPoint(0, sf::Vector2f(0.2f, 0.2f));
		iconPlay.setPoint(1, sf::Vector2f(0.2f, 0.8f));
		iconPlay.setPoint(2, sf::Vector2f(0.8f, 0.5f));
		icons.push_back(iconPlay);
		break;
	}
	case Enums::eInstructionPlayerCommand::CmdPause:
	{
		sf::ConvexShape iconLeft;
		iconLeft.setPointCount(4);
		iconLeft.setPoint(0, sf::Vector2f(0.25f, 0.2f));
		iconLeft.setPoint(1, sf::Vector2f(0.45f, 0.2f));
		iconLeft.setPoint(2, sf::Vector2f(0.45f, 0.8f));
		iconLeft.setPoint(3, sf::Vector2f(0.25f, 0.8f));
		icons.push_back(iconLeft);
		sf::ConvexShape iconRight;
		iconRight.setPointCount(4);
		iconRight.setPoint(0, sf::Vector2f(0.55f, 0.2f));
		iconRight.setPoint(1, sf::Vector2f(0.75f, 0.2f));
		iconRight.setPoint(2, sf::Vector2f(0.75f, 0.8f));
		iconRight.setPoint(3, sf::Vector2f(0.55f, 0.8f));
		icons.push_back(iconRight);
		break;
	}
	case Enums::eInstructionPlayerCommand::CmdStop:
	{
		sf::ConvexShape iconStop;
		iconStop.setPointCount(4);
		iconStop.setPoint(0, sf::Vector2f(0.2f, 0.2f));
		iconStop.setPoint(1, sf::Vector2f(0.8f, 0.2f));
		iconStop.setPoint(2, sf::Vector2f(0.8f, 0.8f));
		iconStop.setPoint(3, sf::Vector2f(0.2f, 0.8f));
		icons.push_back(iconStop);
		break;
	}
	case Enums::eInstructionPlayerCommand::CmdStep:
	{
		sf::ConvexShape iconLeft;
		iconLeft.setPointCount(3);
		iconLeft.setPoint(0, sf::Vector2f(0.2f, 0.2f));
		iconLeft.setPoint(1, sf::Vector2f(0.2f, 0.8f));
		iconLeft.setPoint(2, sf::Vector2f(0.6f, 0.5f));
		icons.push_back(iconLeft);
		sf::ConvexShape iconRight;
		iconRight.setPointCount(4);
		iconRight.setPoint(0, sf::Vector2f(0.8f, 0.2f));
		iconRight.setPoint(1, sf::Vector2f(0.6f, 0.2f));
		iconRight.setPoint(2, sf::Vector2f(0.6f, 0.8f));
		iconRight.setPoint(3, sf::Vector2f(0.8f, 0.8f));
		icons.push_back(iconRight);
		break;
	}
	case Enums::eInstructionPlayerCommand::CmdSpeedSlow:
	{
		sf::ConvexShape iconSlow;
		iconSlow.setPointCount(3);
		iconSlow.setPoint(0, sf::Vector2f(0.38f, 0.3f));
		iconSlow.setPoint(1, sf::Vector2f(0.38f, 0.7f));
		iconSlow.setPoint(2, sf::Vector2f(0.62f, 0.5f));
		icons.push_back(iconSlow);
		break;
	}
	case Enums::eInstructionPlayerCommand::CmdSpeedMedium:
	{
		sf::ConvexShape iconSlow;
		iconSlow.setPointCount(4);
		iconSlow.setPoint(0, sf::Vector2f(0.32f, 0.3f));
		iconSlow.setPoint(1, sf::Vector2f(0.32f, 0.7f));
		iconSlow.setPoint(2, sf::Vector2f(0.44f, 0.6f));
		iconSlow.setPoint(3, sf::Vector2f(0.44f, 0.4f));
		icons.push_back(iconSlow);
		sf::ConvexShape iconMedium;
		iconMedium.setPointCount(3);
		iconMedium.setPoint(0, sf::Vector2f(0.44f, 0.3f));
		iconMedium.setPoint(1, sf::Vector2f(0.44f, 0.7f));
		iconMedium.setPoint(2, sf::Vector2f(0.68f, 0.5f));
		icons.push_back(iconMedium);
		break;
	}
	case Enums::eInstructionPlayerCommand::CmdSpeedFast:
	{
		sf::ConvexShape iconSlow;
		iconSlow.setPointCount(4);
		iconSlow.setPoint(0, sf::Vector2f(0.26f, 0.3f));
		iconSlow.setPoint(1, sf::Vector2f(0.26f, 0.7f));
		iconSlow.setPoint(2, sf::Vector2f(0.38f, 0.6f));
		iconSlow.setPoint(3, sf::Vector2f(0.38f, 0.4f));
		icons.push_back(iconSlow);
		sf::ConvexShape iconMedium;
		iconMedium.setPointCount(4);
		iconMedium.setPoint(0, sf::Vector2f(0.38f, 0.3f));
		iconMedium.setPoint(1, sf::Vector2f(0.38f, 0.7f));
		iconMedium.setPoint(2, sf::Vector2f(0.5f, 0.6f));
		iconMedium.setPoint(3, sf::Vector2f(0.5f, 0.4f));
		icons.push_back(iconMedium);
		sf::ConvexShape iconFast;
		iconFast.setPointCount(3);
		iconFast.setPoint(0, sf::Vector2f(0.5f, 0.3f));
		iconFast.setPoint(1, sf::Vector2f(0.5f, 0.7f));
		iconFast.setPoint(2, sf::Vector2f(0.74f, 0.5f));
		icons.push_back(iconFast);
		break;
	}
	case Enums::eInstructionPlayerCommand::CmdSpeedInstant:
	{
		sf::ConvexShape iconSlow;
		iconSlow.setPointCount(4);
		iconSlow.setPoint(0, sf::Vector2f(0.2f, 0.3f));
		iconSlow.setPoint(1, sf::Vector2f(0.2f, 0.7f));
		iconSlow.setPoint(2, sf::Vector2f(0.32f, 0.6f));
		iconSlow.setPoint(3, sf::Vector2f(0.32f, 0.4f));
		icons.push_back(iconSlow);
		sf::ConvexShape iconMedium;
		iconMedium.setPointCount(4);
		iconMedium.setPoint(0, sf::Vector2f(0.32f, 0.3f));
		iconMedium.setPoint(1, sf::Vector2f(0.32f, 0.7f));
		iconMedium.setPoint(2, sf::Vector2f(0.44f, 0.6f));
		iconMedium.setPoint(3, sf::Vector2f(0.44f, 0.4f));
		icons.push_back(iconMedium);
		sf::ConvexShape iconFast;
		iconFast.setPointCount(4);
		iconFast.setPoint(0, sf::Vector2f(0.44f, 0.3f));
		iconFast.setPoint(1, sf::Vector2f(0.44f, 0.7f));
		iconFast.setPoint(2, sf::Vector2f(0.56f, 0.6f));
		iconFast.setPoint(3, sf::Vector2f(0.56f, 0.4f));
		icons.push_back(iconFast);
		sf::ConvexShape iconInstant;
		iconInstant.setPointCount(3);
		iconInstant.setPoint(0, sf::Vector2f(0.56f, 0.3f));
		iconInstant.setPoint(1, sf::Vector2f(0.56f, 0.7f));
		iconInstant.setPoint(2, sf::Vector2f(0.8f, 0.5f));
		icons.push_back(iconInstant);
		break;
	}
	default: break;
	}

	for (sf::ConvexShape& icon : icons)
	{
		icon.scale(mBoundingBox);
		icon.move(mTopLeftCorner);
		icon.setFillColor(sf::Color(127, 127, 255));
		target.draw(icon);
	}
}

//void GUIPlayerButton::setSquareSize(sf::Vector2f newSize)
//{
//	mBoundingBox = newSize;
//}
//
//void GUIPlayerButton::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
//{
//	//mBoundingBox set in setSquareSize to be called before this
//	mTopLeftCorner.x = minCorner.x + mPositionRatio.x * maxBox.x - mBoundingBox.x / 2.0f;
//	mTopLeftCorner.y = minCorner.y + mPositionRatio.y * maxBox.y - mBoundingBox.y / 2.0f;
//}
