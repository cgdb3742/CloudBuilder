#pragma once
#include "GUIButton.h"
#include "CloudPicture.h"

class Level;

class GUITestsModel :
	public GUIButton
{
public:
	GUITestsModel(GameContext& gameContext, sf::Vector2f positionRatio, Level& level);
	~GUITestsModel();

	void updateCloud();

	virtual void updateCurrent(sf::Time dt);

	void drawAccept(sf::RenderTarget& target, sf::Vector2f topLeftCorner, sf::Vector2f boundingBox);
	void drawReject(sf::RenderTarget& target, sf::Vector2f topLeftCorner, sf::Vector2f boundingBox);
	void drawArrow(sf::RenderTarget& target, sf::Vector2f topLeftCorner, sf::Vector2f boundingBox);
	virtual void drawCurrent(sf::RenderTarget& target);
private:
	Level& mLevel;

	unsigned int mCurrentCloud;
	CloudPicture mStartingCloud;
	bool mIsValidation;
	bool mWantAccept;
	CloudPicture mResultCloud;
};

