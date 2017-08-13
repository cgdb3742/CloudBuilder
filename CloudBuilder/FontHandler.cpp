#include "FontHandler.h"



FontHandler::FontHandler()
{
}


FontHandler::~FontHandler()
{
}

void FontHandler::loadResources()
{
	mFonts[eFont::Arial] = sf::Font();
	mFonts[eFont::Arial].loadFromFile("arial.ttf");
}

sf::Font & FontHandler::getFont(eFont id)
{
	return mFonts[id];
}
