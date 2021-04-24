#pragma once
#include "Component.h"
#include "InputBox.h"
#include "Button.h"

class InputButton :
    public Component
{
private:
    InputBox inputBox;
    Button button;

public:
    InputButton(sf::Vector2f pos, sf::Vector2f size,
        std::string button_text, int button_char_size = 30,
        sf::Color input_back = sf::Color(255,255,255,150), sf::Color input_back_active = sf::Color(255,0,0,150), 
        sf::Color input_outline = sf::Color::White, sf::Color input_outline_active = sf::Color::Red,
        sf::Color button_idle = sf::Color::Green, sf::Color button_hover = sf::Color::Blue, sf::Color button_active = sf::Color::Red);
    ~InputButton();

    bool isPressed();
    std::string getInput();
    void resetInput();

    void handleEvents(sf::Event);
    void update(const float dt);
    void draw(sf::RenderTarget*, sf::View*);
};

