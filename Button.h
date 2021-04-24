#pragma once

#include "State.h"

enum button_states { BTN_IDLE = 0, BTN_PRESSED, BTN_ACTIVE, BTN_HELD };

class Button
{
private:
	short unsigned buttonState;
	bool pressed;
	bool hover;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;



public:
	Button(sf::Vector2f pos, sf::Vector2f size,
		sf::Font* font = nullptr, std::string text = "", int character_size = 40,
		sf::Color idleColor = sf::Color::Green, sf::Color hoverColor = sf::Color::Blue, 
		sf::Color activeColor = sf::Color::Red);
	~Button();

	// accessors
	const bool isPressed() const;

	// functions 
	void update();
	void draw(sf::RenderTarget* target);

};

