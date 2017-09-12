#pragma once
#include "SFML/Graphics.hpp"

class ParticleHandler;

class Particle
{
public:
	struct ParticleData
	{
		ParticleData(unsigned int i, float ltm, float px, float py, float vx, float vy, float ax, float ay, float sx, float sy, float gx, float gy, sf::Sprite spr) : id(i), lifeTime(0.0f), lifeTimeMax(ltm), posx(px), posy(py), velx(vx), vely(vy), accx(ax), accy(ay), sizex(sx), sizey(sy), growthx(gx), growthy(gy), sprite(spr) {}
		ParticleData(unsigned int i, float ltm, float px, float py, float vx, float vy, float sx, float sy, float gx, float gy, sf::Sprite spr) : id(i), lifeTime(0.0f), lifeTimeMax(ltm), posx(px), posy(py), velx(vx), vely(vy), accx(0.0f), accy(0.0f), sizex(sx), sizey(sy), growthx(gx), growthy(gy), sprite(spr) {}
		ParticleData(unsigned int i, float ltm, float px, float py, float vx, float vy, float sx, float sy, sf::Sprite spr) : id(i), lifeTime(0.0f), lifeTimeMax(ltm), posx(px), posy(py), velx(vx), vely(vy), accx(0.0f), accy(0.0f), sizex(sx), sizey(sy), growthx(0.0f), growthy(0.0f), sprite(spr) {}
		ParticleData(unsigned int i, float ltm, float px, float py, float sx, float sy, sf::Sprite spr) : id(i), lifeTime(0.0f), lifeTimeMax(ltm), posx(px), posy(py), velx(0.0f), vely(0.0f), accx(0.0f), accy(0.0f), sizex(sx), sizey(sy), growthx(0.0f), growthy(0.0f), sprite(spr) {}

		unsigned int id;
		float lifeTime;
		float lifeTimeMax;
		float posx;
		float posy;
		float velx;
		float vely;
		float accx;
		float accy;
		float sizex;
		float sizey;
		float growthx;
		float growthy;
		sf::Sprite sprite;
	};

	Particle(ParticleData data, ParticleHandler& handler);
	~Particle();

	virtual void updateCurrent(sf::Time dt);
	virtual void drawCurrent(sf::RenderTarget& target);
	virtual void resize(float xratio, float yratio, float sizeratio);
private:
	ParticleData mData;

	ParticleHandler& mHandler;
};

