#include "SplayTree.h"


SplayTree::SplayTree()
{
    this->insert(3413);
    this->insert(3252);
    this->insert(4535);
    this->insert(2132);
    this->insert(6786);
    this->insert(1231);
    this->insert(3252);
    this->insert(6545);
    this->insert(1231);
    this->insert(1412);
    this->insert(5235);
    this->insert(12);
    this->insert(2121);
    this->insert(5235);
    this->insert(1211);
}

SplayTree::~SplayTree()
{
    delete this->root;
}

Node* SplayTree::getRoot()
{
    return this->root;
}

void SplayTree::calcMaxes()
{
    this->root->calcMax();
    this->root->applyOffset();
}

void SplayTree::insert(int val)
{
    Node* curr_node = root;

    // if root is null
    if (root == nullptr)
    {
        root = new Node(this, val);
        this->calcMaxes();
        return;
    }

    //while (curr_node != nullptr)
    while (true)
    {
        if (val <= curr_node->data)
        {
            if (curr_node->left == nullptr)
            {
                curr_node->left = new Node(this, curr_node, val);
                this->calcMaxes();
                return;
            }
            else
                curr_node = curr_node->left;
        }
        else if (val > curr_node->data)
        {
            if (curr_node->right == nullptr)
            {
                curr_node->right = new Node(this, curr_node, val);
                this->calcMaxes();
                return;
            }
            else
                curr_node = curr_node->right;
        }
    }
}

void SplayTree::inorder(Node* node)
{
    if (node == nullptr)
        node = this->root;

    if (node->left != nullptr)
        this->inorder(node->left);
    std::cout << node->data << ' ';
    if (node->right != nullptr)
        this->inorder(node->right);
}

unsigned SplayTree::getMaxLevel()
{
    if (this->root == nullptr)
        return 0;

    this->traverseHeight(this->root, 0);
}

int SplayTree::traverseHeight(Node* node, int lvl)
{
    // !!!!!!!!!!!
    if (node == nullptr)
        return lvl - 1;
    if (node->left == nullptr && node->right == nullptr)
        return lvl;

    return std::max(this->traverseHeight(node->left, lvl + 1), this->traverseHeight(node->right, lvl + 1));
}

void SplayTree::draw(sf::RenderTarget* target)
{
    if (this->root != nullptr)
        this->root->draw(target);
}
