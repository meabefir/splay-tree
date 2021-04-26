#include "NodeHighlight.h"
#include "Node.h"

float NodeHighlight::totalTime = GameData::transitionDuration;

float NodeHighlight::outlineThickness = 4.f;

sf::Color NodeHighlight::outlineColor = sf::Color::Red;

NodeHighlight::NodeHighlight(Node* node):
	node(node), running(false), currTime(0.f)
{
	this->shape.setRadius(this->node->shape.getRadius() - this->node->shape.getOutlineThickness());
	this->shape.setOrigin(this->shape.getRadius() + this->node->shape.getOutlineThickness(), this->shape.getRadius() + this->node->shape.getOutlineThickness());
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setOutlineColor(NodeHighlight::outlineColor);
	this->shape.setOutlineThickness(NodeHighlight::outlineThickness);
}

NodeHighlight::~NodeHighlight()
{
}

void NodeHighlight::start()
{
	this->running = true;
}

void NodeHighlight::stop()
{
	this->running = false;
	this->currTime = 0.f;
}

void NodeHighlight::update(const float dt)
{
	if (this->running)
	{
		this->currTime += dt;
		if (this->currTime > NodeHighlight::totalTime)
		{
			this->stop();
		}
	}
}

void NodeHighlight::draw(sf::RenderTarget* target)
{
	if (this->running)
	{
		this->shape.setPosition(this->node->shape.getPosition());
		target->draw(this->shape);
	}
}
