#include "RotateComponent.h"


RotateComponent::RotateComponent(std::unordered_map<std::string, Component*>* components, SplayTree* tree):
    tree(tree), components(components), running(false), timeLeft(0.f)
{
}

RotateComponent::~RotateComponent()
{
}

Node* RotateComponent::findNode(int value, Node* curr_node, Node* parent)
{
    if (this->tree->root == nullptr)
        return nullptr;

    if (curr_node == nullptr)
    {
        //this->splay(parent);
        return parent;
    }

    if (curr_node->data == value)
    {
        //this->splay(curr_node);
        return curr_node;
    }
    else
    {
        if (value < curr_node->data)
        {
            return findNode(value, curr_node->left, curr_node);

        }
        else if (value > curr_node->data)
        {
            return findNode(value, curr_node->right, curr_node);
        }
    }
}

void RotateComponent::resetTimer()
{
    this->timeLeft = GameData::transitionDuration;
}

void RotateComponent::rotate(Node* node)
{
    if (node == nullptr)
        return;
    if (node->parent == nullptr)
        return;
    if (node->parent->left == node)
        this->rotateRight(node);
    else if (node->parent->right == node)
        this->rotateLeft(node);
}

void RotateComponent::rotateRight(Node* node)
{
    Node* old_parent = node->parent;
    Node* old_right = node->right;

    old_parent->left = old_right;
    if (old_right != nullptr)
    {
        old_right->parent = old_parent;
    }

    if (old_parent->parent != nullptr)
    {
        node->parent = old_parent->parent;
        if (old_parent->parent->left == old_parent)
            old_parent->parent->left = node;
        else
            old_parent->parent->right = node;
    }
    else if (old_parent->parent == nullptr)
    {
        this->tree->root = node;
        node->parent = nullptr;
    }

    node->right = old_parent;
    old_parent->parent = node;

    this->fixTree();
}

void RotateComponent::rotateLeft(Node* node)
{
    Node* old_parent = node->parent;
    Node* old_left = node->left;

    old_parent->right = old_left;
    if (old_left != nullptr)
    {
        old_left->parent = old_parent;
    }

    if (old_parent->parent != nullptr)
    {
        node->parent = old_parent->parent;
        if (old_parent->parent->left == old_parent)
            old_parent->parent->left = node;
        else
            old_parent->parent->right = node;
    }
    else if (old_parent->parent == nullptr)
    {
        this->tree->root = node;
        node->parent = nullptr;
    }

    node->left = old_parent;
    old_parent->parent = node;

    this->fixTree();
}

void RotateComponent::setTree(SplayTree* tree)
{
    this->tree = tree;
}

void RotateComponent::splay(Node* node)
{
    // if node is root do nothing
    if (node == this->tree->root)
        return;
    // if node is child of root
    if (node->parent == this->tree->root)
    {
        this->nodesToRotate.push_back({ node, 0 });
        running = true;
    }
    else
    {
        // check if zig zig or zig zag
        int zig_count = 0;
        // check parent
        if (node->parent->left == node)
            zig_count += 1;
        else
            zig_count -= 1;
        // check grandparent
        if (node->parent->parent->left == node->parent)
            zig_count += 1;
        else
            zig_count -= 1;

        // if zig_count == 0 that meansa zig zag, else it means zag
        if (zig_count == 0)
        {
            this->nodesToRotate.push_back({ node, 0 });
            this->running = true;
            //this->splay(node);
        }
        else
        {
            // rotate parent
            this->nodesToRotate.push_back({ node, 1 });
            // rotate self
            this->nodesToRotate.push_back({ node, 0 });

            this->running = true;
            //this->splay(node);
        }
    }
}

void RotateComponent::fixTree()
{
    if (this->tree->root != nullptr)
    {
        this->tree->root->calcMax();
        this->tree->root->setTarget();
    }
}

void RotateComponent::handleEvents(sf::Event e)
{
}

void RotateComponent::update(const float dt)
{
    if (this->running)
    {
        this->timeLeft -= dt;
        if (this->timeLeft <= 0)
        {
            this->timeLeft += GameData::transitionDuration;
            

            if (this->nodesToRotate[0].second == 0)
                this->rotate(nodesToRotate[0].first);
            else
                this->rotate(nodesToRotate[0].first->parent);

            this->splay(nodesToRotate[0].first);

            this->nodesToRotate.erase(this->nodesToRotate.begin());

            if (this->nodesToRotate.size() == 0)
            {
                this->running = false;
                this->timeLeft = 0.f;
            }
        }
    }
}

void RotateComponent::draw(sf::RenderTarget*, sf::View*)
{
}
