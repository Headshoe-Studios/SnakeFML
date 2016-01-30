#include "World.hpp"



World::World(std::string backgroundTile, sf::Vector2i size)
{
	backgroundTexture.loadFromFile(backgroundTile);
	backgroundTexture.setRepeated(true);
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setTextureRect({ 0,0,size.x,size.y }); //because tiled texture
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(backgroundSprite);
}

sf::FloatRect	World::getBounds()
{
	return backgroundSprite.getGlobalBounds();
}
