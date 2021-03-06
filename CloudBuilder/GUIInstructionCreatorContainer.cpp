//#include <utility>
#include "GUIInstructionCreatorContainer.h"
#include "InstructionBoard.h"
#include "Game.h"



GUIInstructionCreatorContainer::GUIInstructionCreatorContainer(GameContext& gameContext, Level& level, InstructionBoard& board):
	GameEntity(gameContext),
	mTrashBin(gameContext, sf::Vector2f(42.0f / 50.0f, 3.0f / 11.0f)),
	mReset(gameContext, sf::Vector2f(42.0f / 50.0f, 8.0f / 11.0f), level),
	mBoard(board)
{
	setUpCreators();
}


GUIInstructionCreatorContainer::~GUIInstructionCreatorContainer()
{
}

void GUIInstructionCreatorContainer::setUpCreators()
{
	//TODO Fail if duplicates in availableInstructions
	for (Enums::eInstruction instruction : mGameContext.levelData.availableInstructions)
	{
		//Note : mCreators.insert(std::pair<Enums::eInstruction, GUIInstructionCreator>(instruction, GUIInstructionCreator(mGameContext, instruction, positionRatio))); would be easier to read ?
		switch (instruction)
		{
		case Enums::eInstruction::ActMove: mCreators.insert(std::pair<Enums::eInstruction, GUIInstructionCreator>(Enums::eInstruction::ActMove, GUIInstructionCreator(mGameContext, Enums::eInstruction::ActMove, sf::Vector2f(3.0f / 50.0f, 3.0f / 11.0f)))); break;
		case Enums::eInstruction::ActSetCloud: mCreators.insert(std::pair<Enums::eInstruction, GUIInstructionCreator>(Enums::eInstruction::ActSetCloud, GUIInstructionCreator(mGameContext, Enums::eInstruction::ActSetCloud, sf::Vector2f(3.0f / 50.0f, 8.0f / 11.0f)))); break;
		case Enums::eInstruction::ActSetColor: mCreators.insert(std::pair<Enums::eInstruction, GUIInstructionCreator>(Enums::eInstruction::ActSetColor, GUIInstructionCreator(mGameContext, Enums::eInstruction::ActSetColor, sf::Vector2f(8.0f / 50.0f, 8.0f / 11.0f)))); break;
		case Enums::eInstruction::CheckCloud: mCreators.insert(std::pair<Enums::eInstruction, GUIInstructionCreator>(Enums::eInstruction::CheckCloud, GUIInstructionCreator(mGameContext, Enums::eInstruction::CheckCloud, sf::Vector2f(14.0f / 50.0f, 8.0f / 11.0f)))); break;
		case Enums::eInstruction::CheckColor: mCreators.insert(std::pair<Enums::eInstruction, GUIInstructionCreator>(Enums::eInstruction::CheckColor, GUIInstructionCreator(mGameContext, Enums::eInstruction::CheckColor, sf::Vector2f(19.0f / 50.0f, 8.0f / 11.0f)))); break;
		case Enums::eInstruction::CheckBorder: mCreators.insert(std::pair<Enums::eInstruction, GUIInstructionCreator>(Enums::eInstruction::CheckBorder, GUIInstructionCreator(mGameContext, Enums::eInstruction::CheckBorder, sf::Vector2f(14.0f / 50.0f, 3.0f / 11.0f)))); break;
		case Enums::eInstruction::FlowWait: mCreators.insert(std::pair<Enums::eInstruction, GUIInstructionCreator>(Enums::eInstruction::FlowWait, GUIInstructionCreator(mGameContext, Enums::eInstruction::FlowWait, sf::Vector2f(25.0f / 50.0f, 3.0f / 11.0f)))); break;
		case Enums::eInstruction::FlowPause: mCreators.insert(std::pair<Enums::eInstruction, GUIInstructionCreator>(Enums::eInstruction::FlowPause, GUIInstructionCreator(mGameContext, Enums::eInstruction::FlowPause, sf::Vector2f(25.0f / 50.0f, 8.0f / 11.0f)))); break;
		case Enums::eInstruction::FlowResume: mCreators.insert(std::pair<Enums::eInstruction, GUIInstructionCreator>(Enums::eInstruction::FlowResume, GUIInstructionCreator(mGameContext, Enums::eInstruction::FlowResume, sf::Vector2f(30.0f / 50.0f, 8.0f / 11.0f)))); break;
		case Enums::eInstruction::FlowSync: mCreators.insert(std::pair<Enums::eInstruction, GUIInstructionCreator>(Enums::eInstruction::FlowSync, GUIInstructionCreator(mGameContext, Enums::eInstruction::FlowSync, sf::Vector2f(30.0f / 50.0f, 3.0f / 11.0f)))); break;
		case Enums::eInstruction::SpeAccept: mCreators.insert(std::pair<Enums::eInstruction, GUIInstructionCreator>(Enums::eInstruction::SpeAccept, GUIInstructionCreator(mGameContext, Enums::eInstruction::SpeAccept, sf::Vector2f(36.0f / 50.0f, 3.0f / 11.0f)))); break;
		case Enums::eInstruction::SpeReject: mCreators.insert(std::pair<Enums::eInstruction, GUIInstructionCreator>(Enums::eInstruction::SpeReject, GUIInstructionCreator(mGameContext, Enums::eInstruction::SpeReject, sf::Vector2f(36.0f / 50.0f, 8.0f / 11.0f)))); break;
		default: break;
		}
	}
}

