#include "../includes/Asteroid.h"
#include <cstdlib>
#include <cmath>

Asteroid::Asteroid(AsteroidSize size, sf::Vector2f position) : size(size) {
    float radius;
    int pointCount = 7 + (rand() % 5);
    shape.setPointCount(pointCount);

    switch (size) {
        case AsteroidSize::LARGE:
            radius = 35.f;
            break;
        case AsteroidSize::MEDIUM:
            radius = 20.f;
            break;
        case AsteroidSize::SMALL:
            radius = 10.f;
            break;
    }

    for (int i = 0; i < pointCount; ++i) {
        float angle = (i * 360.f / pointCount) * 3.14159f / 180.f;
        float randomRadius = radius + (rand() % static_cast<int>(radius/2.f)) - (radius/4.f);
        shape.setPoint(i, sf::Vector2f(cos(angle) * randomRadius, sin(angle) * randomRadius));
    }

    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1.5f);
    shape.setPosition(position);

    // Give it a random velocity
    float angle = (rand() % 360) * 3.14159f / 180.f;
    float speed = 1.f + (rand() % 101) / 100.f; // 1.0 to 2.0
    velocity = sf::Vector2f(cos(angle) * speed, sin(angle) * speed);
}

void Asteroid::update() {
    shape.move(velocity);
    shape.rotate(0.5f); // Make them spin

    // Screen wrapping
    sf::Vector2f pos = shape.getPosition();
    if (pos.x < -30) pos.x = 830;
    if (pos.x > 830) pos.x = -30;
    if (pos.y < -30) pos.y = 630;
    if (pos.y > 630) pos.y = -30;
    shape.setPosition(pos);
}

void Asteroid::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Asteroid::getBounds() const {
    return shape.getGlobalBounds();
}

AsteroidSize Asteroid::getSize() const {
    return size;
}

sf::Vector2f Asteroid::getPosition() const {
    return shape.getPosition();
}
