#include "../includes/Player.h"
#include <cmath>

Player::Player() {
    // Create the player's ship shape (a triangle)
    shape.setPointCount(3);
    shape.setPoint(0, sf::Vector2f(20, 0));
    shape.setPoint(1, sf::Vector2f(-10, -10));
    shape.setPoint(2, sf::Vector2f(-10, 10));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1);
    
    rotationSpeed = 3.f;
    movementSpeed = 0.1f;
    invincibilityDuration = 3.f;    // 3 sec of invincibility 
    invincible = false;

    reset(); // Set initial position and velocity
}

void Player::reset() {
    shape.setPosition(400, 300); // Start in the center of the screen
    shape.setRotation(-90.f);
    velocity = sf::Vector2f(0.f, 0.f);
    invincible = true;
    invincibilityClock.restart();
}

void Player::handleInput() {
    // Rotate left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        shape.rotate(-rotationSpeed);
    }
    // Rotate right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        shape.rotate(rotationSpeed);
    }
    // Move forward
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        float angle = shape.getRotation() * 3.14159f / 180.f;
        velocity.x += cos(angle) * movementSpeed;
        velocity.y += sin(angle) * movementSpeed;
    }
}

void Player::update() {

    // Check if invibility has worn off 
    if (invincible && invincibilityClock.getElapsedTime().asSeconds() > invincibilityDuration) {
        invincible = false;
    }

    // Update the player's position
    shape.move(velocity);

    // Screen wrapping
    sf::Vector2f pos = shape.getPosition();
    if (pos.x < 0) pos.x = 800;
    if (pos.x > 800) pos.x = 0;
    if (pos.y < 0) pos.y = 600;
    if (pos.y > 600) pos.y = 0;
    shape.setPosition(pos);

    // Apply some friction
    velocity *= 0.99f;
}

void Player::draw(sf::RenderWindow& window) {

    if (invincible) {
        if (fmod(invincibilityClock.getElapsedTime().asSeconds(), 0.2f) < 0.1f) {
            return;
        }
    }
    window.draw(shape);
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}

float Player::getRotation() const {
    return shape.getRotation();
}

sf::FloatRect Player::getBounds() const {
    return shape.getGlobalBounds();
}

bool Player::isInvincible() const {
    return invincible;
}

void Player::drawLife(sf::RenderWindow& window, sf::Vector2f position) {
    sf::ConvexShape lifeShape = shape;
    lifeShape.setRotation(-90.f);
    lifeShape.setScale(0.7f, 0.7f);
    lifeShape.setPosition(position);
    window.draw(lifeShape);
}
