#include "Button.hpp"


Button::Button(std::function<void()> clickCallback, std::string buttonGraphic) :
	m_clickCallback(clickCallback)
{
	m_graphicTexture.loadFromFile(buttonGraphic);
	setTexture(m_graphicTexture, true);
}

bool Button::pressed(const sf::Event& event)
{
	switch (event.type) 
	{
	case sf::Event::MouseButtonPressed:
		if (getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) 
		{
			m_clickCallback();
			return true;
		}
	default:
		break;
	}
}

