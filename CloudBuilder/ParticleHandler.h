#pragma once
#include <map>
#include <list>
#include "Particle.h"

class ResourceHandler;

class ParticleHandler
{
public:
	enum eParticle
	{
		ParticleCloud = 0,
		ParticleLightRed = 1,
		ParticleLightBlue = 2,
		ParticleLightGreen = 3,
		ParticleLightYellow = 4,
		ParticleYes = 5,
		ParticleNo = 6,
		ParticleNote = 7,
		ParticleMess = 8,
		ParticleSleep = 9
	};

	ParticleHandler(float screenWidth, float screenHeight, ResourceHandler& resourceHandler);
	~ParticleHandler();

	Particle& createParticle(eParticle type, float lifetime, float posx, float posy, float sizex, float sizey);
	void destroyParticle(unsigned int id);
	void clearParticles();

	virtual void updateAll(sf::Time dt);
	virtual void drawAll(sf::RenderTarget& target);
	virtual void setPositionAll(sf::Vector2f minCorner, sf::Vector2f maxBox);
private:
	std::map<unsigned int, Particle> mParticles;
	std::list<unsigned int> mToRemove;

	float mScreenWidth;
	float mScreenHeight;

	unsigned int mCurrentId;

	ResourceHandler& mResourceHandler;
};

