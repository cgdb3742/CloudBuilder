#pragma once
#include "InstructionSquare.h"
class InstructionSquareFlowSync :
	public InstructionSquare
{
public:
	InstructionSquareFlowSync(GameContext& gameContext);
	InstructionSquareFlowSync(GameContext& gameContext, std::wstring source);
	~InstructionSquareFlowSync();

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::wstring convertToString();
	virtual bool convertFromString(std::wstring& source);
protected:
	virtual void drawInterior(sf::RenderTarget & target);
};

