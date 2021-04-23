#pragma once
#include "State.h"

class Game
{
private:
	sf::RenderWindow* window;
	sf::View* UIView;

	// states
	std::stack<State*> states;

	// delta time
	float dt;
	sf::Clock dtClock;

public:
	Game();
	~Game();

	void init();
	void run();
	void engineUpdate();
	void handleEvents();
	void update();
	void draw();
};

