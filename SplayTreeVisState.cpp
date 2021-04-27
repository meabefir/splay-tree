#include "SplayTreeVisState.h"
#include "Mouse.h"
#include <ctime>
#include "PauseState.h"

SplayTreeVisState::SplayTreeVisState(sf::RenderWindow* window, std::stack<State*>* states): 
	State(window, states)
{
	srand(time(0));
	splayTree = new SplayTree();

	this->components["INSERT_INPUT"] = new InputButton(sf::Vector2f(10.f, 10.f), sf::Vector2f(100.f, 40.f),"INSERT");
	this->components["DELETE_INPUT"] = new InputButton(sf::Vector2f(210.f, 10.f), sf::Vector2f(100.f, 40.f),"DELETE");
	this->components["ROTATION_INPUT"] = new InputButton(sf::Vector2f(410.f, 10.f), sf::Vector2f(100.f, 40.f),"ROTATE");
	this->components["FIND_INPUT"] = new InputButton(sf::Vector2f(610.f, 10.f), sf::Vector2f(100.f, 40.f),"FIND");

	this->components["SUCCESSOR_INPUT"] = new InputButton(sf::Vector2f(10.f, 60.f), sf::Vector2f(100.f, 40.f),"SUCC");
	this->components["PREDECESSOR_INPUT"] = new InputButton(sf::Vector2f(210.f, 60.f), sf::Vector2f(100.f, 40.f),"PRED");

	this->components["FIND_COMPONENT"] = new FindComponent(&this->components, this->splayTree);
	this->components["ROTATE_COMPONENT"] = new RotateComponent(&this->components, this->splayTree);
}

SplayTreeVisState::~SplayTreeVisState()
{
	std::cout << " Deleting splay tree\n";
	delete this->splayTree;
}

void SplayTreeVisState::resetTree()
{
	delete this->splayTree;
	this->splayTree = new SplayTree();
	
	// reset references to find and rotate comp
	auto find_comp = dynamic_cast<FindComponent*>(this->components["FIND_COMPONENT"]);
	find_comp->setTree(this->splayTree);

	auto rotate_comp = dynamic_cast<RotateComponent*>(this->components["ROTATE_COMPONENT"]);
	rotate_comp->setTree(this->splayTree);
}

void SplayTreeVisState::handleEvents(sf::Event e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		if (e.key.code == sf::Keyboard::Key::R)
			this->resetTree();
	}

	if (e.type == sf::Event::KeyReleased)
	{
		if (e.key.code == sf::Keyboard::Key::Q)
			this->splayTree->insert(std::rand() % 10000);
		if (e.key.code == sf::Keyboard::Escape)
			this->states->push(new PauseState(this->window, this->states));
	}

	// uncomment this after you make ui elemets unaffected by panning
	if (e.type == sf::Event::MouseMoved)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			sf::View curr_view = this->window->getView();
			curr_view.move(-Mouse::relativePos);
			this->window->setView(curr_view);
		}
	}

	// if scroll
	if (e.type == sf::Event::MouseWheelMoved)
	{
		// zoom out
		if (e.mouseWheel.delta == -1)
		{
			sf::View curr_view = this->window->getView();
			curr_view.zoom(1.1f);
			Mouse::zoom = Mouse::zoom * 1.1f;
			this->window->setView(curr_view);
		}
		else if (e.mouseWheel.delta == 1 && Mouse::zoom >= .5f) // zoom in
		{
			sf::View curr_view = this->window->getView();
			curr_view.zoom(.9f);
			Mouse::zoom = Mouse::zoom * .9f;
			this->window->setView(curr_view);
		}
	}

	State::handleEvents(e);
}

void SplayTreeVisState::update(const float dt)
{
	// update components
	State::update(dt);

	// update splay tree
	this->splayTree->update(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		this->splayTree->insert(std::rand() % 10000);
	}
	
	for (auto& comp : this->components)
	{
		InputButton* inp= dynamic_cast<InputButton*>(comp.second);
		if (inp != nullptr && inp->isPressed())
			if (inp->getInput() != "")
			{
				if (comp.first == "INSERT_INPUT")
				{
					if (this->splayTree->getRoot() == nullptr)
						this->splayTree->insert(std::stoi(inp->getInput()));
					else
					{
						auto find_comp = dynamic_cast<FindComponent*>(this->components["FIND_COMPONENT"]);
						find_comp->setMode("insert");
						find_comp->setNewNodeVal(std::stoi(inp->getInput()));
						find_comp->findNode(std::stoi(inp->getInput()), this->splayTree->getRoot());
					}
				}
				else if (comp.first == "DELETE_INPUT")
					this->splayTree->remove(std::stoi(inp->getInput()));
				else if (comp.first == "ROTATION_INPUT")
				{
					auto rotate_comp = dynamic_cast<RotateComponent*>(this->components["ROTATE_COMPONENT"]);
					auto found = rotate_comp->findNode(std::stoi(inp->getInput()), this->splayTree->getRoot());
					rotate_comp->splay(found);
				}
				else if (comp.first == "FIND_INPUT")
				{
					if (this->splayTree->getRoot() != nullptr)
					{
						auto find_comp = dynamic_cast<FindComponent*>(this->components["FIND_COMPONENT"]);
						find_comp->findNode(std::stoi(inp->getInput()), this->splayTree->getRoot());
					}
				}
				else if (comp.first == "SUCCESSOR_INPUT")
				{
					Node* found = splayTree->findNode(std::stoi(inp->getInput()), this->splayTree->getRoot());
					if (found != nullptr && found->getData() >= std::stoi(inp->getInput()))
					{
						found->highlight();
					}
					else
					{
						found = this->splayTree->getSuccessor(found);
						found->highlight();
					}
				}
				else if (comp.first == "PREDECESSOR_INPUT")
				{
					Node* found = splayTree->findNode(std::stoi(inp->getInput()), this->splayTree->getRoot());
					if (found != nullptr && found->getData() <= std::stoi(inp->getInput()))
					{
						found->highlight();
					}
					else
					{
						found = this->splayTree->getPredecessor(found);
						found->highlight();
					}
				}
				inp->resetInput();
			}
	}
}

void SplayTreeVisState::draw(sf::RenderTarget* target, sf::View* UIView)
{
	this->splayTree->draw(target);

	State::draw(target, UIView);
}
