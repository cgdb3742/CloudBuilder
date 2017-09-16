#pragma once
#include "InstructionSquare.h"

class InstructionRobot;

class InstructionSquareStart :
	public InstructionSquare
{
public:
	InstructionSquareStart(GameContext& gameContext);
	InstructionSquareStart(GameContext& gameContext, std::wstring& source);
	InstructionSquareStart(GameContext& gameContext, Enums::eColor color);
	//InstructionSquareStart(Enums::eColor color, InstructionRobot& robot);
	~InstructionSquareStart();

	virtual bool isValid();

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::wstring convertToString();
	virtual bool convertFromString(std::wstring& source);

	virtual Enums::eColor getStartColor();
	virtual void setStartColor(Enums::eColor newColor);
protected:
	virtual void drawInterior(sf::RenderTarget & target);
private:
	Enums::eColor mColor;
	//InstructionRobot& mRobot;
};

