#pragma once
#include <list>
#include "GameEntity.h"
#include "GUIInstructionModifier.h"

class InstructionBoard;
class InstructionSquare;

class GUIInstructionModifierContainer :
	public GameEntity
{
public:
	GUIInstructionModifierContainer(GameContext& gameContext, InstructionBoard& board);
	~GUIInstructionModifierContainer();

	void setUpModifiers();

	//void updateCurrent(sf::Time dt);

	void drawCurrent(sf::RenderTarget & target);

	virtual sf::Vector2f computeChildsBoundingBox();
	virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
protected:
	virtual void updateChildsVector();
private:
	void createAllModifiers(unsigned int i, unsigned int j, InstructionSquare& instruction);
	void createModifiers(unsigned int i, unsigned int j, Enums::eInstructionModifier modifier);

	std::list<GUIInstructionModifier> mModifiers;
	InstructionBoard& mBoard;
};

