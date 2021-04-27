#pragma once
#include "State.h"
class PauseState :
    public State
{
public:
    PauseState(sf::RenderWindow*, std::stack<State*>*);
    ~PauseState();

    void update(const float dt);
    void draw(sf::RenderTarget*, sf::View*);
    void handleEvents(sf::Event);
};

