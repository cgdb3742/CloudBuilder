#pragma once

#include <vector>
#include <map>
#include <utility>
#include "GameEntity.h"
#include "StringConvertible.h"
#include "InstructionSquare.h"
#include "InstructionDraggableHandler.h"
#include "BuildLockable.h"

class InstructionBoard :
	public GameEntity,
	public InstructionDraggableHandler,
	public BuildLockable,
	public StringConvertible
{
public:
	InstructionBoard(GameContext& gameContext);
	InstructionBoard(GameContext& gameContext, std::string source);
	InstructionBoard(GameContext& gameContext, unsigned int width, unsigned int height);
	~InstructionBoard();

	//InstructionBoard(const InstructionBoard& toCopy);
	InstructionBoard(const InstructionBoard&) = delete;

	virtual std::string convertToString();
	virtual bool convertFromString(std::string& source);

	bool exists(unsigned int i, unsigned int j);
	InstructionSquare& get(unsigned int i, unsigned int j);
	bool canMove(unsigned int i, unsigned int j, Enums::eDir dir);

	sf::Vector2f getSquareSize();

	virtual InstructionSquare::InstructionSquarePtr giveToDrag(sf::Vector2f mousePos);
	virtual bool canGetFromDrag(sf::Vector2f mousePos);
	virtual InstructionSquare::InstructionSquarePtr getFromDrag(sf::Vector2f mousePos, InstructionSquare::InstructionSquarePtr ptr);

	virtual void drawCurrent(sf::RenderTarget & target);
	virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
	virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);

	void handleEventCurrent(const sf::Event & event);

	bool hasUpdatedStartPoints();
	void setStartPosition(Enums::eColor color, unsigned int i, unsigned int j);
	std::pair<unsigned int, unsigned int> getStartPosition(Enums::eColor color);

	bool hasUpdatedSelection();
	void setSelection(unsigned int i, unsigned int j);
	InstructionSquare& getSelection();
	unsigned int getSelectionI();
	unsigned int getSelectionJ();
protected:
	virtual void updateChildsVector();
private:
	InstructionSquare::InstructionSquarePtr giveToDrag(unsigned int i, unsigned int j);
	InstructionSquare::InstructionSquarePtr getFromDrag(unsigned int i, unsigned int j, InstructionSquare::InstructionSquarePtr ptr);
	InstructionSquare::InstructionSquarePtr insert(unsigned int i, unsigned int j, InstructionSquare::InstructionSquarePtr ptr);

	unsigned int mWidth;
	unsigned int mHeight;
	//std::vector<std::vector<InstructionSquare::InstructionSquarePtr>> mBoard;
	std::vector<InstructionSquare::InstructionSquarePtr> mBoard;
	std::map<Enums::eColor, std::pair<unsigned int, unsigned int>> mStartPoints;
	bool mStartPointsUpdated;
	std::pair<unsigned int, unsigned int> mSelected;
	bool mSelectionUpdated;
};

