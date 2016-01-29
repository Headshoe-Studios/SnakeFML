#pragma once

#include <SFML/Graphics.hpp>

#include "Button.hpp"

class Menu : public sf::Drawable
{
public:
	Menu(sf::RenderWindow& window, std::initializer_list<Button> buttons);
	~Menu() = default;

	void handleEvent(const sf::Event& event);

private:
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Button>	m_buttons;
};

