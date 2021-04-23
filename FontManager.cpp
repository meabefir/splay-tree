#include "FontManager.h"

sf::Font FontManager::currentFont;

void FontManager::loadFont(std::string name)
{
	if (name == "")
		FontManager::currentFont.loadFromFile("Fonts/Dosis-Light.ttf");
	else
		FontManager::currentFont.loadFromFile("Fonts/" + name + ".ttf");

	std::cout << " Font loaded...\n";
}
