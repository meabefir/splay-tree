#include "SplayTree.h"


SplayTree::SplayTree()
{
  
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

Node* SplayTree::findNode(int value, Node* curr_node, Node* parent)
{
    if (this->root == nullptr)
        return nullptr;

    if (curr_node == nullptr)
    {
        this->splay(parent);
        return parent;
    }

    if (curr_node->data == value)
    {
        this->splay(curr_node);
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

Node* SplayTree::findNodeWithoutFix(int value, Node* curr_node, Node* parent)
{
    if (this->root == nullptr)
        return nullptr;

    if (curr_node == nullptr)
    {
        return parent;
    }

    if (curr_node->data == value)
    {
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

void SplayTree::splay(Node* node) 
{
    // if node is root do nothing
    if (node == this->root)
        return;
    // if node is child of root
    if (node->parent == this->root)
    {
        this->rotate(node);
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
            this->rotate(node);
            //this->rotate(node->parent);
            this->splay(node);
        }
        else
        {
            this->rotate(node->parent);
            //this->rotate(node);
            this->splay(node);
        }
    }
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
                Node* new_node = new Node(this, curr_node, val);
                curr_node->left = new_node;
                this->splay(new_node);
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
                Node* new_node = new Node(this, curr_node, val);
                curr_node->right = new_node;
                this->splay(new_node);
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

    if (node->data == value)
    {
        // no longer splaying here, we always splay when searching
        // now we remove the root
        if (this->root->left != nullptr)
        {
            if (this->root->left->right == nullptr)
            {
                // we just make left the root and connect its right child to the old right child of the old root
                this->root->left->right = this->root->right;
                if (this->root->right != nullptr)
                    this->root->right->parent = this->root->left;
                Node* old_root = this->root;
                this->root = this->root->left;
                this->root->parent = nullptr;
                delete old_root;
            }
            else
            {
                // store the right subtree
                Node* right_subtree = this->root->right;
                right_subtree->parent = nullptr;
                this->root->right = nullptr;
                // set the root to be the left subtree
                Node* old_root = this->root;
                this->root = this->root->left;
                this->root->parent = nullptr;
                delete old_root;
                // we make the root of the left subtree its biggets element and then we make it the root of the tree
                Node* biggest_in_left_subtree = this->getBiggestInSubtree(this->root);
                // we splay the biggest element we found in the subtree, so now the root wont have a right child
                this->splay(biggest_in_left_subtree);
                this->root->right = right_subtree;
                right_subtree->parent = this->root;
            }
        }
        else
        {
            if (this->root->right != nullptr)
            {
                // make right subtree the root
                this->root = this->root->right;
                delete this->root->parent;
                this->root->parent = nullptr;
            }
            else
            {
                // root had no children, we just remove it
                delete this->root;
                this->root = nullptr;
            }
        }
    }
    else
    {
        // we didnt find the value we looked for, we just splay the closest node
        this->splay(node);
    }

    this->fixTree();
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

Node* SplayTree::getSuccessor(Node* node)
{
    if (node == nullptr)
        return nullptr;
    if (node->right != nullptr)
    {
        Node* curr_node = node->right;
        while (curr_node->left != nullptr)
            curr_node = curr_node->left;
        return curr_node;
    }
    else
    {
        Node* curr_node = node;
        while (curr_node->parent != nullptr)
        {
            if (curr_node->data >= node->data)
                return curr_node;
            curr_node = curr_node->parent;
        }
        return curr_node;
    }
}

Node* SplayTree::getPredecessor(Node* node)
{
    if (node == nullptr)
        return nullptr;
    if (node->left != nullptr)
    {
        Node* curr_node = node->left;
        while (curr_node->right != nullptr)
            curr_node = curr_node->right;
        return curr_node;
    }
    else
    {
        Node* curr_node = node;
        while (curr_node->parent != nullptr)
        {
            if (curr_node->data <= node->data)
                return curr_node;
            curr_node = curr_node->parent;
        }
        return curr_node;
    }
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

Node* SplayTree::getBiggestInSubtree(Node* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    Node* curr = node;
    while (curr->right != nullptr)
    {
        curr = curr->right;
    }
    return curr;
}

void SplayTree::update(const float dt)
{
    if (this->root != nullptr)
        this->root->update(dt);
}

void SplayTree::draw(sf::RenderTarget* target)
{
    if (this->root != nullptr)
        this->root->draw(target);
}
