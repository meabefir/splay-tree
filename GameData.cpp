#include "GameData.h"

sf::Vector2f GameData::windowSize = sf::Vector2f();

float GameData::transitionDuration = 200.f;

void GameData::setWindowSize(sf::Vector2f size)
{
	GameData::windowSize = size;
}
