#pragma once
#include "InstructionSquare.h"
class InstructionSquareFlowResume :
	public InstructionSquare
{
public:
	InstructionSquareFlowResume(GameContext& gameContext);
	InstructionSquareFlowResume(GameContext& gameContext, std::wstring source);
	~InstructionSquareFlowResume();

	virtual bool isValid();

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::wstring convertToString();
	virtual bool convertFromString(std::wstring& source);
protected:
	virtual void drawInterior(sf::RenderTarget & target);
};

