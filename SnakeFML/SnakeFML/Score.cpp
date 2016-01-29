#include "Score.hpp"

Score::Score(std::string fontFile)
{
	m_displayFont.loadFromFile(fontFile);
	m_displayText.setFont(m_displayFont);
}

void	Score::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_displayText);
}

void	Score::update(int currentScore)
{
	m_displayText.setString(std::to_string(currentScore));
}