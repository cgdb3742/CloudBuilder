#pragma once

#include <vector>
#include <memory>
#include <SFML\Graphics.hpp>

struct GameContext;

class GameEntity
{
public:
	//typedef std::weak_ptr<GameEntity> GameEntityPtr;
	typedef std::reference_wrapper<GameEntity> GameEntityRef;
	//typedef std::unique_ptr<GameEntity> GameEntityPtr;

	GameEntity(GameContext& gameContext);
	~GameEntity();

	//TODO Propagate a function when language is changed ?

	virtual void handleEventAll(const sf::Event& event);
	virtual void handleEventChilds(const sf::Event& event);
	virtual void handleEventCurrent(const sf::Event& event);
	//virtual void handleEvent(const sf::Event& event);
	virtual void updateAll(sf::Time dt);
	virtual void updateChilds(sf::Time dt);
	virtual void updateCurrent(sf::Time dt);
	//virtual void update(sf::Time dt);
	virtual void drawAll(sf::RenderTarget& target);
	virtual void drawChilds(sf::RenderTarget& target);
	virtual void drawCurrent(sf::RenderTarget& target);
	//virtual void draw(sf::RenderTarget& target);

	virtual void setPositionAll(sf::Vector2f minCorner, sf::Vector2f maxBox);
	virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
	virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);
	virtual sf::Vector2f computeChildsBoundingBox();
	virtual void setBoundingBoxCurrent(sf::Vector2f boundingBox); //Empty : only used for components like GUIButton
	//virtual void setPosition(sf::Vector2f minCorner, sf::Vector2f maxBox);
	virtual sf::Vector2f getTopLeftCorner();
	virtual sf::Vector2f getBoundingBox();

	virtual void updateChildsVectorAll();


protected:
	virtual std::vector<GameEntityRef> getChilds();
	virtual void updateChildsVector();

	sf::Vector2f mTopLeftCorner;
	sf::Vector2f mBoundingBox;
	std::vector<GameEntityRef> mChilds;

	GameContext& mGameContext;
};

