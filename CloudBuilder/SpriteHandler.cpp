#include "SpriteHandler.h"



SpriteHandler::SpriteHandler()
{
}


SpriteHandler::~SpriteHandler()
{
}

void SpriteHandler::loadResources()
{
	mTextures.clear();
	mSprites.clear();

	sf::Texture cat;
	cat.loadFromFile("Textures/cat_palette.png");
	mTextures.insert(std::pair<eTexture, sf::Texture>(eTexture::Cat, cat));

	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::Head, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(0, 0, 64, 64))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::FaceAngry, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(64, 0, 64, 64))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::FaceHappy, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(128, 0, 64, 64))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::FaceNeutral, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(192, 0, 64, 64))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::FaceSleep, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(256, 0, 64, 64))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::BandRed, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(0, 64, 64, 64))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::BandBlue, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(64, 64, 64, 64))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::BandGreen, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(128, 64, 64, 64))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::BandYellow, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(192, 64, 64, 64))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::Limb, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(256, 64, 64, 64))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::Body, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(0, 128, 64, 64))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::ShirtRed, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(64, 128, 64, 64))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::ShirtBlue, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(128, 128, 64, 64))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::ShirtGreen, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(192, 128, 64, 64))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::ShirtYellow, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(256, 128, 64, 64))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::PartCloud, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(0, 192, 32, 32))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::PartLightRed, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(32, 192, 32, 32))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::PartLightBlue, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(64, 192, 32, 32))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::PartLightGreen, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(96, 192, 32, 32))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::PartLightYellow, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(128, 192, 32, 32))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::PartYes, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(160, 192, 32, 32))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::PartNo, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(192, 192, 32, 32))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::PartNote, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(224, 192, 32, 32))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::PartMess, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(256, 192, 32, 32))));
	mSprites.insert(std::pair<eSprite, std::pair<eTexture, sf::IntRect>>(eSprite::PartSleep, std::pair<eTexture, sf::IntRect>(eTexture::Cat, sf::IntRect(288, 192, 32, 32))));
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
