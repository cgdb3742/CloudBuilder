#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
//#include "GameDataReader.h"
//#include "LevelDataReader.h"

void testSFML()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
}

//void testPugiXML()
//{
//	GameDataReader gdr;
//	std::cout << gdr.readData() << std::endl;
//
//	LevelDataReader ldr(1,1);
//	std::cout << ldr.readData() << std::endl;
//}

int main()
{
	//testSFML();
	//testPugiXML();

	Game game;
	//game.run();
	game.test();

	return 0;
}