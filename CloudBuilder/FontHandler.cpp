#include "FontHandler.h"



FontHandler::FontHandler()
{
}


FontHandler::~FontHandler()
{
}

void FontHandler::loadResources()
{
	sf::Font arial;
	arial.loadFromFile("arial.ttf");
	mFonts.insert(std::pair<eFont,sf::Font>(eFont::Arial,arial));
}

sf::Font & FontHandler::getFont(eFont id)
{
	return mFonts[id];
}
