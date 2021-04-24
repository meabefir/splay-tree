#pragma once
#include "State.h"
#include "Node.h"

class SplayTree
{
private:
	Node* root;

public:
	SplayTree();
	~SplayTree();

	//getter setter
	Node* getRoot();

	void fixTree();

	Node* findNode(int value, Node* = nullptr);

	void rotate(Node*);
	void rotateRight(Node*);
	void rotateLeft(Node*);

	void splayUp(Node*);
	void insert(int);
	void remove(int);
	void inorder(Node* node = nullptr);

	unsigned getMaxLevel();
	int traverseHeight(Node*, int lvl);

	void draw(sf::RenderTarget*);
};

