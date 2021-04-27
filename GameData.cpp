#include "GameData.h"

sf::Vector2f GameData::windowSize = sf::Vector2f();

float GameData::transitionDuration = 400.f;

void GameData::setWindowSize(sf::Vector2f size)
{
	GameData::windowSize = size;
}
