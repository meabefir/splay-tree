#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states):
    window(window)
{
    this->states = states;
}

State::~State()
{
}

void State::setQuit()
{
    this->quit = true;
}

bool State::getQuit()
{
    return this->quit;
}
