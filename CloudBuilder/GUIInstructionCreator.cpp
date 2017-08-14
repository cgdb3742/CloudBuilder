#include "GUIInstructionCreator.h"



GUIInstructionCreator::GUIInstructionCreator(GameContext& gameContext):
	GUIButton(gameContext, sf::Vector2f(0.0f, 0.0f)),
	mType(Enums::eInstruction::Unassigned),
	mInstruction(InstructionSquare::createNewInstructionSquare(gameContext, Enums::eInstruction::Unassigned))//,
	//mPositionRatio(sf::Vector2f(0.0f,0.0f))
{
}

GUIInstructionCreator::GUIInstructionCreator(GameContext& gameContext, Enums::eInstruction type, sf::Vector2f positionRatio):
	GUIButton(gameContext, positionRatio),
	mType(type),
	mInstruction(InstructionSquare::createNewInstructionSquare(gameContext, type))//,
	//mPositionRatio(positionRatio)
{
}

GUIInstructionCreator::GUIInstructionCreator(const GUIInstructionCreator & toCopy):
	GUIButton(toCopy),
	mType(toCopy.mType),
	//mInstruction(nullptr),
	//mInstruction(std::move(toCopy.mInstruction)),
	//mInstruction(std::make_unique<InstructionSquare>(InstructionSquare(*toCopy.mInstruction))),
	mInstruction(InstructionSquare::createNewInstructionSquare(toCopy.mGameContext, toCopy.mType))//,
	//mPositionRatio(toCopy.mPositionRatio)
{
	//mInstruction = std::move(toCopy.mInstruction);
}


GUIInstructionCreator::~GUIInstructionCreator()
{
}

InstructionSquare::InstructionSquarePtr GUIInstructionCreator::giveToDrag(sf::Vector2f mousePos)
{
	sf::Vector2f relativeMousePos = mousePos - mTopLeftCorner;

	if (relativeMousePos.x > 0 && relativeMousePos.x < mBoundingBox.x && relativeMousePos.y > 0 && relativeMousePos.y < mBoundingBox.y)
	{
		return createNewInstruction();
	}

	return nullptr;
}

InstructionSquare::InstructionSquarePtr GUIInstructionCreator::createNewInstruction()
{
	return InstructionSquare::createNewInstructionSquare(mGameContext, mType);
}

//void GUIInstructionCreator::setSquareSize(sf::Vector2f newSize)
//{
//	mBoundingBox = newSize;
//}

//void GUIInstructionCreator::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
//{
//	//mBoundingBox set in setSquareSize to be called before this
//	mTopLeftCorner.x = minCorner.x + mPositionRatio.x * maxBox.x - mBoundingBox.x / 2.0f;
//	mTopLeftCorner.y = minCorner.y + mPositionRatio.y * maxBox.y - mBoundingBox.y / 2.0f;
//}

void GUIInstructionCreator::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape background(mBoundingBox);
	background.setPosition(mTopLeftCorner);
	background.setFillColor(sf::Color(255, 0, 255));
	target.draw(background);
}

void GUIInstructionCreator::updateChildsVector()
{
	mChilds.clear();
	mChilds.push_back(*mInstruction);
}
