#pragma once
#include <vector>
#include "GameEntity.h"
#include "GUIOptionsLanguage.h"
#include "GUIOptionsVolume.h"
#include "GUIButtonChangeState.h"
class GUIOptionsContainer :
	public GameEntity
{
public:
	GUIOptionsContainer(GameContext& gameContext);
	~GUIOptionsContainer();

	virtual void drawCurrent(sf::RenderTarget& target);

	virtual void setPositionChilds(sf::Vector2f minCorner, sf::Vector2f maxBox);
protected:
	virtual void updateChildsVector();
private:
	std::vector<GUIOptionsLanguage> mLanguageButtons;

	GUIOptionsVolume mMusicVolume;
	GUIOptionsVolume mSoundVolume;

	GUIButtonChangeState mToLevelSelect;
};

