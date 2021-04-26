#pragma once
#include "Component.h"
#include "GameData.h"
#include "SplayTree.h"
#include "Node.h"

class FindComponent :
    public Component
{
private:
    bool running;
    float timeLeft;

    SplayTree* tree;

    std::vector<Node*> nodesTraveled;

public:
    FindComponent(SplayTree*);
    ~FindComponent();

    void findNode(int value, Node* = nullptr, Node* = nullptr);

    void handleEvents(sf::Event e);
    void update(const float dt);
    void draw(sf::RenderTarget*, sf::View*);
};

