#pragma once
#include "State.h"
#include "Component.h"

enum input_states  {INP_IDLE, INP_HOVERED, INP_FOCUSED};

class InputBox: public Component
{
private:
	short unsigned input_state;

	sf::RectangleShape shape;
	sf::Text textRender;
	std::string text;

	int characterLimit;
	sf::Color backgroungDefaultColor;
	sf::Color backgroundActiveColor;
	sf::Color outlineColor;
	sf::Color outlineFocusedColor;

	bool inFocus;

public:
	InputBox(sf::Vector2f pos, sf::Vector2f size, 
		sf::Color backgroungDefaultColor = sf::Color(255,255,255,180),sf::Color backgroundActiveColor = sf::Color(255,0,0,180), 
		sf::Color outlineColor = sf::Color(0,0,0), sf::Color outlineFocusedColor = sf::Color::Green,
		int characterLimit = 4, int char_size = 30);
	~InputBox();

	bool isPressed();
	void setFocus(bool);

	std::string getText();
	void setText(std::string);

	void handleEvents(sf::Event e);
	void update(const float dt);
	void draw(sf::RenderTarget* target, sf::View* UIView);

	friend class InputButton;
};

