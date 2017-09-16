#pragma once
#include "GUIButton.h"
class GUIOptionsVolume :
	public GUIButton
{
public:
	GUIOptionsVolume(GameContext& gameContext, sf::Vector2f positionRatio, bool controlMusic);
	~GUIOptionsVolume();

	void beginDrag(float mousePosx);
	void updateDrag(float mousePosx);
	void endDrag(float mousePosx);

	virtual void handleEventCurrent(const sf::Event& event);
	virtual void drawCurrent(sf::RenderTarget& target);
	virtual void setPositionCurrent(sf::Vector2f minCorner, sf::Vector2f maxBox);
private:
	bool mControlMusic; //true for music volume, false for sound volume
	float mVolumeRatio;

	float mBarWidthRatio;
	
	bool mIsDragged;
	float mCurrentPos;
	float mMinPos;
	float mMaxPos;
};

