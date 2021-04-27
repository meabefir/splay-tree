#pragma once
#include "Component.h"
#include "SplayTree.h"

class InsertComponent :
    public Component
{
private:
    std::unordered_map<std::string, Component*>* components;

public:
    InsertComponent(std::unordered_map<std::string, Component*>* components, SplayTree*);
    ~InsertComponent();

    void handleEvents(sf::Event);
    void update(const float dt);
    void draw(sf::RenderTarget*, sf::View*);
};

