#include "World.hpp"

World::World(std::string backgroundTile, sf::Vector2i size)
{
	//grass
	backgroundTexture.loadFromFile(backgroundTile);
	backgroundTexture.setRepeated(true);
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setTextureRect({ 0,0,size.x,size.y }); //because tiled texture
	
	//sea
	m_seaTexture.loadFromFile("SeaTile.png");
	sf::Vector2f seaTopLeft(backgroundSprite.getPosition().x-size.x/2.f,
							backgroundSprite.getPosition().y-size.y/2.f);
	m_sea.setPrimitiveType(sf::Quads);
	float tileSide = 64.f;
	for (int i=0; i<2*size.x/tileSide; ++i){
		for (int j=0; j<2*size.y/tileSide; ++j){
			m_sea.append(sf::Vertex({seaTopLeft.x+i*tileSide,seaTopLeft.y+j*tileSide},
									{0,0}));
			m_sea.append(sf::Vertex({seaTopLeft.x+(i+1)*tileSide,seaTopLeft.y+j*tileSide},
									{tileSide,0}));
			m_sea.append(sf::Vertex({seaTopLeft.x+(i+1)*tileSide,seaTopLeft.y+(j+1)*tileSide},
									{tileSide,tileSide}));
			m_sea.append(sf::Vertex({seaTopLeft.x+i*tileSide,seaTopLeft.y+(j+1)*tileSide},
									{0,tileSide}));
		}
	}
	
	m_waterEffect.loadFromFile("WaterEffect.frag", sf::Shader::Fragment);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	m_waterEffect.setParameter("time", m_shaderClock.getElapsedTime().asSeconds());	
	states.shader = &m_waterEffect;
	states.texture = &m_seaTexture;
	target.draw(m_sea, states);
	target.draw(backgroundSprite);
}

sf::FloatRect	World::getBounds()
{
	return backgroundSprite.getGlobalBounds();
}
