#include "Node.h"
#include "SplayTree.h"

// statics
float Node::radius = 40.f;

float Node::outlineThickness = 3.f;

float Node::yStart = 50.f;

float Node::yMargin = 100.f;

float Node::xMargin = 10.f;

sf::Color Node::fillColor = sf::Color(255, 183, 3);

Node::Node(SplayTree* tree, Node* parent, int data):
	tree(tree), parent(parent), data(data), left(nullptr), right(nullptr), vertexArray(sf::LinesStrip, 3)
{
	this->init();
}

Node::Node(SplayTree* tree, int data):
	tree(tree), data(data), parent(nullptr), left(nullptr), right(nullptr), vertexArray(sf::LinesStrip, 3)
{
	this->init();
}

Node::~Node()
{
	std::cout << " Node " << this << " deleted\n";
	this->parent = nullptr;
	delete left;
	this->left = nullptr;
	delete right;
	this->right = nullptr;
}

void Node::setPosition(sf::Vector2f pos)
{
	this->shape.setPosition(pos);
	this->textRender.setPosition(pos);
}

sf::Vector2f Node::getPosition()
{
	return this->shape.getPosition();
}

unsigned Node::getLevel()
{
	if (this->parent == nullptr)
		return 0;
	unsigned lvl = 0;
	Node* curr_parent = this->parent;
	while (curr_parent != nullptr)
	{
		curr_parent = curr_parent->parent;
		lvl++;
	}
	return lvl;
}

unsigned Node::getIndexInLevel()
{
	if (this->parent == nullptr)
		return 0;

	Node* curr_node = this;
	Node* curr_parent = this->parent;

	std::stack<int> dir;

	while (curr_parent != nullptr)
	{
		if (curr_parent->left == curr_node)
			dir.push(-1);
		else if (curr_parent->right == curr_node)
			dir.push(1);

		curr_node = curr_parent;
		curr_parent = curr_parent->parent;
	}
	int index = 0;
	while (dir.size())
	{
		if (dir.top() == -1)
			index = index * 2 + 1;
		else
			index = index * 2 + 2;
		dir.pop();
	}
	
	int log = std::log2(index + 1);
	index = index + 1 - std::pow(2, log);
	return index;
}

void Node::init()
{
	this->maxLeft = 1;
	this->maxRight = 1;

	// shape stuff
	this->shape.setRadius(Node::radius - Node::outlineThickness);
	this->shape.setFillColor(Node::fillColor);
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setOutlineThickness(Node::outlineThickness);
	this->shape.setPosition(sf::Vector2f());
	this->shape.setOrigin(Node::radius, Node::radius);

	// text stuff
	this->textRender.setFont(FontManager::currentFont);
	this->textRender.setFillColor(sf::Color::White);
	this->textRender.setOutlineColor(sf::Color::Black);
	this->textRender.setCharacterSize(Node::radius);
	this->textRender.setOutlineThickness(2.f);
	this->textRender.setString(std::to_string(this->data));
	this->textRender.setOrigin(this->textRender.getGlobalBounds().width / 2.f,
								this->textRender.getGlobalBounds().height);

	//// temp
	//this->maxLeftTextRender.setFont(FontManager::currentFont);
	//this->maxLeftTextRender.setFillColor(sf::Color::Black);
	//this->maxLeftTextRender.setOrigin(this->textRender.getGlobalBounds().width / 2.f,
	//this->maxLeftTextRender.getGlobalBounds().height);
	//this->maxLeftTextRender.setString("aa");

	//this->maxRightTextRender.setFont(FontManager::currentFont);
	//this->maxRightTextRender.setFillColor(sf::Color::Black);
	//this->maxRightTextRender.setOrigin(this->textRender.getGlobalBounds().width / 2.f,
	//this->maxRightTextRender.getGlobalBounds().height);
	//this->maxRightTextRender.setString("aa");
	/// temp

	// set line color
	for (int i = 0; i < 3; i++)
		this->vertexArray[i].color = sf::Color(33, 158, 188);
}

