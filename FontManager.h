#pragma once
#include "State.h"

class FontManager
{
public:
	static sf::Font currentFont;

	static void loadFont(std::string name = "");
};

