#include "../includes/Bullet.h"
#include <cmath>

Bullet::Bullet(sf::Vector2f position, float angle) {
    shape.setRadius(3.f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(position);

    maxSpeed = 8.f;
    velocity.x = std::cos(angle * 3.14159f / 180.f) * maxSpeed;
    velocity.y = std::sin(angle * 3.14159f / 180.f) * maxSpeed;
}

void Bullet::update() {
    shape.move(velocity);
}

void Bullet::draw(sf::RenderWindow& window) {
     window.draw(shape);
}

sf::Vector2f Bullet::getPosition() const {
    return shape.getPosition();
}

sf::FloatRect Bullet::getBounds() const {
    return shape.getGlobalBounds();
}
