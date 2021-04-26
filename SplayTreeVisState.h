#pragma once
#include "State.h"
#include "SplayTree.h"
#include "InputButton.h"
#include "Component.h"
#include "FindComponent.h"
#include "RotateComponent.h"

class SplayTreeVisState: public State
{
private:
	SplayTree* splayTree;

public:
	SplayTreeVisState(sf::RenderWindow*, std::stack<State*>*);
	~SplayTreeVisState();

	void resetTree();

	void handleEvents(sf::Event);
	void update(const float dt);
	void draw(sf::RenderTarget*, sf::View*);
};

