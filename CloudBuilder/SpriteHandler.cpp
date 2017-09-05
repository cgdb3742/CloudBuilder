#include "SpriteHandler.h"



SpriteHandler::SpriteHandler()
{
}


SpriteHandler::~SpriteHandler()
{
}

void SpriteHandler::loadResources()
{
}

sf::Texture & SpriteHandler::getTexture(eTexture id)
{
	return mTextures[id];
}

sf::Sprite SpriteHandler::createSprite(eSprite id)
{
	sf::Sprite res;
	res.setTexture(getTexture(mSprites[id].first));
	res.setTextureRect(mSprites[id].second);
	return res;
}
