#include "GUIInstructionTrashBin.h"






GUIInstructionTrashBin::GUIInstructionTrashBin(GameContext & gameContext, sf::Vector2f positionRatio) :
	GUIButton(gameContext, positionRatio)
{
}

GUIInstructionTrashBin::GUIInstructionTrashBin(GameContext & gameContext) :
	GUIButton(gameContext, sf::Vector2f(0.0f, 0.0f))
{
}

GUIInstructionTrashBin::~GUIInstructionTrashBin()
{
}

bool GUIInstructionTrashBin::canGetFromDrag(sf::Vector2f mousePos)
{
	sf::Vector2f relativeMousePos = mousePos - mTopLeftCorner;

	return (relativeMousePos.x > 0 && relativeMousePos.x < mBoundingBox.x && relativeMousePos.y > 0 && relativeMousePos.y < mBoundingBox.y);
}

InstructionSquare::InstructionSquarePtr GUIInstructionTrashBin::getFromDrag(sf::Vector2f mousePos, InstructionSquare::InstructionSquarePtr ptr)
{
	if (!canGetFromDrag(mousePos) || !(ptr->IsErasable()))
	{
		return ptr;
	}
	else
	{
		return nullptr;
	}
}

void GUIInstructionTrashBin::drawCurrent(sf::RenderTarget & target)
{
	sf::RectangleShape background(mBoundingBox);
	background.setPosition(mTopLeftCorner);
	background.setFillColor(sf::Color(255, 0, 255));
	target.draw(background);

	sf::RectangleShape square(mBoundingBox * 3.0f / 4.0f);
	square.setPosition(mTopLeftCorner + mBoundingBox / 8.0f);
	square.setFillColor(sf::Color(63, 63, 63));
	square.setOutlineThickness(1.0f);
	square.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(square);

	sf::CircleShape handle(mBoundingBox.x / 8.0f);
	handle.setPosition(mTopLeftCorner + sf::Vector2f(mBoundingBox.x * 3.0f / 8.0f, mBoundingBox.y * 5.0f / 32.0f));
	handle.setFillColor(sf::Color(191, 191, 191));
	handle.setOutlineThickness(1.0f);
	handle.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(handle);

	sf::RectangleShape binTop(sf::Vector2f(mBoundingBox.x * 5.0f / 8.0f, mBoundingBox.y / 16.0f));
	binTop.setPosition(mTopLeftCorner + sf::Vector2f(mBoundingBox.x * 3.0f / 16.0f, mBoundingBox.y / 4.0f));
	binTop.setFillColor(sf::Color(191, 191, 191));
	binTop.setOutlineThickness(1.0f);
	binTop.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(binTop);

	sf::RectangleShape binBottom(sf::Vector2f(mBoundingBox.x / 2.0f, mBoundingBox.y / 2.0f));
	binBottom.setPosition(mTopLeftCorner + sf::Vector2f(mBoundingBox.x / 4.0f, mBoundingBox.y * 5.0f / 16.0f));
	binBottom.setFillColor(sf::Color(191, 191, 191));
	binBottom.setOutlineThickness(1.0f);
	binBottom.setOutlineColor(sf::Color(0, 0, 0));
	target.draw(binBottom);
}
