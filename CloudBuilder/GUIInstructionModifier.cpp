#include "GUIInstructionModifier.h"
#include "InstructionBoard.h"


GUIInstructionModifier::GUIInstructionModifier(GameContext& gameContext, InstructionModificationData modificationReport, InstructionBoard & board, sf::Vector2f positionRatio, sf::ConvexShape basicShape):
	GUIButton(gameContext, positionRatio),
	mModificationReport(modificationReport),
	//mPositionRatio(positionRatio),
	mBoard(board),
	mBasicShape(basicShape),
	mShape(basicShape)
{
}


GUIInstructionModifier::~GUIInstructionModifier()
{
}

InstructionModificationData GUIInstructionModifier::getModification()
{
	return mModificationReport;
}

void GUIInstructionModifier::applyModification()
{
	applyModification(mBoard.getSelection());
}

void GUIInstructionModifier::applyModification(InstructionSquare & instruction)
{
	instruction.applyModification(mModificationReport);
	mBoard.updateBordFlow();
}

void GUIInstructionModifier::clicked()
{
	applyModification();
}

//void GUIInstructionModifier::setSquareSize(sf::Vector2f newSize)
//{
//	mBoundingBox = newSize;
//}

void GUIInstructionModifier::setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	//mBoundingBox = maxBox;

	//mBoudingBox set in setSquareSize before
	//mTopLeftCorner.x = minCorner.x + mPositionRatio.x * maxBox.x - mBoundingBox.x / 2.0f;
	//mTopLeftCorner.y = minCorner.y + mPositionRatio.y * maxBox.y - mBoundingBox.y / 2.0f;

	GUIButton::setPositionCurrent(minCorner, maxBox);

	mShape = mBasicShape;
	for (unsigned int i = 0; i < mShape.getPointCount(); i++)
	{
		sf::Vector2f p = mShape.getPoint(i);
		p.x *= mBoundingBox.x;
		p.y *= mBoundingBox.y;
		p += mTopLeftCorner;
		mShape.setPoint(i, p);
	}
}

//void GUIInstructionModifier::handleEventCurrent(const sf::Event & event)
//{
//	switch (event.type)
//	{
//	case sf::Event::MouseButtonReleased:
//		if (event.mouseButton.button == sf::Mouse::Button::Left && containsPoint(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
//		{
//			clicked();
//		}
//		break;
//	}
//}

void GUIInstructionModifier::drawCurrent(sf::RenderTarget & target)
{
	//sf::RectangleShape background(mBoundingBox);
	//background.setPosition(mTopLeftCorner);
	//background.setFillColor(sf::Color(255, 255, 255, 0));
	//background.setOutlineThickness(1.0f);
	//background.setOutlineColor(sf::Color(255, 255, 255));
	//target.draw(background);

	sf::ConvexShape toDraw(mShape);
	toDraw.setFillColor(sf::Color(191, 191, 0));
	toDraw.setOutlineThickness(1.0f);
	toDraw.setOutlineColor(sf::Color(255, 255, 0));
	target.draw(toDraw);
}

//Based on https://stackoverflow.com/questions/1119627/how-to-test-if-a-point-is-inside-of-a-convex-polygon-in-2d-integer-coordinates
bool GUIInstructionModifier::containsPoint(sf::Vector2f point)
{
	//Rapid check for obvious cases
	if (point.x <= mTopLeftCorner.x || point.x >= mTopLeftCorner.x + mBoundingBox.x || point.y <= mTopLeftCorner.y || point.y >= mTopLeftCorner.y + mBoundingBox.y)
	{
		return false;
	}

	int previous_side = 0;
	unsigned int n = mShape.getPointCount();

	for (unsigned int i = 0; i < n; i++)
	{
		sf::Vector2f p1 = mShape.getPoint(i);
		sf::Vector2f p2 = mShape.getPoint((i + 1) % n);
		sf::Vector2f aff_seg = p2 - p1;
		sf::Vector2f aff_point = point - p1;
		float cross_product = (aff_seg.x * aff_point.y) - (aff_seg.y * aff_point.x);
		int current_side = 0;
		if (cross_product < 0)
		{
			current_side = -1;
		}
		else if (cross_product > 0)
		{
			current_side = 1;
		}

		if (current_side == 0)
		{
			return false;
		}
		else if (previous_side == 0)
		{
			previous_side = current_side;
		}
		else if (current_side != previous_side)
		{
			return false;
		}
	}

	return true;
}
