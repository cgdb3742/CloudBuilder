#include "ResourceHandler.h"



ResourceHandler::ResourceHandler()
{
}


ResourceHandler::~ResourceHandler()
{
}

void ResourceHandler::loadResources()
{
	mFonts.loadResources();
}

sf::Font & ResourceHandler::getFont(FontHandler::eFont id)
{
	return mFonts.getFont(id);
}
