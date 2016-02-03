#pragma once
#include <SFML/Graphics.hpp>
class World : public sf::Drawable, public sf::Transformable
{
public:
	World(std::string backgroundTile, sf::Vector2i size);
	~World() = default;

	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::FloatRect	getBounds();

private:
	sf::Texture backgroundTexture, m_seaTexture;
	sf::Sprite	backgroundSprite;
	sf::VertexArray m_sea;
	mutable sf::Shader m_waterEffect;
	sf::Clock m_shaderClock;
};

