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

	void calcMaxes();

	void insert(int);
	void inorder(Node* node = nullptr);

	unsigned getMaxLevel();
	int traverseHeight(Node*, int lvl);

	void draw(sf::RenderTarget*);
};

