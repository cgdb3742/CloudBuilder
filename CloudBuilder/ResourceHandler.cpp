#include "ResourceHandler.h"



ResourceHandler::ResourceHandler()
{
	//TODO Pre-load only stuff necessary for the first screen and create a loading screen for the rest ?
	loadResources();
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
