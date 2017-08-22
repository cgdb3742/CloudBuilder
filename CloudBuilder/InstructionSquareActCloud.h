#pragma once
#include "InstructionSquare.h"
class InstructionSquareActCloud :
	public InstructionSquare
{
public:
	InstructionSquareActCloud(GameContext& gameContext);
	InstructionSquareActCloud(GameContext& gameContext, std::string& source);
	~InstructionSquareActCloud();

	bool getWantCloud();
	void setWantCloud(bool newWant);
	Enums::eColor getRobotColor();
	void setRobotColor(Enums::eColor newColor);

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);

	virtual bool applyInstruction(CloudRobot& cloudRobot, CloudCanvas& canvas, InstructionRobot& instructionRobot, float progress);

	virtual void drawInterior(sf::RenderTarget & target);
private:
	bool mWantCloud;
	Enums::eColor mRobotColor;
};

