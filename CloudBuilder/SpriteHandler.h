#pragma once
#include <map>
#include <utility>
#include <SFML/Graphics.hpp>

class SpriteHandler
{
public:
	enum eTexture
	{
		Cat = 0
	};

	enum eSprite
	{
		Head = 0,
		FaceAngry = 1,
		FaceHappy = 2,
		FaceNeutral = 3,
		FaceSleep = 4,
		BandRed = 10,
		BandBlue = 11,
		BandGreen = 12,
		BandYellow = 13,
		Limb = 14,
		Body = 20,
		ShirtRed = 21,
		ShirtBlue = 22,
		ShirtGreen = 23,
		ShirtYellow = 24,
		PartCloud = 30,
		PartLightRed = 31,
		PartLightBlue = 32,
		PartLightGreen = 33,
		PartLightYellow = 34,
		PartYes = 35,
		PartNo = 36,
		PartNote = 37,
		PartMess = 38,
		PartSleep = 39
	};

	SpriteHandler();
	~SpriteHandler();

	void loadResources();

	sf::Texture& getTexture(eTexture id);
	sf::Sprite createSprite(eSprite id);
private:
	std::map<eTexture, sf::Texture> mTextures;
	std::map<eSprite, std::pair<eTexture, sf::IntRect>> mSprites;
};