void Node::draw(sf::RenderTarget* target)
{
	// do the drawing stuff
	target->draw(this->shape);
	target->draw(this->textRender);

	/*target->draw(this->maxLeftTextRender);
	target->draw(this->maxRightTextRender);*/

	// draw and set vertex coords
	if (this->left != nullptr || this->right != nullptr)
	{
		/*this->vertexArray[1].position = this->getPosition();
		this->vertexArray[0].position = this->getPosition();
		this->vertexArray[2].position = this->getPosition();
		if (this->left != nullptr)
			this->vertexArray[0].position = this->left->getPosition();
		if (this->right != nullptr)
			this->vertexArray[2].position = this->right->getPosition();*/
		target->draw(vertexArray);
	}

	// draw children
	if (this->left != nullptr)
		this->left->draw(target);
	if (this->right != nullptr)
		this->right->draw(target);
}

//void Node::rearange(bool is_root)
//{
//	if (is_root)
//	{
//		this->setPosition(sf::Vector2f(GameData::windowSize.x / 2.f, Node::yStart));
//	}
//	else
//	{
//		int level = this->getLevel();
//		int index = this->getIndexInLevel();
//		int max_level = this->tree->getMaxLevel();
//
//		int nodes_on_level = std::pow(2, level);
//		int nodes_on_max_level = std::pow(2, max_level);
//		float space_for_one = (nodes_on_max_level / nodes_on_level) * Node::radius * 2.f + xMargin;
//
//		space_for_one *= .3f;
//
//		index -= nodes_on_level / 2;
//		 
//		sf::Vector2f new_pos;
//		new_pos.x = GameData::windowSize.x / 2.f + index * space_for_one + space_for_one / 2.f;
//		new_pos.y = this->parent->getPosition().y + Node::yMargin;
//
//		this->setPosition(new_pos);
//	}
//
//	if (this->left != nullptr)
//		this->left->rearange();
//	if (this->right != nullptr)
//		this->right->rearange();
//}

void Node::calcMax()
{
	this->maxLeft = 1;
	this->maxRight = 1;

	if (this->left != nullptr)
		this->left->calcMax();

	if (this->right != nullptr)
		this->right->calcMax();

	if (this->left != nullptr)
	{
		this->maxLeft = this->left->maxRight + this->left->maxLeft;
	}

	if (this->right != nullptr)
	{
		this->maxRight = this->right->maxRight + this->right->maxLeft;
	}

	// temp
	/*this->maxLeftTextRender.setString(std::to_string(this->maxLeft));
	this->maxRightTextRender.setString(std::to_string(this->maxRight));*/
}

void Node::applyOffset()
{
	if (this->parent == nullptr)
	{
		this->setPosition(sf::Vector2f(GameData::windowSize.x / 2.f, Node::yStart));
	}
	else
	{
		int level = this->getLevel();
		// if i am a left child
		if (this == this->parent->left)
		{
			sf::Vector2f new_pos;
			new_pos.x = this->parent->getPosition().x - this->maxRight * (Node::radius + xMargin);
			new_pos.y = Node::yStart + level * Node::yMargin;
			this->setPosition(new_pos);

			// update line that connects this to parent
			this->parent->vertexArray[0].position = new_pos;
			if (this->parent->right == nullptr)
				this->parent->vertexArray[2] = this->parent->getPosition();
		}

		// if i am a right child
		else if (this == this->parent->right)
		{
			sf::Vector2f new_pos;
			new_pos.x = this->parent->getPosition().x + this->maxLeft * (Node::radius + xMargin);
			new_pos.y = Node::yStart + level * Node::yMargin;
			this->setPosition(new_pos);

			// update line that connects this to parent
			this->parent->vertexArray[2].position = new_pos;
			if (this->parent->left == nullptr)
				this->parent->vertexArray[0] = this->parent->getPosition();
		}
	}

	this->vertexArray[1].position = this->getPosition();

	//// temp
	//this->maxLeftTextRender.setPosition(this->getPosition() + sf::Vector2f(-10.f, 5.f));
	//this->maxRightTextRender.setPosition(this->getPosition() + sf::Vector2f(10.f, 5.f));

	if (this->left != nullptr)
		this->left->applyOffset();
	if (this->right != nullptr)
		this->right->applyOffset();
}
