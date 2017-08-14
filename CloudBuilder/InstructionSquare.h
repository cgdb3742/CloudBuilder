#pragma once

#include <list>
#include <string>
#include "GameEntity.h"
#include "StringConvertible.h"
#include "Enums.h"
#include "GUIInstructionModifier.h"

class CloudRobot;
class CloudCanvas;
class InstructionRobot;

class InstructionSquare :
	public GameEntity,
	public StringConvertible
{
public:
	typedef std::unique_ptr<InstructionSquare> InstructionSquarePtr;

	static InstructionSquarePtr createNewInstructionSquare(GameContext& gameContext, Enums::eInstruction type);
	static InstructionSquarePtr createNewInstructionSquare(GameContext& gameContext, Enums::eInstruction type, Enums::eColor color); //used for starter
	static InstructionSquarePtr createNewInstructionSquare(GameContext& gameContext, std::string source);
	//static InstructionSquare createNewInstructionSquareRaw(Enums::eInstruction type);
	//static InstructionSquare createNewInstructionSquareRaw(Enums::eInstruction type, Enums::eColor color);

	InstructionSquare(GameContext& gameContext);
	InstructionSquare(GameContext& gameContext, std::string& source);
	~InstructionSquare();

	bool IsAssigned();
	bool IsSpecial();
	bool IsAction();
	bool IsCheck();
	bool IsFlow();
	bool IsWriteOnly();
	bool IsDraggable();
	bool IsErasable();
	Enums::eInstruction getType();
	virtual Enums::eDir getNextDir();
	virtual Enums::eDir getNextDir(InstructionRobot& robot);
	virtual void setNextDir(Enums::eDir newDir);

	virtual std::list<Enums::eInstructionModifier> getPossibleModifications();
	virtual void applyModification(InstructionModificationData modificationData);

	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);

	virtual bool applyInstruction(CloudRobot& cloudRobot, CloudCanvas& canvas, InstructionRobot& instructionRobot, float progress);
	//virtual bool isValid();

	virtual Enums::eColor getStartColor();
	virtual void setStartColor(Enums::eColor newColor);

	virtual void setUpNextDir(bool isLeftBorder, bool isRightBorder, bool isUpBorder, bool isDownBorder);

	virtual void drawCurrent(sf::RenderTarget & target);
protected:
	InstructionSquare(GameContext& gameContext, Enums::eInstruction type, std::string name);

	virtual void drawNextDir(sf::RenderTarget & target);
	virtual void drawInterior(sf::RenderTarget & target);
//private:
	Enums::eInstruction mType;
	Enums::eDir mNext;
	std::string mName;
};

