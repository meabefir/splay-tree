#pragma once
#include "State.h"

class Component
{
protected:

public:
	virtual void handleEvents(sf::Event e) = 0;
	virtual void update(const float dt) = 0;
	virtual void draw(sf::RenderTarget*, sf::View*) = 0;
};

