#pragma once
#include "InstructionSquare.h"
class InstructionSquareReject :
	public InstructionSquare
{
public:
	InstructionSquareReject();
	explicit InstructionSquareReject(std::string& source);
	~InstructionSquareReject();

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);

	virtual bool applyInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress);

	virtual void drawInterior(sf::RenderTarget & target);
};

