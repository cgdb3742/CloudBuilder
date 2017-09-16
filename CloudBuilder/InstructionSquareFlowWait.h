#pragma once
#include "InstructionSquare.h"
class InstructionSquareFlowWait :
	public InstructionSquare
{
public:
	InstructionSquareFlowWait(GameContext& gameContext);
	InstructionSquareFlowWait(GameContext& gameContext, std::wstring source);
	~InstructionSquareFlowWait();

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::wstring convertToString();
	virtual bool convertFromString(std::wstring& source);
protected:
	virtual void drawInterior(sf::RenderTarget & target);
};

