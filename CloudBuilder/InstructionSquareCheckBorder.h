#pragma once
#include "InstructionSquareCheck.h"
class InstructionSquareCheckBorder :
	public InstructionSquareCheck
{
public:
	InstructionSquareCheckBorder(GameContext& gameContext);
	InstructionSquareCheckBorder(GameContext& gameContext, std::wstring& source);
	~InstructionSquareCheckBorder();

	virtual Enums::eDir getBorder();
	virtual void setBorder(Enums::eDir newBorder);

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::wstring convertToString();
	virtual bool convertFromString(std::wstring& source);

	virtual bool performCheck(CloudRobot& cloudRobot, CloudCanvas& canvas, InstructionRobot& instructionRobot, unsigned int toChecki, unsigned int toCheckj);
protected:
	virtual void drawInterior(sf::RenderTarget & target);
private:
	Enums::eDir mBorder;
};

