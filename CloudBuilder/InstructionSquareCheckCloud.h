#pragma once
#include "InstructionSquare.h"
class InstructionSquareCheckCloud :
	public InstructionSquare
{
public:
	InstructionSquareCheckCloud();
	explicit InstructionSquareCheckCloud(std::string& source);
	~InstructionSquareCheckCloud();

	virtual Enums::eDir getNextDir(InstructionRobot& robot);
	virtual Enums::eDir getNextTrueDir();
	virtual void setNextTrueDir(Enums::eDir newDir);
	virtual Enums::eDir getNextFalseDir();
	virtual void setNextFalseDir(Enums::eDir newDir);

	virtual Enums::eDir getCheckDir();
	virtual void setCheckDir(Enums::eDir newDir);
	virtual Enums::eColor getRobotColor();
	virtual void setRobotColor(Enums::eColor newColor);
	virtual bool getWantCloud();
	virtual void setWantCloud(bool newWant);

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);

	virtual bool applyInstruction(CloudRobot& cloudRobot, CloudCanvas& canvas, InstructionRobot& instructionRobot, float progress);

	virtual void setUpNextDir(bool isLeftBorder, bool isRightBorder, bool isUpBorder, bool isDownBorder);
protected:
	virtual void drawNextDir(sf::RenderTarget & target);
	virtual void drawInterior(sf::RenderTarget & target);
private:
	Enums::eDir mNextTrue;
	Enums::eDir mNextFalse;
	Enums::eDir mCheckDir;
	Enums::eColor mRobotColor;
	bool mWantCloud;
};

