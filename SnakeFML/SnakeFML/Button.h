#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
	Button(std::function<void()> t_clickCallback);

	void processEvent(const sf::Event& event);
	
	std::function<void()> clickCallback;
	sf::RectangleShape shape;

private:


};