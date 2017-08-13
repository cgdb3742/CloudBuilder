#include "GUIInstructionModifierContainer.h"
#include "InstructionBoard.h"



GUIInstructionModifierContainer::GUIInstructionModifierContainer(InstructionBoard& board):
	mBoard(board)
{
}


GUIInstructionModifierContainer::~GUIInstructionModifierContainer()
{
}

void GUIInstructionModifierContainer::setUpModifiers()
{
	createAllModifiers(mBoard.getSelectionI(), mBoard.getSelectionJ(), mBoard.getSelection());
	updateChildsVectorAll();
	setPositionChilds(mTopLeftCorner, mBoundingBox);
}

//void GUIInstructionModifierContainer::updateCurrent(sf::Time dt)
//{
//	if (mBoard.hasUpdatedSelection()) //Note : can only happen in build mode
//	{
//		createAllModifiers(mBoard.getSelection());
//	}
//}

void GUIInstructionModifierContainer::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape background(mBoundingBox);
	background.setPosition(mTopLeftCorner);
	background.setFillColor(sf::Color(0, 191, 191, 127));
	target.draw(background);

	sf::RectangleShape line(sf::Vector2f(1.0f, mBoundingBox.y * 0.8f));
	line.setPosition(sf::Vector2f(mTopLeftCorner.x + mBoundingBox.x * 0.6f, mTopLeftCorner.y + mBoundingBox.y * 0.1f));
	line.setFillColor(sf::Color(0, 63, 63));
	target.draw(line);
}

sf::Vector2f GUIInstructionModifierContainer::computeChildsBoundingBox()
{
	float minSize = std::min(mBoundingBox.x / 5.0f, mBoundingBox.y); //Max 5 modifiers on an instruction square
	float margin = minSize * 0.2f;

	return sf::Vector2f(minSize - 2.0f * margin, minSize - 2.0f * margin);
}

void GUIInstructionModifierContainer::setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	float minSize = std::min(mBoundingBox.x / 5.0f, mBoundingBox.y); //Max 5 modifiers on an instruction square
	float margin = minSize * 0.2f;

	sf::Vector2f childBoundingBox = computeChildsBoundingBox();

	for (GUIInstructionModifier& modifier : mModifiers)
	{
		modifier.setBoundingBoxCurrent(childBoundingBox);
		modifier.setPositionAll(minCorner + sf::Vector2f(margin, margin), maxBox - 2.0f * sf::Vector2f(margin, margin));
	}
}

void GUIInstructionModifierContainer::updateChildsVector()
{
	mChilds.clear();

	for (GUIInstructionModifier& modifier : mModifiers)
	{
		mChilds.push_back(modifier);
	}
}

void GUIInstructionModifierContainer::createAllModifiers(unsigned int i, unsigned int j, InstructionSquare & instruction)
{
	mModifiers.clear();

	for (Enums::eInstructionModifier modifier : instruction.getPossibleModifications())
	{
		createModifiers(i, j, modifier);
	}
}

