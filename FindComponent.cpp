
#include "FindComponent.h"

FindComponent::FindComponent(SplayTree* tree):
    tree(tree), timeLeft(0.f), running(false)
{
}

FindComponent::~FindComponent()
{
}

void FindComponent::findNode(int value, Node* curr_node, Node* parent)
{
    if (this->tree->root == nullptr)
        return;

    if (curr_node == nullptr)
    {
        //this->splay(parent);
        this->running = true;
        return;
    }

    this->nodesTraveled.push_back(curr_node);

    if (curr_node->data == value)
    {
        //this->splay(curr_node);
        this->running = true;
        return;
    }
    else
    {
        if (value < curr_node->data)
        {
            findNode(value, curr_node->left, curr_node);

        }
        else if (value > curr_node->data)
        {
            findNode(value, curr_node->right, curr_node);
        }
    }
}

void FindComponent::handleEvents(sf::Event e)
{
}

void FindComponent::update(const float dt)
{
    if (this->running)
    {
        this->timeLeft -= dt;
        if (this->timeLeft <= 0)
        {
            this->timeLeft += GameData::transitionDuration;

            this->nodesTraveled[0]->highlight();
            this->nodesTraveled.erase(this->nodesTraveled.begin());

            if (this->nodesTraveled.size() == 0)
            {
                this->running = false;
                this->timeLeft = 0;
            }
        }
    }
}

void FindComponent::draw(sf::RenderTarget*, sf::View*)
{
}
