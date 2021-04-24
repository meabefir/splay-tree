#include "InputButton.h"

InputButton::InputButton(sf::Vector2f pos, sf::Vector2f size,
	std::string button_text, int button_char_size,
	sf::Color input_back, sf::Color input_back_active,
	sf::Color input_outline, sf::Color input_outline_active,
	sf::Color button_idle, sf::Color button_hover, sf::Color button_active) :
	inputBox(pos, size, input_back, input_back_active, input_outline, input_outline_active),
	button(pos + sf::Vector2f(size.x, 0.f), size, nullptr, button_text, button_char_size)
{
}

InputButton::~InputButton()
{
}

bool InputButton::isPressed()
{
	return this->button.isPressed();
}

std::string InputButton::getInput()
{
	return this->inputBox.getText();
}

void InputButton::resetInput()
{
	this->inputBox.setText("");
}

void InputButton::handleEvents(sf::Event e)
{
	this->inputBox.handleEvents(e);
}



void InputButton::update(const float dt)
{
	this->inputBox.update(dt);
	this->button.update();
}

void InputButton::draw(sf::RenderTarget* target, sf::View* UIView)
{
	// save the window view
	sf::View default_view = target->getView();
	// set the ui view
	target->setView(*UIView);

	this->inputBox.draw(target, UIView);
	this->button.draw(target);

	// set back the default view
	target->setView(default_view);
}
