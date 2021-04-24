#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

#include <SFML/Graphics.hpp>

class Component;

class State
{
protected:
	sf::RenderWindow* window;
	std::stack<State*>* states;
	std::unordered_map<std::string, Component*> components;

	bool quit = false;

public:
	State(sf::RenderWindow*, std::stack<State*>* states);
	virtual ~State();

	void setQuit();
	bool getQuit();

	virtual void update(const float dt) = 0;
	virtual void draw(sf::RenderTarget*, sf::View*) = 0;
	virtual void handleEvents(sf::Event) = 0;
};

