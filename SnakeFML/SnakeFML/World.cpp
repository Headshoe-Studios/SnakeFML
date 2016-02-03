#include "World.hpp"

World::World(std::string backgroundTile, sf::Vector2i size)
{
	backgroundTexture.loadFromFile(backgroundTile);
	backgroundTexture.setRepeated(true);
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setTextureRect({ 0,0,size.x,size.y }); //because tiled texture	

	m_seaTexture.loadFromFile("SeaTile.png");
	m_seaTexture.setRepeated(true);	
	m_sea.setTexture(m_seaTexture);
	m_sea.setTextureRect({0,0,2*size.x, 2*size.y});
	m_sea.setPosition(backgroundSprite.getPosition().x-size.x/2.f,
					  backgroundSprite.getPosition().y-size.y/2.f);
	
	m_waterEffect.loadFromFile("WaterEffect.frag", sf::Shader::Fragment);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.shader = &m_waterEffect;
	target.draw(m_sea, states);
	target.draw(backgroundSprite);
}

sf::FloatRect	World::getBounds()
{
	return backgroundSprite.getGlobalBounds();
}
