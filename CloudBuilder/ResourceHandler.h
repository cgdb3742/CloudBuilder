#pragma once
#include "FontHandler.h"

class ResourceHandler
{
public:
	ResourceHandler();
	~ResourceHandler();

	void loadResources();

	sf::Font& getFont(FontHandler::eFont id);

private:
	FontHandler mFonts;
};

