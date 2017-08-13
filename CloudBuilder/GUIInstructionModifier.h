#pragma once
#include "GUIButton.h"
#include "Enums.h"

class InstructionBoard;
class InstructionSquare;

struct InstructionModificationData
{
	InstructionModificationData() : modification(Enums::eInstructionModifier::Unknown), dirData(Enums::eDir::Center), colorData(Enums::eColor::NoColor), boolData(false) {}
	InstructionModificationData(Enums::eInstructionModifier modifier, Enums::eDir value) : modification(modifier), dirData(value), colorData(Enums::eColor::NoColor), boolData(false) {}
	InstructionModificationData(Enums::eInstructionModifier modifier, Enums::eColor value) : modification(modifier), dirData(Enums::eDir::Center), colorData(value), boolData(false) {}
	InstructionModificationData(Enums::eInstructionModifier modifier, bool value) : modification(modifier), dirData(Enums::eDir::Center), colorData(Enums::eColor::NoColor), boolData(value) {}

	Enums::eInstructionModifier modification;
	Enums::eDir dirData;
	Enums::eColor colorData;
	bool boolData;
};

class GUIInstructionModifier :
	public GUIButton
{
public:
	GUIInstructionModifier(InstructionModificationData modificationReport, InstructionBoard& board, sf::Vector2f positionRatio, sf::ConvexShape basicShape);
	~GUIInstructionModifier();

	InstructionModificationData getModification();
	void applyModification();
	void applyModification(InstructionSquare& instruction);

	virtual void clicked();

	//virtual void setSquareSize(sf::Vector2f newSize);
	virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);
	//virtual void handleEventCurrent(const sf::Event& event);
	virtual void drawCurrent(sf::RenderTarget& target);
protected:
	virtual bool containsPoint(sf::Vector2f point);
private:
	InstructionModificationData mModificationReport;

	//sf::Vector2f mPositionRatio;
	sf::ConvexShape mBasicShape;
	sf::ConvexShape mShape;

	InstructionBoard& mBoard;
};

