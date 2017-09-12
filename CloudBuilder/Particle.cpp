#include "Particle.h"
#include "ParticleHandler.h"



Particle::Particle(ParticleData data, ParticleHandler& handler):
	mData(data),
	mHandler(handler)
{
}


Particle::~Particle()
{
}

void Particle::updateCurrent(sf::Time dt)
{
	mData.velx += mData.accx * dt.asSeconds();
	mData.vely += mData.accy * dt.asSeconds();
	mData.posx += mData.velx * dt.asSeconds();
	mData.posy += mData.vely * dt.asSeconds();
	mData.sizex += mData.growthx * dt.asSeconds();
	mData.sizey += mData.growthy * dt.asSeconds();

	mData.lifeTime += dt.asSeconds();

	if (mData.lifeTime >= mData.lifeTimeMax)
	{
		mHandler.destroyParticle(mData.id);
	}
}

void Particle::drawCurrent(sf::RenderTarget & target)
{
	//sf::RectangleShape square(sf::Vector2f(mData.sizex, mData.sizey));
	//square.setPosition(mData.posx - mData.sizex / 2.0f, mData.posy - mData.sizey / 2.0f);
	//square.setFillColor(sf::Color(191, 0, 0));
	//target.draw(square);

	mData.sprite.setPosition(mData.posx, mData.posy);
	mData.sprite.setScale(mData.sizex / (mData.sprite.getLocalBounds().width), mData.sizey / (mData.sprite.getLocalBounds().height));
	target.draw(mData.sprite);
}

void Particle::resize(float xratio, float yratio, float sizeratio)
{
	mData.posx *= xratio;
	mData.posy *= yratio;
	mData.velx *= xratio;
	mData.vely *= yratio;
	mData.accx *= xratio;
	mData.accy *= yratio;
	mData.sizex *= sizeratio;
	mData.sizey *= sizeratio;
	mData.growthx *= sizeratio;
	mData.growthy *= sizeratio;
}
