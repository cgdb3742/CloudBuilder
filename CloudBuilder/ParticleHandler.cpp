//#include <utility>
#include <random>
#include "ParticleHandler.h"
#include "ResourceHandler.h"



ParticleHandler::ParticleHandler(float screenWidth, float screenHeight, ResourceHandler& resourceHandler):
	mScreenWidth(screenWidth),
	mScreenHeight(screenHeight),
	mCurrentId(0),
	mResourceHandler(resourceHandler)
{
}


ParticleHandler::~ParticleHandler()
{
}

Particle & ParticleHandler::createParticle(eParticle type, float lifetime, float posx, float posy, float sizex, float sizey)
{
	mCurrentId++;

	if (mCurrentId > 1000000)
	{
		mCurrentId = 0;
	}

	static std::random_device rd;
	static std::default_random_engine engine(rd());
	static std::uniform_real_distribution<> distribution(0.0f, 1.0f);
	float randFloat = static_cast<float>(distribution(engine));

	sf::Transform rot(sf::Transform::Identity);
	rot.rotate(360.0f * randFloat);
	sf::Vector2f dir(1.0f, 0.0f);
	dir = rot.transformPoint(dir);

	sf::Sprite sprite;
	float accx = 0.0f;
	float accy = 0.0f;
	float velx = 0.0f;
	float vely = 0.0f;
	float growthx = 0.0f;
	float growthy = 0.0f;

	switch (type)
	{
	case eParticle::ParticleCloud:
		sprite = mResourceHandler.createSprite(SpriteHandler::eSprite::PartCloud);
		growthx = -sizex / lifetime;
		growthy = -sizey / lifetime;
		velx = dir.x * sizex * 5.0f / lifetime;
		vely = dir.y * sizey * 5.0f / lifetime;
		accy = sizey * 5.0f / lifetime;
		break;
	case eParticle::ParticleLightRed:
		sprite = mResourceHandler.createSprite(SpriteHandler::eSprite::PartLightRed);
		growthx = -sizex / lifetime;
		growthy = -sizey / lifetime;
		velx = dir.x * sizex * 5.0f / lifetime;
		vely = dir.y * sizey * 5.0f / lifetime;
		break;
	case eParticle::ParticleLightBlue:
		sprite = mResourceHandler.createSprite(SpriteHandler::eSprite::PartLightBlue);
		growthx = -sizex / lifetime;
		growthy = -sizey / lifetime;
		velx = dir.x * sizex * 5.0f / lifetime;
		vely = dir.y * sizey * 5.0f / lifetime;
		break;
	case eParticle::ParticleLightGreen:
		sprite = mResourceHandler.createSprite(SpriteHandler::eSprite::PartLightGreen);
		growthx = -sizex / lifetime;
		growthy = -sizey / lifetime;
		velx = dir.x * sizex * 5.0f / lifetime;
		vely = dir.y * sizey * 5.0f / lifetime;
		break;
	case eParticle::ParticleLightYellow:
		sprite = mResourceHandler.createSprite(SpriteHandler::eSprite::PartLightYellow);
		growthx = -sizex / lifetime;
		growthy = -sizey / lifetime;
		velx = dir.x * sizex * 5.0f / lifetime;
		vely = dir.y * sizey * 5.0f / lifetime;
		break;
	case eParticle::ParticleYes:
		sprite = mResourceHandler.createSprite(SpriteHandler::eSprite::PartYes);
		growthx = sizex * 0.5f / lifetime;
		growthy = (sizex * 1.5f - sizey) / lifetime;
		vely = -sizey * 20.0f / lifetime;
		break;
	case eParticle::ParticleNo:
		sprite = mResourceHandler.createSprite(SpriteHandler::eSprite::PartNo);
		growthx = sizex * 0.5f / lifetime;
		growthy = (sizex * 1.5f - sizey) / lifetime;
		vely = -sizey * 20.0f / lifetime;
		break;
	case eParticle::ParticleNote:
		sprite = mResourceHandler.createSprite(SpriteHandler::eSprite::PartNote);
		growthx = sizex * 0.5f / lifetime;
		growthy = (sizex * 1.5f - sizey) / lifetime;
		vely = -sizey * 20.0f / lifetime;
		break;
	case eParticle::ParticleMess:
		sprite = mResourceHandler.createSprite(SpriteHandler::eSprite::PartMess);
		growthx = sizex * 0.5f / lifetime;
		growthy = (sizex * 1.5f - sizey) / lifetime;
		vely = -sizey * 20.0f / lifetime;
		break;
	case eParticle::ParticleSleep:
		sprite = mResourceHandler.createSprite(SpriteHandler::eSprite::PartSleep);
		growthx = sizex * 0.5f / lifetime;
		growthy = (sizex * 1.5f - sizey) / lifetime;
		vely = -sizey * 20.0f / lifetime;
		break;
	}

	sf::FloatRect spriteRect = sprite.getLocalBounds();
	sprite.setOrigin(spriteRect.left + spriteRect.width / 2.0f, spriteRect.top + spriteRect.height / 2.0f);

	Particle::ParticleData data(mCurrentId, lifetime, posx, posy, velx, vely, accx, accy, sizex, sizey, growthx, growthy, sprite);

	Particle toInsert(data, *this);

	return (mParticles.insert(std::pair<unsigned int, Particle>(mCurrentId, toInsert))).first->second;
}

void ParticleHandler::destroyParticle(unsigned int id)
{
	mToRemove.push_back(id);
}

void ParticleHandler::clearParticles()
{
	mParticles.clear();
}

void ParticleHandler::updateAll(sf::Time dt)
{
	for (auto& part : mParticles)
	{
		part.second.updateCurrent(dt);
	}

	for (unsigned int removable : mToRemove)
	{
		mParticles.erase(removable);
	}

	mToRemove.clear();
}

void ParticleHandler::drawAll(sf::RenderTarget & target)
{
	for (auto part : mParticles)
	{
		part.second.drawCurrent(target);
	}
}

void ParticleHandler::setPositionAll(sf::Vector2f minCorner, sf::Vector2f maxBox)
{
	float xratio = maxBox.x / mScreenWidth;
	float yratio = maxBox.y / mScreenHeight;
	float sizeratio = (xratio + yratio) / 2.0f;

	for (auto part : mParticles)
	{
		part.second.resize(xratio, yratio, sizeratio);
	}

	mScreenWidth = maxBox.x;
	mScreenHeight = maxBox.y;
}
