#pragma once
#include "InstructionSquare.h"
class InstructionSquareAccept :
	public InstructionSquare
{
public:
	InstructionSquareAccept();
	explicit InstructionSquareAccept(std::string& source);
	~InstructionSquareAccept();

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);

	virtual bool applyInstruction(CloudRobot & cloudRobot, CloudCanvas & canvas, InstructionRobot & instructionRobot, float progress);

	virtual void drawInterior(sf::RenderTarget & target);
};

