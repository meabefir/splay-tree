#pragma once
#include "State.h"
#include "GameData.h"
#include "FontManager.h"

class SplayTree;

class Node
{
private:
	Node* parent;
	Node* left;
	Node* right;
	SplayTree* tree;

	int nrLeftNodes;
	int nrRightNodes;
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

public:
	Node(SplayTree*, Node* parent, int data);
	Node(SplayTree*, int data);
	~Node();

	// setter getter
	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition();

	unsigned getLevel();
	unsigned getIndexInLevel();

	void init();
	void draw(sf::RenderTarget*);

	void calcMax();
	void applyOffset();

	friend class SplayTree;
};

