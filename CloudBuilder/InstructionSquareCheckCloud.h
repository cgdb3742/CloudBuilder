#pragma once
#include "InstructionSquareCheck.h"
class InstructionSquareCheckCloud :
	public InstructionSquareCheck
{
public:
	InstructionSquareCheckCloud(GameContext& gameContext);
	InstructionSquareCheckCloud(GameContext& gameContext, std::wstring& source);
	~InstructionSquareCheckCloud();

	virtual bool getWantCloud();
	virtual void setWantCloud(bool newWant);

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::wstring convertToString();
	virtual bool convertFromString(std::wstring& source);

	virtual bool performCheck(CloudRobot& cloudRobot, CloudCanvas& canvas, InstructionRobot& instructionRobot, unsigned int toChecki, unsigned int toCheckj);
protected:
	virtual void drawInterior(sf::RenderTarget & target);
private:
	bool mWantCloud;
};

