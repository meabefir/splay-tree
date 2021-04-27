#pragma once
#include "Component.h"
#include "GameData.h"
#include "SplayTree.h"
#include "Node.h"

class FindComponent :
    public Component
{
private:
    static float timeMultiplier;
    bool running;
    float timeLeft;

    SplayTree* tree;

    Node* nodeToRotate;

    std::vector<Node*> nodesTraveled;

    std::unordered_map<std::string, Component*>* components;

    std::string mode;
    int newNodeVal;

public:
    FindComponent(std::unordered_map<std::string, Component*>* components, SplayTree*);
    ~FindComponent();

    void setNewNodeVal(int);
    void setTree(SplayTree*);

    void findNode(int value, Node* = nullptr, Node* = nullptr);

    void setMode(std::string);
    void resetMode();

    void handleEvents(sf::Event e);
    void update(const float dt);
    void draw(sf::RenderTarget*, sf::View*);
};

