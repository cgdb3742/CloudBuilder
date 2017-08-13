#pragma once
#include <string>
#include "GameEntity.h"

class GUILevelMenu;

class GUILevelMenuTab :
	public GameEntity
{
public:
	//GUILevelMenuTab();
	GUILevelMenuTab(std::string name, unsigned int id, GUILevelMenu& menu);
	~GUILevelMenuTab();

	virtual void handleEventCurrent(const sf::Event& event);
	void drawCurrent(sf::RenderTarget & target);
private:
	GUILevelMenu& mMenu;
	std::string mName;
	unsigned int mId;
};

