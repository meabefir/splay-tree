#include "Button.h"
#include "Mouse.h"
#include "FontManager.h"

Button::Button(sf::Vector2f pos, sf::Vector2f size,
	sf::Font* font, std::string text, int character_size,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(pos);
	this->shape.setSize(size);

	if (font == nullptr)
		this->font = &FontManager::currentFont;
	else
		this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setOutlineColor(sf::Color::Black);
	this->text.setOutlineThickness(1.f);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + this->shape.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + this->shape.getSize().y / 2.f - this->text.getGlobalBounds().height
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{

}

//accessors 

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_PRESSED)
		return true;
	return false;
}


//functions 

void Button::update()
{
	// update the booleans for hover and pressed
	sf::Vector2f mousePos(Mouse::mousePosWindow.x, Mouse::mousePosWindow.y);

	// idle
	this->buttonState = BTN_IDLE;

	// hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_ACTIVE;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			this->buttonState = BTN_HELD;
		// pressed
		if (Mouse::stillClick)
		{
			this->buttonState = BTN_PRESSED;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->hoverColor);
		break;
	case BTN_PRESSED:
		this->shape.setFillColor(this->activeColor);
		break;
	case BTN_HELD:
		this->shape.setFillColor(this->activeColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::draw(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

