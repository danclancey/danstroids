#pragma once
#include <SFML/Graphics.hpp>

enum class AsteroidSize { LARGE, MEDIUM, SMALL };

class Asteroid {
public:
    Asteroid(AsteroidSize size, sf::Vector2f position);

    void update();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

    AsteroidSize getSize() const;
    sf::Vector2f getPosition() const;

private:
    sf::ConvexShape shape;
    sf::Vector2f velocity;
    AsteroidSize size;
};
