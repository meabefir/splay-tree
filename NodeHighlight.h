#pragma once
#include "State.h"

class Node;

class NodeHighlight
{
private:
	static sf::Color outlineColor;
	static float outlineThickness;
	static float totalTime;
	float currTime;
	bool running;

	Node* node;
	sf::CircleShape shape;

public:
	NodeHighlight(Node* node);
	~NodeHighlight();

	void start();
	void stop();

	void update(const float dt);
	void draw(sf::RenderTarget*);
};

