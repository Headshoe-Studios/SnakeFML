#include "Button.h"


Button::Button(std::function<void()> t_clickCallback) : clickCallback(t_clickCallback) {

}

void Button::processEvent(const sf::Event& event) {
	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		/*
			Simple check to see whether the button was clicked.
			MapPixelToCoords is not required since the GUI should be view independent (Potential STC)
			*/
		if (shape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			clickCallback();
		}
	default:
		break;
	}
}
