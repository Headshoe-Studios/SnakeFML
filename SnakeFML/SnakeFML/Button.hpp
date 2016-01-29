#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

class Button : public sf::Sprite
{
public:
	Button(std::function<void()> clickCallback, std::string buttonGraphic);
	~Button() = default;
	
	bool pressed(const sf::Event& event);

private:
	std::function<void()>	m_clickCallback;
	sf::Texture				m_graphicTexture;
};