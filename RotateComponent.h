#pragma once
#include "Component.h"
#include "GameData.h"
#include "SplayTree.h"
#include "Node.h"

class RotateComponent :
    public Component
{
private:
    bool running;
    float timeLeft;

    SplayTree* tree;

    std::vector<Node*> nodesToRotate;

public:
    RotateComponent(SplayTree*);
    ~RotateComponent();

    void splay(Node*);

    Node* findNode(int value, Node* curr_node = nullptr, Node* parent = nullptr);

    void rotate(Node*);
    void rotateRight(Node*);
    void rotateLeft(Node*);

    void fixTree();

    void handleEvents(sf::Event e);
    void update(const float dt);
    void draw(sf::RenderTarget*, sf::View*);
};