//TODO what if board square size too big ?
sf::Vector2f GUIInstructionCreatorContainer::computeChildsBoundingBox()
{
	//float size = std::min(mBoard.getSquareSize().x, std::min(mBoundingBox.x / 16.0f, mBoundingBox.y / 4.0f));
	//float size = std::min(mBoard.getSquareSize().x, std::min(mBoundingBox.x * 2.0f / 29.0f, mBoundingBox.y * 2.0f / 7.0f));

	//return sf::Vector2f(size, size);
	return mBoard.getSquareSize();
}

//void GUIInstructionCreatorContainer::setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox)
//{
//	sf::Vector2f size = mBoard.getSquareSize(); //TODO Verify this is updated AFTER the InstructionBoard
//
//	for (auto &creator : mCreators)
//	{
//		creator.second.setSquareSize(size);
//		creator.second.setPositionAll(minCorner, maxBox);
//	}
//}

bool GUIInstructionCreatorContainer::canGetFromDrag(sf::Vector2f mousePos)
{
	return mTrashBin.canGetFromDrag(mousePos);
}

InstructionSquare::InstructionSquarePtr GUIInstructionCreatorContainer::getFromDrag(sf::Vector2f mousePos, InstructionSquare::InstructionSquarePtr ptr)
{
	return mTrashBin.getFromDrag(mousePos, std::move(ptr));
}

//TODO Give only if mouse in inner bounding box ?
InstructionSquare::InstructionSquarePtr GUIInstructionCreatorContainer::giveToDrag(sf::Vector2f mousePos)
{
	for (auto &creator : mCreators)
	{
		sf::Vector2f relativeMousePos = mousePos - creator.second.getTopLeftCorner();

		if (relativeMousePos.x > 0 && relativeMousePos.x < creator.second.getBoundingBox().x && relativeMousePos.y > 0 && relativeMousePos.y < creator.second.getBoundingBox().y)
		{
			return creator.second.giveToDrag(mousePos);
		}
	}

	return nullptr;
}

void GUIInstructionCreatorContainer::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape background(mBoundingBox);
	background.setPosition(mTopLeftCorner);
	background.setFillColor(sf::Color(191, 0, 191, 127));
	target.draw(background);

	sf::RectangleShape line1(sf::Vector2f(1.0f, mBoundingBox.y * 0.8f));
	line1.setPosition(sf::Vector2f(mTopLeftCorner.x + mBoundingBox.x * 11.0f / 50.0f, mTopLeftCorner.y + mBoundingBox.y * 0.1f));
	line1.setFillColor(sf::Color(63, 0, 63));
	target.draw(line1);

	sf::RectangleShape line2(sf::Vector2f(1.0f, mBoundingBox.y * 0.8f));
	line2.setPosition(sf::Vector2f(mTopLeftCorner.x + mBoundingBox.x * 22.0f / 50.0f, mTopLeftCorner.y + mBoundingBox.y * 0.1f));
	line2.setFillColor(sf::Color(63, 0, 63));
	target.draw(line2);

	sf::RectangleShape line3(sf::Vector2f(1.0f, mBoundingBox.y * 0.8f));
	line3.setPosition(sf::Vector2f(mTopLeftCorner.x + mBoundingBox.x * 33.0f / 50.0f, mTopLeftCorner.y + mBoundingBox.y * 0.1f));
	line3.setFillColor(sf::Color(63, 0, 63));
	target.draw(line3);

	sf::RectangleShape line4(sf::Vector2f(1.0f, mBoundingBox.y * 0.8f));
	line4.setPosition(sf::Vector2f(mTopLeftCorner.x + mBoundingBox.x * 39.0f / 50.0f, mTopLeftCorner.y + mBoundingBox.y * 0.1f));
	line4.setFillColor(sf::Color(63, 0, 63));
	target.draw(line4);
}

void GUIInstructionCreatorContainer::updateChildsVector()
{
	mChilds.clear();

	for (auto &creator : mCreators)
	{
		mChilds.push_back(creator.second);
	}

	mChilds.push_back(mTrashBin);
	mChilds.push_back(mReset);
}
