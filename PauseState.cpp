#include "PauseState.h"

PauseState::PauseState(sf::RenderWindow* window, std::stack<State*>* states):
	State(window, states)
{
}

PauseState::~PauseState()
{
}

void PauseState::update(const float dt)
{
}

void PauseState::draw(sf::RenderTarget*, sf::View*)
{
}

void PauseState::handleEvents(sf::Event e)
{
	if (e.type == sf::Event::KeyReleased)
		if (e.key.code == sf::Keyboard::Escape)
			this->setQuit();
}
