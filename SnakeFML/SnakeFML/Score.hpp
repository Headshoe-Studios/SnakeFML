#pragma once

#include <SFML/Graphics.hpp>

class Score : public sf::Drawable
{
public:
	Score(std::string fontFile);
	~Score() = default;

	void update(int currentScore);

private:
	sf::Font			m_displayFont;
	sf::Text			m_displayText;

	virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

