#pragma once
#include <string>
#include "GameEntity.h"

class GUILevelMenu;

class GUILevelMenuTab :
	public GameEntity
{
public:
	//GUILevelMenuTab();
	//GUILevelMenuTab(GameContext& gameContext, std::string name, unsigned int id, GUILevelMenu& menu);
	GUILevelMenuTab(GameContext& gameContext, unsigned int id, GUILevelMenu& menu);
	~GUILevelMenuTab();

	virtual void handleEventCurrent(const sf::Event& event);
	void drawCurrent(sf::RenderTarget & target);
private:
	GUILevelMenu& mMenu;
	unsigned int mId;

	sf::Font& mFont;
};

