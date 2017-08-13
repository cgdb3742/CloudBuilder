#pragma once
#include <map>
#include "GameEntity.h"
#include "RobotPair.h"

class Level;

class InstructionPlayer :
	public GameEntity
{
public:
	InstructionPlayer(Level& level, std::map<Enums::eColor, RobotPair>& robots);
	~InstructionPlayer();

	void activate(bool loopOnce);
	void deactivate();
	void setSpeed(float newSpeed);
	void setPause();

	void processPlayerCommand(Enums::eInstructionPlayerCommand command);

	Enums::eInstructionPlayerCommand getPlayerState();
	Enums::eInstructionPlayerCommand getPlayerSpeed();
	bool getIsPlaying();
	bool getIsPaused();

	bool progressPlayInstant();
	bool progressPlay(sf::Time dt);

	Enums::eResult getCurrentResult();

	//virtual void handleEventCurrent(const sf::Event& event);

	virtual void updateCurrent(sf::Time dt);
private:
	std::map<Enums::eColor, RobotPair>& mRobots;
	bool mIsPlaying;
	bool mIsPaused;
	float mPlayerSpeed; //0.0f for paused/stopped, -1.0f for instant
	float mPlayerProgress;
	bool mApplyingInstruction;
	bool mPauseAtEnd;
	bool mStopAtEnd;

	Level& mLevel;
};
