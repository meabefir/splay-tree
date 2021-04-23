#include "SplayTreeVisState.h"
#include "Mouse.h"
#include <ctime>

SplayTreeVisState::SplayTreeVisState(sf::RenderWindow* window, std::stack<State*>* states): 
	State(window, states)
{
	srand(time(0));
	splayTree = new SplayTree();
}

SplayTreeVisState::~SplayTreeVisState()
{
	std::cout << " Deleting splay tree\n";
	delete this->splayTree;
}

void SplayTreeVisState::resetTree()
{
	delete this->splayTree;
	this->splayTree = new SplayTree();
}

void SplayTreeVisState::handleEvents(sf::Event e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		if (e.key.code == sf::Keyboard::Key::R)
			this->resetTree();
	}

	// uncomment this after you make ui elemets unaffected by panning
	if (e.type == sf::Event::MouseMoved)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			sf::View curr_view = this->window->getView();
			curr_view.move(-Mouse::relativePos);
			this->window->setView(curr_view);
		}
	}

	// if scroll
	if (e.type == sf::Event::MouseWheelMoved)
	{
		// zoom out
		if (e.mouseWheel.delta == -1)
		{
			sf::View curr_view = this->window->getView();
			curr_view.zoom(1.1f);
			Mouse::zoom = Mouse::zoom * 1.1f;
			this->window->setView(curr_view);
		}
		else if (e.mouseWheel.delta == 1 && Mouse::zoom >= .5f) // zoom in
		{
			sf::View curr_view = this->window->getView();
			curr_view.zoom(.9f);
			Mouse::zoom = Mouse::zoom * .9f;
			this->window->setView(curr_view);
		}
	}
}

void SplayTreeVisState::update(const float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		this->splayTree->insert(std::rand() % 10000);
}

void SplayTreeVisState::draw(sf::RenderTarget* target)
{
	this->splayTree->draw(target);
}
