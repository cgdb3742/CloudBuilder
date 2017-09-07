#pragma once
#include "InstructionSquare.h"
class InstructionSquareFlowResume :
	public InstructionSquare
{
public:
	InstructionSquareFlowResume(GameContext& gameContext);
	InstructionSquareFlowResume(GameContext& gameContext, std::string source);
	~InstructionSquareFlowResume();

	virtual bool isValid();

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);
protected:
	virtual void drawInterior(sf::RenderTarget & target);
};

