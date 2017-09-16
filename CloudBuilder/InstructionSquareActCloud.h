#pragma once
#include "InstructionSquare.h"
class InstructionSquareActCloud :
	public InstructionSquare
{
public:
	InstructionSquareActCloud(GameContext& gameContext);
	InstructionSquareActCloud(GameContext& gameContext, std::wstring& source);
	~InstructionSquareActCloud();

	virtual bool isValid();

	bool getWantCloud();
	void setWantCloud(bool newWant);

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::wstring convertToString();
	virtual bool convertFromString(std::wstring& source);

	virtual bool applyInstruction(CloudRobot& cloudRobot, CloudCanvas& canvas, InstructionRobot& instructionRobot, float progress);

	virtual void animateInstruction(CloudRobot& cloudRobot, CloudCanvas& canvas, InstructionRobot& instructionRobot, float progress, float lastProgress);

	virtual void drawInterior(sf::RenderTarget & target);
private:
	bool mWantCloud;
};