//TODO Implement missing modifiers 
void GUIInstructionModifierContainer::createModifiers(unsigned int i, unsigned int j, Enums::eInstructionModifier modifier)
{
	sf::ConvexShape shape;

	switch (modifier)
	{
	case Enums::eInstructionModifier::Unknown: break;
	case Enums::eInstructionModifier::NextDir: //Pos 4.5/5 (offset : 0.8f)
	{
		if (mBoard.canMove(i, j, Enums::eDir::Left))
		{
			shape.setPointCount(5);
			shape.setPoint(0, sf::Vector2f(0.0f, 0.2f));
			shape.setPoint(1, sf::Vector2f(0.2f, 0.2f));
			shape.setPoint(2, sf::Vector2f(0.5f, 0.5f));
			shape.setPoint(3, sf::Vector2f(0.2f, 0.8f));
			shape.setPoint(4, sf::Vector2f(0.0f, 0.8f));
			mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::NextDir, Enums::eDir::Left), mBoard, sf::Vector2f(0.8f, 0.5f), shape));
		}
		if (mBoard.canMove(i, j, Enums::eDir::Right))
		{
			shape.setPointCount(5);
			shape.setPoint(0, sf::Vector2f(1.0f, 0.2f));
			shape.setPoint(1, sf::Vector2f(0.8f, 0.2f));
			shape.setPoint(2, sf::Vector2f(0.5f, 0.5f));
			shape.setPoint(3, sf::Vector2f(0.8f, 0.8f));
			shape.setPoint(4, sf::Vector2f(1.0f, 0.8f));
			mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::NextDir, Enums::eDir::Right), mBoard, sf::Vector2f(0.8f, 0.5f), shape));
		}
		if (mBoard.canMove(i, j, Enums::eDir::Up))
		{
			shape.setPointCount(5);
			shape.setPoint(0, sf::Vector2f(0.2f, 0.0f));
			shape.setPoint(1, sf::Vector2f(0.2f, 0.2f));
			shape.setPoint(2, sf::Vector2f(0.5f, 0.5f));
			shape.setPoint(3, sf::Vector2f(0.8f, 0.2f));
			shape.setPoint(4, sf::Vector2f(0.8f, 0.0f));
			mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::NextDir, Enums::eDir::Up), mBoard, sf::Vector2f(0.8f, 0.5f), shape));
		}
		if (mBoard.canMove(i, j, Enums::eDir::Down))
		{
			shape.setPointCount(5);
			shape.setPoint(0, sf::Vector2f(0.2f, 1.0f));
			shape.setPoint(1, sf::Vector2f(0.2f, 0.8f));
			shape.setPoint(2, sf::Vector2f(0.5f, 0.5f));
			shape.setPoint(3, sf::Vector2f(0.8f, 0.8f));
			shape.setPoint(4, sf::Vector2f(0.8f, 1.0f));
			mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::NextDir, Enums::eDir::Down), mBoard, sf::Vector2f(0.8f, 0.5f), shape));
		}
		break;
	}
	case Enums::eInstructionModifier::NextDirTrue: //Pos 4/5 (offset : 0.7f)
		if (mBoard.canMove(i, j, Enums::eDir::Left))
		{
			shape.setPointCount(5);
			shape.setPoint(0, sf::Vector2f(0.0f, 0.2f));
			shape.setPoint(1, sf::Vector2f(0.2f, 0.2f));
			shape.setPoint(2, sf::Vector2f(0.5f, 0.5f));
			shape.setPoint(3, sf::Vector2f(0.2f, 0.8f));
			shape.setPoint(4, sf::Vector2f(0.0f, 0.8f));
			mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::NextDirTrue, Enums::eDir::Left), mBoard, sf::Vector2f(0.7f, 0.5f), shape));
		}
		if (mBoard.canMove(i, j, Enums::eDir::Right))
		{
			shape.setPointCount(5);
			shape.setPoint(0, sf::Vector2f(1.0f, 0.2f));
			shape.setPoint(1, sf::Vector2f(0.8f, 0.2f));
			shape.setPoint(2, sf::Vector2f(0.5f, 0.5f));
			shape.setPoint(3, sf::Vector2f(0.8f, 0.8f));
			shape.setPoint(4, sf::Vector2f(1.0f, 0.8f));
			mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::NextDirTrue, Enums::eDir::Right), mBoard, sf::Vector2f(0.7f, 0.5f), shape));
		}
		if (mBoard.canMove(i, j, Enums::eDir::Up))
		{
			shape.setPointCount(5);
			shape.setPoint(0, sf::Vector2f(0.2f, 0.0f));
			shape.setPoint(1, sf::Vector2f(0.2f, 0.2f));
			shape.setPoint(2, sf::Vector2f(0.5f, 0.5f));
			shape.setPoint(3, sf::Vector2f(0.8f, 0.2f));
			shape.setPoint(4, sf::Vector2f(0.8f, 0.0f));
			mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::NextDirTrue, Enums::eDir::Up), mBoard, sf::Vector2f(0.7f, 0.5f), shape));
		}
		if (mBoard.canMove(i, j, Enums::eDir::Down))
		{
			shape.setPointCount(5);
			shape.setPoint(0, sf::Vector2f(0.2f, 1.0f));
			shape.setPoint(1, sf::Vector2f(0.2f, 0.8f));
			shape.setPoint(2, sf::Vector2f(0.5f, 0.5f));
			shape.setPoint(3, sf::Vector2f(0.8f, 0.8f));
			shape.setPoint(4, sf::Vector2f(0.8f, 1.0f));
			mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::NextDirTrue, Enums::eDir::Down), mBoard, sf::Vector2f(0.7f, 0.5f), shape));
		}
		break;
	case Enums::eInstructionModifier::NextDirFalse: //Pos 5/5 (offset : 0.9f)
		if (mBoard.canMove(i, j, Enums::eDir::Left))
		{
			shape.setPointCount(5);
			shape.setPoint(0, sf::Vector2f(0.0f, 0.2f));
			shape.setPoint(1, sf::Vector2f(0.2f, 0.2f));
			shape.setPoint(2, sf::Vector2f(0.5f, 0.5f));
			shape.setPoint(3, sf::Vector2f(0.2f, 0.8f));
			shape.setPoint(4, sf::Vector2f(0.0f, 0.8f));
			mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::NextDirFalse, Enums::eDir::Left), mBoard, sf::Vector2f(0.9f, 0.5f), shape));
		}
		if (mBoard.canMove(i, j, Enums::eDir::Right))
		{
			shape.setPointCount(5);
			shape.setPoint(0, sf::Vector2f(1.0f, 0.2f));
			shape.setPoint(1, sf::Vector2f(0.8f, 0.2f));
			shape.setPoint(2, sf::Vector2f(0.5f, 0.5f));
			shape.setPoint(3, sf::Vector2f(0.8f, 0.8f));
			shape.setPoint(4, sf::Vector2f(1.0f, 0.8f));
			mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::NextDirFalse, Enums::eDir::Right), mBoard, sf::Vector2f(0.9f, 0.5f), shape));
		}
		if (mBoard.canMove(i, j, Enums::eDir::Up))
		{
			shape.setPointCount(5);
			shape.setPoint(0, sf::Vector2f(0.2f, 0.0f));
			shape.setPoint(1, sf::Vector2f(0.2f, 0.2f));
			shape.setPoint(2, sf::Vector2f(0.5f, 0.5f));
			shape.setPoint(3, sf::Vector2f(0.8f, 0.2f));
			shape.setPoint(4, sf::Vector2f(0.8f, 0.0f));
			mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::NextDirFalse, Enums::eDir::Up), mBoard, sf::Vector2f(0.9f, 0.5f), shape));
		}
		if (mBoard.canMove(i, j, Enums::eDir::Down))
		{
			shape.setPointCount(5);
			shape.setPoint(0, sf::Vector2f(0.2f, 1.0f));
			shape.setPoint(1, sf::Vector2f(0.2f, 0.8f));
			shape.setPoint(2, sf::Vector2f(0.5f, 0.5f));
			shape.setPoint(3, sf::Vector2f(0.8f, 0.8f));
			shape.setPoint(4, sf::Vector2f(0.8f, 1.0f));
			mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::NextDirFalse, Enums::eDir::Down), mBoard, sf::Vector2f(0.9f, 0.5f), shape));
		}
		break;
	case Enums::eInstructionModifier::CheckDir: //Pos 2/5 (offset : 0.3f)
	{
		shape.setPointCount(5);
		shape.setPoint(0, sf::Vector2f(0.0f, 0.5f));
		shape.setPoint(1, sf::Vector2f(0.2f, 0.3f));
		shape.setPoint(2, sf::Vector2f(0.3f, 0.3f));
		shape.setPoint(3, sf::Vector2f(0.3f, 0.7f));
		shape.setPoint(4, sf::Vector2f(0.2f, 0.7f));
		mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::CheckDir, Enums::eDir::Left), mBoard, sf::Vector2f(0.3f, 0.5f), shape));
		shape.setPointCount(5);
		shape.setPoint(0, sf::Vector2f(1.0f, 0.5f));
		shape.setPoint(1, sf::Vector2f(0.8f, 0.3f));
		shape.setPoint(2, sf::Vector2f(0.7f, 0.3f));
		shape.setPoint(3, sf::Vector2f(0.7f, 0.7f));
		shape.setPoint(4, sf::Vector2f(0.8f, 0.7f));
		mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::CheckDir, Enums::eDir::Right), mBoard, sf::Vector2f(0.3f, 0.5f), shape));
		shape.setPointCount(5);
		shape.setPoint(0, sf::Vector2f(0.5f, 0.0f));
		shape.setPoint(1, sf::Vector2f(0.3f, 0.2f));
		shape.setPoint(2, sf::Vector2f(0.3f, 0.3f));
		shape.setPoint(3, sf::Vector2f(0.7f, 0.3f));
		shape.setPoint(4, sf::Vector2f(0.7f, 0.2f));
		mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::CheckDir, Enums::eDir::Up), mBoard, sf::Vector2f(0.3f, 0.5f), shape));
		shape.setPointCount(5);
		shape.setPoint(0, sf::Vector2f(0.5f, 1.0f));
		shape.setPoint(1, sf::Vector2f(0.3f, 0.8f));
		shape.setPoint(2, sf::Vector2f(0.3f, 0.7f));
		shape.setPoint(3, sf::Vector2f(0.7f, 0.7f));
		shape.setPoint(4, sf::Vector2f(0.7f, 0.8f));
		mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::CheckDir, Enums::eDir::Down), mBoard, sf::Vector2f(0.3f, 0.5f), shape));
		shape.setPointCount(4);
		shape.setPoint(0, sf::Vector2f(0.3f, 0.3f));
		shape.setPoint(1, sf::Vector2f(0.7f, 0.3f));
		shape.setPoint(2, sf::Vector2f(0.7f, 0.7f));
		shape.setPoint(3, sf::Vector2f(0.3f, 0.7f));
		mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::CheckDir, Enums::eDir::Center), mBoard, sf::Vector2f(0.3f, 0.5f), shape));
		break;
	}
	case Enums::eInstructionModifier::CloudDir: //Pos 3/5 (offset : 0.5f)
	{
		shape.setPointCount(5);
		shape.setPoint(0, sf::Vector2f(0.0f, 0.2f));
		shape.setPoint(1, sf::Vector2f(0.2f, 0.2f));
		shape.setPoint(2, sf::Vector2f(0.5f, 0.5f));
		shape.setPoint(3, sf::Vector2f(0.2f, 0.8f));
		shape.setPoint(4, sf::Vector2f(0.0f, 0.8f));
		mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::CloudDir, Enums::eDir::Left), mBoard, sf::Vector2f(0.5f, 0.5f), shape));
		shape.setPointCount(5);
		shape.setPoint(0, sf::Vector2f(1.0f, 0.2f));
		shape.setPoint(1, sf::Vector2f(0.8f, 0.2f));
		shape.setPoint(2, sf::Vector2f(0.5f, 0.5f));
		shape.setPoint(3, sf::Vector2f(0.8f, 0.8f));
		shape.setPoint(4, sf::Vector2f(1.0f, 0.8f));
		mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::CloudDir, Enums::eDir::Right), mBoard, sf::Vector2f(0.5f, 0.5f), shape));
		shape.setPointCount(5);
		shape.setPoint(0, sf::Vector2f(0.2f, 0.0f));
		shape.setPoint(1, sf::Vector2f(0.2f, 0.2f));
		shape.setPoint(2, sf::Vector2f(0.5f, 0.5f));
		shape.setPoint(3, sf::Vector2f(0.8f, 0.2f));
		shape.setPoint(4, sf::Vector2f(0.8f, 0.0f));
		mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::CloudDir, Enums::eDir::Up), mBoard, sf::Vector2f(0.5f, 0.5f), shape));
		shape.setPointCount(5);
		shape.setPoint(0, sf::Vector2f(0.2f, 1.0f));
		shape.setPoint(1, sf::Vector2f(0.2f, 0.8f));
		shape.setPoint(2, sf::Vector2f(0.5f, 0.5f));
		shape.setPoint(3, sf::Vector2f(0.8f, 0.8f));
		shape.setPoint(4, sf::Vector2f(0.8f, 1.0f));
		mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::CloudDir, Enums::eDir::Down), mBoard, sf::Vector2f(0.5f, 0.5f), shape));
		break;
	}
	case Enums::eInstructionModifier::RobotColor: //Pos 1/5 (offset : 0.1f), TODO only created if more than one robot ?
	{
		if (mBoard.getStartPosition(Enums::eColor::Blue) != std::pair<unsigned int, unsigned int>(-1, -1) || mBoard.getStartPosition(Enums::eColor::Green) != std::pair<unsigned int, unsigned int>(-1, -1) || mBoard.getStartPosition(Enums::eColor::Yellow) != std::pair<unsigned int, unsigned int>(-1, -1)) //TODO Can do a better check ?
		{
			if (mBoard.getStartPosition(Enums::eColor::Red) != std::pair<unsigned int, unsigned int>(-1, -1))
			{
				shape.setPointCount(5);
				shape.setPoint(0, sf::Vector2f(0.0f, 0.0f));
				shape.setPoint(1, sf::Vector2f(0.5f, 0.0f));
				shape.setPoint(2, sf::Vector2f(0.5f, 0.2f));
				shape.setPoint(3, sf::Vector2f(0.2f, 0.5f));
				shape.setPoint(4, sf::Vector2f(0.0f, 0.5f));
				mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::RobotColor, Enums::eColor::Red), mBoard, sf::Vector2f(0.1f, 0.5f), shape));
			}
			if (mBoard.getStartPosition(Enums::eColor::Blue) != std::pair<unsigned int, unsigned int>(-1, -1))
			{
				shape.setPointCount(5);
				shape.setPoint(0, sf::Vector2f(1.0f, 0.0f));
				shape.setPoint(1, sf::Vector2f(0.5f, 0.0f));
				shape.setPoint(2, sf::Vector2f(0.5f, 0.2f));
				shape.setPoint(3, sf::Vector2f(0.8f, 0.5f));
				shape.setPoint(4, sf::Vector2f(1.0f, 0.5f));
				mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::RobotColor, Enums::eColor::Blue), mBoard, sf::Vector2f(0.1f, 0.5f), shape));
			}
			if (mBoard.getStartPosition(Enums::eColor::Green) != std::pair<unsigned int, unsigned int>(-1, -1))
			{
				shape.setPointCount(5);
				shape.setPoint(0, sf::Vector2f(0.0f, 1.0f));
				shape.setPoint(1, sf::Vector2f(0.5f, 1.0f));
				shape.setPoint(2, sf::Vector2f(0.5f, 0.8f));
				shape.setPoint(3, sf::Vector2f(0.2f, 0.5f));
				shape.setPoint(4, sf::Vector2f(0.0f, 0.5f));
				mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::RobotColor, Enums::eColor::Green), mBoard, sf::Vector2f(0.1f, 0.5f), shape));
			}
			if (mBoard.getStartPosition(Enums::eColor::Yellow) != std::pair<unsigned int, unsigned int>(-1, -1))
			{
				shape.setPointCount(5);
				shape.setPoint(0, sf::Vector2f(1.0f, 1.0f));
				shape.setPoint(1, sf::Vector2f(0.5f, 1.0f));
				shape.setPoint(2, sf::Vector2f(0.5f, 0.8f));
				shape.setPoint(3, sf::Vector2f(0.8f, 0.5f));
				shape.setPoint(4, sf::Vector2f(1.0f, 0.5f));
				mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::RobotColor, Enums::eColor::Yellow), mBoard, sf::Vector2f(0.1f, 0.5f), shape));
			}
			shape.setPointCount(4);
			shape.setPoint(0, sf::Vector2f(0.5f, 0.2f));
			shape.setPoint(1, sf::Vector2f(0.2f, 0.5f));
			shape.setPoint(2, sf::Vector2f(0.5f, 0.8f));
			shape.setPoint(3, sf::Vector2f(0.8f, 0.5f));
			mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::RobotColor, Enums::eColor::NoColor), mBoard, sf::Vector2f(0.1f, 0.5f), shape));
		}
		break;
	}
	case Enums::eInstructionModifier::CloudColor: //Pos 3/5 (offset : 0.5f)
	{
		shape.setPointCount(5);
		shape.setPoint(0, sf::Vector2f(0.0f, 0.0f));
		shape.setPoint(1, sf::Vector2f(0.5f, 0.0f));
		shape.setPoint(2, sf::Vector2f(0.5f, 0.2f));
		shape.setPoint(3, sf::Vector2f(0.2f, 0.5f));
		shape.setPoint(4, sf::Vector2f(0.0f, 0.5f));
		mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::CloudColor, Enums::eColor::Red), mBoard, sf::Vector2f(0.5f, 0.5f), shape));
		shape.setPointCount(5);
		shape.setPoint(0, sf::Vector2f(1.0f, 0.0f));
		shape.setPoint(1, sf::Vector2f(0.5f, 0.0f));
		shape.setPoint(2, sf::Vector2f(0.5f, 0.2f));
		shape.setPoint(3, sf::Vector2f(0.8f, 0.5f));
		shape.setPoint(4, sf::Vector2f(1.0f, 0.5f));
		mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::CloudColor, Enums::eColor::Blue), mBoard, sf::Vector2f(0.5f, 0.5f), shape));
		shape.setPointCount(5);
		shape.setPoint(0, sf::Vector2f(0.0f, 1.0f));
		shape.setPoint(1, sf::Vector2f(0.5f, 1.0f));
		shape.setPoint(2, sf::Vector2f(0.5f, 0.8f));
		shape.setPoint(3, sf::Vector2f(0.2f, 0.5f));
		shape.setPoint(4, sf::Vector2f(0.0f, 0.5f));
		mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::CloudColor, Enums::eColor::Green), mBoard, sf::Vector2f(0.5f, 0.5f), shape));
		shape.setPointCount(5);
		shape.setPoint(0, sf::Vector2f(1.0f, 1.0f));
		shape.setPoint(1, sf::Vector2f(0.5f, 1.0f));
		shape.setPoint(2, sf::Vector2f(0.5f, 0.8f));
		shape.setPoint(3, sf::Vector2f(0.8f, 0.5f));
		shape.setPoint(4, sf::Vector2f(1.0f, 0.5f));
		mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::CloudColor, Enums::eColor::Yellow), mBoard, sf::Vector2f(0.5f, 0.5f), shape));
		shape.setPointCount(4);
		shape.setPoint(0, sf::Vector2f(0.5f, 0.2f));
		shape.setPoint(1, sf::Vector2f(0.2f, 0.5f));
		shape.setPoint(2, sf::Vector2f(0.5f, 0.8f));
		shape.setPoint(3, sf::Vector2f(0.8f, 0.5f));
		mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::CloudColor, Enums::eColor::NoColor), mBoard, sf::Vector2f(0.5f, 0.5f), shape));
		break;
	}
	case Enums::eInstructionModifier::CloudBool: //Pos 3/5 (offset : 0.5f)
	{
		shape.setPointCount(6);
		shape.setPoint(0, sf::Vector2f(0.2f, 0.0f));
		shape.setPoint(1, sf::Vector2f(0.0f, 0.2f));
		shape.setPoint(2, sf::Vector2f(0.0f, 0.5f));
		shape.setPoint(3, sf::Vector2f(1.0f, 0.5f));
		shape.setPoint(4, sf::Vector2f(1.0f, 0.2f));
		shape.setPoint(5, sf::Vector2f(0.8f, 0.0f));
		mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::CloudBool, true), mBoard, sf::Vector2f(0.5f, 0.5f), shape));
		shape.setPointCount(6);
		shape.setPoint(0, sf::Vector2f(0.2f, 1.0f));
		shape.setPoint(1, sf::Vector2f(0.0f, 0.8f));
		shape.setPoint(2, sf::Vector2f(0.0f, 0.5f));
		shape.setPoint(3, sf::Vector2f(1.0f, 0.5f));
		shape.setPoint(4, sf::Vector2f(1.0f, 0.8f));
		shape.setPoint(5, sf::Vector2f(0.8f, 1.0f));
		mModifiers.push_back(GUIInstructionModifier(InstructionModificationData(Enums::eInstructionModifier::CloudBool, false), mBoard, sf::Vector2f(0.5f, 0.5f), shape));
		break;
	}
	default:break;
	}
}
