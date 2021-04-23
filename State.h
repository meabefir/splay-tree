#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

#include <SFML/Graphics.hpp>

class State
{
protected:
	sf::RenderWindow* window;
	std::stack<State*>* states;

	bool quit = false;

public:
	State(sf::RenderWindow*, std::stack<State*>* states);
	virtual ~State();

	void setQuit();
	bool getQuit();

	virtual void update(const float dt) = 0;
	virtual void draw(sf::RenderTarget*) = 0;
	virtual void handleEvents(sf::Event) = 0;
};

