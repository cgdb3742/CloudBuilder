#pragma once
#include "InstructionSquare.h"
class InstructionSquareFlowSync :
	public InstructionSquare
{
public:
	InstructionSquareFlowSync(GameContext& gameContext);
	InstructionSquareFlowSync(GameContext& gameContext, std::string source);
	~InstructionSquareFlowSync();

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);
protected:
	virtual void drawInterior(sf::RenderTarget & target);
};

