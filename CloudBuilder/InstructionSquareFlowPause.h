#pragma once
#include "InstructionSquare.h"
class InstructionSquareFlowPause :
	public InstructionSquare
{
public:
	InstructionSquareFlowPause(GameContext& gameContext);
	InstructionSquareFlowPause(GameContext& gameContext, std::string source);
	~InstructionSquareFlowPause();

	virtual bool isValid();

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);
protected:
	virtual void drawInterior(sf::RenderTarget & target);
};

