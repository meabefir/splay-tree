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

	Node* findNode(int value, Node* = nullptr, Node* = nullptr);

	void rotate(Node*);
	void rotateRight(Node*);
	void rotateLeft(Node*);

	void splay(Node*);
	void insert(int);
	void remove(int);
	void inorder(Node* node = nullptr);

	Node* getSuccessor(Node*);
	Node* getPredecessor(Node*);

	unsigned getMaxLevel();
	int traverseHeight(Node*, int lvl);
	Node* getBiggestInSubtree(Node*);

	void update(const float dt);
	void draw(sf::RenderTarget*);

	friend class FindComponent;
	friend class RotateComponent;
};

