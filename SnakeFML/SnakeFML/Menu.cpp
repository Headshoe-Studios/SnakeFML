#include "Menu.hpp"



Menu::Menu(sf::RenderWindow& window, std::initializer_list<Button> buttons) :
	m_buttons(buttons)
{
	auto windowSize(window.getSize());
	auto yDistancePerButton(windowSize.y / m_buttons.size());
	auto index(0);
	for (auto& button : m_buttons)
	{
		//origin to center
		auto buttonRect(button.getGlobalBounds());
		button.setOrigin(buttonRect.width / 2, buttonRect.height / 2);

		//position to middle of screen (equal space per button)
		auto yPos(yDistancePerButton * index + yDistancePerButton / 2);
		button.setPosition(static_cast<float>(windowSize.x / 2), static_cast<float>(yPos));
		++index;
	}
}

void	Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& button : m_buttons)
		target.draw(button);
}

void	Menu::handleEvent(const sf::Event& event)
{
	for (auto& button : m_buttons)
	{
		if (button.pressed(event))
			return;
	}
}