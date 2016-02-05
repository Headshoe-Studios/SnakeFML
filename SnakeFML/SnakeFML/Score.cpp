#include "Score.hpp"
#include <fstream>

Score::Score(std::string fontFile)
{
	m_displayFont.loadFromFile(fontFile);
	m_displayText.setFont(m_displayFont);
	m_highScoreText.setFont(m_displayFont);

	//check if a saved score is present
	std::ifstream saveFile("highScore.snake");
	if (saveFile.good())
	{
		//read the saved score
		saveFile >> m_highScore;
		m_highScoreText.setString("High Score: " + std::to_string(m_highScore));

		//put the current score below the high score
		auto highScoreBounds(m_highScoreText.getGlobalBounds());
		sf::Vector2f position(highScoreBounds.left, highScoreBounds.top + highScoreBounds.height);
		m_displayText.setPosition(position);
	}
}

void	Score::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_displayText);
	target.draw(m_highScoreText);
}

void	Score::update(int currentScore)
{
	m_displayText.setString("Current Score: " + std::to_string(currentScore));

	//check if it's a new high score
	if (currentScore > m_highScore)
	{
		m_highScore = currentScore;
		m_highScoreText.setString("High Score: " + std::to_string(currentScore));

		//put the current score below the high score
		auto highScoreBounds(m_highScoreText.getGlobalBounds());
		sf::Vector2f position(highScoreBounds.left, highScoreBounds.top + highScoreBounds.height);
		m_displayText.setPosition(position);

		//store it in the save file
		std::ofstream saveFile("highScore.snake");
		saveFile << m_highScore;
		saveFile.close();
	}
}