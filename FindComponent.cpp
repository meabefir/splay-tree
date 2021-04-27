#include "FindComponent.h"
#include "RotateComponent.h"

float FindComponent::timeMultiplier = 2.f;

FindComponent::FindComponent(std::unordered_map<std::string, Component*>* components, SplayTree* tree):
    components(components), tree(tree), timeLeft(0.f), running(false), nodeToRotate(nullptr),
    mode("splay"), newNodeVal(-1)
{
}

void FindComponent::setNewNodeVal(int val)
{
    this->newNodeVal = val;
}

void FindComponent::setMode(std::string s)
{
    this->mode = s;
}

void FindComponent::resetMode()
{
    this->mode = "splay";
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

void FindComponent::setTree(SplayTree* tree)
{
    this->tree = tree;
}

void FindComponent::handleEvents(sf::Event e)
{
}

void FindComponent::update(const float dt)
{
    if (this->running)
    {
        this->timeLeft -= dt * FindComponent::timeMultiplier;
        if (this->timeLeft <= 0)
        {
            this->timeLeft += GameData::transitionDuration;

            this->nodesTraveled[0]->highlight();

            // if its last node, we call rotate component in order to rotate it
            if (this->nodesTraveled.size() == 1)
            {
                if (this->mode == "splay")
                    this->nodeToRotate = this->nodesTraveled[0];
                else if (this->mode == "insert")
                {
                    // make new node
                    Node* new_node = new Node(this->tree, this->nodesTraveled[0], newNodeVal);
                    if (newNodeVal <= this->nodesTraveled[0]->data)
                        this->nodesTraveled[0]->left = new_node;
                    else
                        this->nodesTraveled[0]->right = new_node;

                    // set its position
                    new_node->setPosition(new_node->parent->getPosition());

                    // fix rotation comp
                    auto rotate_comp = dynamic_cast<RotateComponent*>(this->components->operator[]("ROTATE_COMPONENT"));
                    rotate_comp->fixTree();
                    
                    this->resetMode();
                    this->setNewNodeVal(-1);

                    rotate_comp->resetTimer();
                    rotate_comp->splay(new_node);
                }

            }

            this->nodesTraveled.erase(this->nodesTraveled.begin());

            if (this->nodesTraveled.size() == 0)
            {
                if (this->nodeToRotate != nullptr)
                {
                    auto rotate_comp = dynamic_cast<RotateComponent*>(this->components->operator[]("ROTATE_COMPONENT"));
                    rotate_comp->splay(this->nodeToRotate);
                    this->nodeToRotate = nullptr;
                }
                this->running = false;
                this->timeLeft = 0;
                this->resetMode();
            }
        }
    }
    else
    {
        nodeToRotate = nullptr;
    }
}

void FindComponent::draw(sf::RenderTarget*, sf::View*)
{
}
