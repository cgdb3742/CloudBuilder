#include <iostream>
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
	std::cout << "Font loaded." << std::endl;
}

sf::Font & FontHandler::getFont(eFont id)
{
	std::cout << "Font requested." << std::endl;
	return mFonts[id];
}
