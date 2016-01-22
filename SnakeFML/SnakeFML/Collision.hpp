#include <SFML/Graphics.hpp>

namespace Collision
{
	bool checkForCollision(sf::Vector2f objPos1, sf::Vector2f objPos2, int objSize1, int objSize2)
	{ //using the 2 objects positions determine collison
		float a = objPos2.x - objPos1.x;
		float b = objPos2.y - objPos1.y;
		float c = sqrt(pow(a, 2) + pow(b, 2));
		if(c <= objSize1 + objSize2){
			return true;
		}
		return false;
	}
};