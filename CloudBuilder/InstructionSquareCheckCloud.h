#pragma once
#include "InstructionSquareCheck.h"
class InstructionSquareCheckCloud :
	public InstructionSquareCheck
{
public:
	InstructionSquareCheckCloud(GameContext& gameContext);
	InstructionSquareCheckCloud(GameContext& gameContext, std::string& source);
	~InstructionSquareCheckCloud();

	virtual bool getWantCloud();
	virtual void setWantCloud(bool newWant);

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);

	virtual bool performCheck(CloudRobot& cloudRobot, CloudCanvas& canvas, InstructionRobot& instructionRobot, unsigned int toChecki, unsigned int toCheckj);
protected:
	virtual void drawInterior(sf::RenderTarget & target);
private:
	bool mWantCloud;
};

