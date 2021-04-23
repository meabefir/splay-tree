#include "Game.h"
#include "FontManager.h"
#include "GameData.h"
#include "Mouse.h"

#include "SplayTreeVisState.h"

Game::Game(): dt(0)
{
	this->init();
}

Game::~Game()
{
	delete this->window;
}

void Game::init()
{
	// init window
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	std::string title = "Splay tree";

	this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Close | sf::Style::Titlebar);
	sf::View view(sf::Vector2f(window_bounds.width, window_bounds.height) / 2.f,
		sf::Vector2f(window_bounds.width, window_bounds.height));
	this->window->setView(view);

	this->UIView = new sf::View(sf::Vector2f(window_bounds.width, window_bounds.height) / 2.f,
		sf::Vector2f(window_bounds.width, window_bounds.height));

	// set window size in game data
	GameData::setWindowSize(sf::Vector2f(window_bounds.width, window_bounds.height));

	// init font
	FontManager::loadFont();

	// add state
	this->states.push(new SplayTreeVisState(this->window, &this->states));
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->handleEvents();
		this->engineUpdate();
		this->update();
		this->draw();
	}
}

void Game::engineUpdate()
{
	this->dt = this->dtClock.restart().asMilliseconds();
	Mouse::update(this->window);
}

void Game::handleEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (this->states.size())
		{
			this->states.top()->handleEvents(e);
		}

		if (e.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	if (this->states.size())
	{
		this->states.top()->update(dt);

		if (this->states.top()->getQuit())
		{
			delete this->states.top();
			this->states.top() = nullptr;
			this->states.pop();
		}
	}
	else
	{
		this->window->close();
	}
}

void Game::draw()
{
	this->window->clear(sf::Color(24, 44, 52));

	if (this->states.size())
	{
		this->states.top()->draw(this->window);
	}

	this->window->display();
}
