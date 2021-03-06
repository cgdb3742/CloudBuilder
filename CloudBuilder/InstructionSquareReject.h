#pragma once
#include "InstructionSquare.h"
class InstructionSquareReject :
	public InstructionSquare
{
public:
	InstructionSquareReject(GameContext& gameContext);
	InstructionSquareReject(GameContext& gameContext, std::wstring& source);
	~InstructionSquareReject();

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::wstring convertToString();
	virtual bool convertFromString(std::wstring& source);

	virtual bool applyInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress);

	virtual void drawInterior(sf::RenderTarget & target);
};

