#include "GameData.h"

sf::Vector2f GameData::windowSize = sf::Vector2f();

void GameData::setWindowSize(sf::Vector2f size)
{
	GameData::windowSize = size;
}
