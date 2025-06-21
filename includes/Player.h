#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    void handleInput();
    void update();
    void draw(sf::RenderWindow& window);
    void reset();

    sf::Vector2f getPosition() const;
    float getRotation() const;
    sf::FloatRect getBounds() const;

    bool isInvincible() const;
    void drawLife(sf::RenderWindow& window, sf::Vector2f position);

private:
    sf::ConvexShape shape;
    sf::Vector2f velocity;
    float rotationSpeed;
    float movementSpeed;

    bool invincible;
    sf::Clock invincibilityClock;
    float invincibilityDuration;
};
