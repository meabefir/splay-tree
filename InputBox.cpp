#include "InputBox.h"
#include "FontManager.h"
#include "Mouse.h"

InputBox::InputBox(sf::Vector2f pos, sf::Vector2f size, 
	sf::Color backgroungDefaultColor, sf::Color backgroundActiveColor, 
	sf::Color outlineColor, sf::Color outlineFocusedColor,
	int characterLimit, int char_size):
	backgroungDefaultColor(backgroungDefaultColor), backgroundActiveColor(backgroundActiveColor),
	outlineColor(outlineColor), outlineFocusedColor(outlineFocusedColor)
{
	this->inFocus = false;
	this->characterLimit = characterLimit;
	this->input_state = INP_IDLE;

	int outline_thickness = 5;

	// shape
	this->shape.setSize(size - sf::Vector2f(outline_thickness*2, outline_thickness*2));
	this->shape.setPosition(pos + sf::Vector2f(outline_thickness, outline_thickness));
	this->shape.setFillColor(this->backgroungDefaultColor);
	this->shape.setOutlineThickness(outline_thickness);
	this->shape.setOutlineColor(this->outlineColor);
	
	// text
	this->textRender.setFont(FontManager::currentFont);
	this->textRender.setCharacterSize(char_size);
	this->textRender.setFillColor(sf::Color::White);
	this->textRender.setOutlineThickness(2.f);
	this->textRender.setOutlineColor(sf::Color::Black);
	// simulate size
	/*this->textRender.setString("0");
	this->textRender.setOrigin(0.f, this->textRender.getGlobalBounds().height / 2.f);
	this->textRender.setString("");
	this->textRender.setPosition(this->shape.getPosition().x + 5.f, this->shape.getPosition().y + this->shape.getSize().y / 2.f);*/
}

InputBox::~InputBox()
{
}

bool InputBox::isPressed()
{
	return false;
}

void InputBox::setFocus(bool b)
{
	if (b)
		this->shape.setOutlineColor(this->outlineFocusedColor);
	else
		this->shape.setOutlineColor(this->outlineColor);
	this->inFocus = b;
}

std::string InputBox::getText()
{
	return this->text;
}

void InputBox::setText(std::string s)
{
	if (this->text.size() >= this->characterLimit && !(s.size() < this->text.size()))
		return;
	this->text = s;
	this->textRender.setString(s);

	this->textRender.setOrigin(this->textRender.getLocalBounds().width / 2.f,
								this->textRender.getLocalBounds().height);
	this->textRender.setPosition(this->shape.getPosition().x + this->shape.getSize().x / 2.f,
								this->shape.getPosition().y + this->shape.getSize().y / 2.f);
}

void InputBox::handleEvents(sf::Event e)
{
	if (!this->inFocus)
		return;
	if (e.type == sf::Event::TextEntered)
	{
		if (e.text.unicode == 8)
		{
			if (this->text.size() == 0)
				return;
			this->setText(text.substr(0, this->text.size() - 1));
		}
		else if (e.text.unicode >= 48 && e.text.unicode <= 57)
		{
			this->setText(this->text + static_cast<char>(e.text.unicode));
		}
	}
}



void InputBox::update(const float dt)
{
	sf::Vector2f mouse_pos = sf::Vector2f(Mouse::mousePosWindow);

	if (this->input_state != INP_FOCUSED)
		this->input_state = INP_IDLE;

	if (this->shape.getGlobalBounds().contains(mouse_pos))
	{
		if (this->input_state != INP_FOCUSED)
			this->input_state = INP_HOVERED;

		if (Mouse::stillClick)
		{
			this->input_state = INP_FOCUSED;
		}
	} 
	else if (Mouse::stillClick)
	{
		this->input_state = INP_IDLE;
	}


	switch (this->input_state)
	{
	case INP_IDLE:
		this->shape.setFillColor(this->backgroungDefaultColor);
		this->setFocus(false);
		break;
	case INP_HOVERED:
		this->shape.setFillColor(this->backgroundActiveColor);
		this->setFocus(false);
		break;
	case INP_FOCUSED:
		this->shape.setFillColor(this->backgroundActiveColor);
		this->setFocus(true);
		break;
	default:
		break;
	}
}

void InputBox::draw(sf::RenderTarget* target, sf::View* UIView)
{
	target->draw(this->shape);
	target->draw(this->textRender);
}
