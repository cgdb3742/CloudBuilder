#pragma once
#include <map>
#include <SFML/Graphics.hpp>

class FontHandler
{
public:
	enum eFont
	{
		Arial = 0
	};

	FontHandler();
	~FontHandler();

	void loadResources();
	sf::Font& getFont(eFont id);

private:
	std::map<eFont, sf::Font> mFonts;
};

