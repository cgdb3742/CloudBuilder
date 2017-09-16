#pragma once
#include "InstructionSquare.h"
class InstructionSquareFlowPause :
	public InstructionSquare
{
public:
	InstructionSquareFlowPause(GameContext& gameContext);
	InstructionSquareFlowPause(GameContext& gameContext, std::wstring source);
	~InstructionSquareFlowPause();

	virtual bool isValid();

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::wstring convertToString();
	virtual bool convertFromString(std::wstring& source);
protected:
	virtual void drawInterior(sf::RenderTarget & target);
};

