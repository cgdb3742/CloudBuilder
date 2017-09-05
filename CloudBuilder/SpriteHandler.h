#pragma once
#include <map>
#include <utility>
#include <SFML/Graphics.hpp>

class SpriteHandler
{
public:
	enum eTexture
	{
		TextureTODO = 0
	};

	enum eSprite
	{
		SpriteTODO = 0
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

