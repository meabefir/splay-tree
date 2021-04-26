#pragma once
#include "State.h"
#include "GameData.h"
#include "FontManager.h"
#include "NodeHighlight.h"

class SplayTree;

class Node
{
private:
	Node* parent;
	Node* left;
	Node* right;
	SplayTree* tree;

	sf::Vector2f target;
	sf::Vector2f moveVector;

	int maxLeft;
	int maxRight;

	int data;
	unsigned level;

	sf::Text textRender;
	sf::Text maxLeftTextRender;
	sf::Text maxRightTextRender;

	static float radius;
	static float outlineThickness;
	static float yStart;
	static float yMargin;
	static float xMargin;
	static sf::Color fillColor;

	sf::CircleShape shape;
	sf::VertexArray vertexArray;

	NodeHighlight* nodeHighlight;

public:
	Node(SplayTree*, Node* parent, int data);
	Node(SplayTree*, int data);
	~Node();

	// setter getter
	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition();
	int getData();

	unsigned getLevel();
	unsigned getIndexInLevel();

	void init();
	void update(const float dt);
	void draw(sf::RenderTarget*);

	void calcMax();
	void applyOffset();
	void setTarget();

	void highlight();

	friend class SplayTree;
	friend class NodeHighlight;
	friend class FindComponent;
	friend class RotateComponent;
};

