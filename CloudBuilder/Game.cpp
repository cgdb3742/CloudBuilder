#include <iostream>
#include "Game.h"
#include "Level.h"



Game::Game():
	mWindow(sf::VideoMode(1024, 768), "Cloud Builder"),
	mResourceHandler(),
	mPopUpStack(),
	mData(),
	mContext(mResourceHandler, mPopUpStack, mData.getGameData(), mData.getLevelData()),
	mStateMachine(mContext)
{
	std::cout << "Creating Game." << std::endl;
}


Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	while (mWindow.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		//handleEvent(event);
		processEvents();
		//update();
		update(deltaTime);
		draw();
	}
}

void Game::initialize()
{
	mStateMachine.setPositionAll(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(mWindow.getSize().x, mWindow.getSize().y));
	//mStateMachine.startState(Enums::eState::Level);
	mStateMachine.requestStart(Enums::eState::Level); //TODO startState or requestStart the first state ?
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		handleEvent(event);
	}
}

void Game::handleEvent(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::Closed:
		mWindow.close();
		break;
	case sf::Event::Resized:
		mWindow.setView(sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height)));
		mStateMachine.setPositionAll(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(event.size.width, event.size.height));
		break;
	}

	mStateMachine.handleEventAll(event);
}

void Game::update(sf::Time dt)
{
	mStateMachine.updateAll(dt);
}

void Game::draw()
{
	mWindow.clear(sf::Color(63, 63, 63));
	//mWindow.draw();
	mStateMachine.drawAll(mWindow);
	mWindow.display();
}

void Game::test()
{
	initialize();

	mData.loadLevelData(1, 1);

	sf::Clock clock;
	while (mWindow.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		//std::cout << deltaTime.asMicroseconds() << std::endl;
		processEvents();
		update(deltaTime);
		draw();
	}
}
