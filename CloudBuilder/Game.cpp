#include <iostream>
#include "Game.h"
#include "Level.h"



Game::Game():
	mWindow(sf::VideoMode(1024, 768), "Cloud Builder"),
	mResourceHandler(),
	mParticleHandler(static_cast<float>(mWindow.getSize().x), static_cast<float>(mWindow.getSize().y), mResourceHandler),
	mStateStack(),
	mPopUpStack(mStateStack),
	mData(mPopUpStack),
	mContext(mResourceHandler, mParticleHandler, mStateStack, mPopUpStack, mData),
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
	mStateMachine.setPositionAll(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(static_cast<float>(mWindow.getSize().x), static_cast<float>(mWindow.getSize().y)));
	//mStateMachine.startState(Enums::eState::Level);
	//mStateMachine.requestStart(Enums::eState::Level); //TODO startState or requestStart the first state ?
	//mStateMachine.requestStart(Enums::eState::LevelSelect);
	mStateStack.addStartRequest(Enums::eState::LevelSelect);
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
		mWindow.setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height))));
		mStateMachine.setPositionAll(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(static_cast<float>(event.size.width), static_cast<float>(event.size.height)));
		break;
	}

	mStateMachine.handleEventAll(event);
}

void Game::update(sf::Time dt)
{
	mResourceHandler.updateAll(dt);
	mParticleHandler.updateAll(dt);
	mStateMachine.updateAll(dt);
}

void Game::draw()
{
	mWindow.clear(sf::Color(63, 63, 63));
	//mWindow.draw();
	mStateMachine.drawAll(mWindow);
	mParticleHandler.drawAll(mWindow);
	mWindow.display();
}

void Game::test()
{
	initialize();

	//mData.loadLevelData(1, 1);
	//mData.writeLanguage("fr");
	//mData.writeLevelStatus(1, 2, "Complete");
	//mData.writeSavedBoard(2, 1, "w8h8i1j1vSSrr");
	//mPopUpStack.addMessage("test1", "test1");
	//mPopUpStack.addMessage("test2", "test2");

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
