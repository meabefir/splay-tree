#include "State.h"
#include "Component.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states):
    window(window)
{
    this->states = states;
}

State::~State()
{
    for (auto& comp : this->components)
    {
        delete comp.second;
    }
}

void State::setQuit()
{
    this->quit = true;
}

bool State::getQuit()
{
    return this->quit;
}

void State::update(const float dt)
{
    for (auto& comp : this->components)
    {
        comp.second->update(dt);
    }
}

void State::draw(sf::RenderTarget* target, sf::View* UIView)
{
    for (auto& comp : this->components)
    {
        comp.second->draw(target, UIView);
    }
}

void State::handleEvents(sf::Event e)
{
    for (auto& comp : this->components)
    {
        comp.second->handleEvents(e);
    }
}
