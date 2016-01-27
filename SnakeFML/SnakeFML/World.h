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
	sf::Texture backgroundTexture;
	sf::Sprite	backgroundSprite;
};

