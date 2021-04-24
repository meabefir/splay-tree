#include "SplayTree.h"


SplayTree::SplayTree()
{
    this->insert(5);
    this->insert(3);
    this->insert(7);
    this->insert(1);
    this->insert(4);
    this->insert(6);
    this->insert(8);
}

SplayTree::~SplayTree()
{
    delete this->root;
}

Node* SplayTree::getRoot()
{
    return this->root;
}

void SplayTree::fixTree()
{
    //std::cout << this->root->data << '\n';
    this->root->calcMax();
    this->root->applyOffset();

    /*this->inorder();
    std::cout << '\n';*/
}

Node* SplayTree::findNode(int value, Node* curr_node)
{
    if (curr_node == nullptr)
        curr_node = this->root;
    if (curr_node->data == value)
        return curr_node;
    else
    {
        if (value < curr_node->data)
        {
            if (curr_node->left != nullptr)
                return findNode(value, curr_node->left);
            else
                return curr_node;
        }
        else if (value > curr_node->data)
        {
            if (curr_node->right != nullptr)
                return findNode(value, curr_node->right);
            else
                return curr_node;
        }
    }
}

void SplayTree::rotate(Node* node)
{
    if (node->parent == nullptr)
        return;
    std::cout << " Rotating " << node->data << '\n';
    if (node->parent->left == node)
        this->rotateRight(node);
    else if (node->parent->right == node)
        this->rotateLeft(node);
}

void SplayTree::rotateRight(Node* node)
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
        this->root = node;
        node->parent = nullptr;
    }

    node->right = old_parent;
    old_parent->parent = node;

    this->fixTree();
}

void SplayTree::rotateLeft(Node* node)
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
        this->root = node;
        node->parent = nullptr;
    }

    node->left = old_parent;
    old_parent->parent = node;

    this->fixTree();
}

void SplayTree::splayUp(Node* node)
{

}

void SplayTree::insert(int val)
{
    Node* curr_node = root;

    // if root is null
    if (root == nullptr)
    {
        root = new Node(this, val);
        this->fixTree();
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
                this->fixTree();
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
                this->fixTree();
                return;
            }
            else
                curr_node = curr_node->right;
        }
    }
}

void SplayTree::remove(int value)
{
    if (this->root == nullptr)
        return;

    Node* node = this->findNode(value, this->root);

    std::cout << " node found " << node->data << '\n';
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
