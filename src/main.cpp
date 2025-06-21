#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../includes/Player.h"
#include "../includes/Asteroid.h"
#include "../includes/Bullet.h"
#include "../includes/SoundManager.h"
#include "../includes/Menu.h"
#include "../includes/HighScoreManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>

enum class GameState { MainMenu, Playing, HighScores, GameOver, EnteringName };

// Function to reset the game state
void resetGame(Player& player, std::vector<Asteroid>& asteroids, std::vector<Bullet>& bullets, int& score, int& level, int& lives); 
void nextLevel(int level, std::vector<Asteroid>& asteroids, Player& player); 

int main() {
    srand(static_cast<unsigned int>(time(0)));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroids");
    window.setFramerateLimit(60);

    GameState currentState = GameState::MainMenu;
    Menu menu(window.getSize().x, window.getSize().y);
    HighScoreManager highScoreManager;
    SoundManager soundManager;

    sf::Font font;
    if (!font.loadFromFile("../assets/arial.ttf")) {
        std::cerr << "Error loading arial.ttf" << std::endl;
        return 1;
    }

    // Game Objects
    Player player;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;

    // Game Variables 
    int score = 0;
    int level = 1;
    int lives = 3;

    // Text for score and lives 
    sf::Text scoreText, livesText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    scoreText.setFont(font);
    livesText.setFont(font); livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(10, 40);

    // Text for name
    std::string playerName = "";
    sf::Text nameEntryText, promptText;
    promptText.setFont(font);
    promptText.setString("New High Score! Enter Name: ");
    promptText.setCharacterSize(30);
    promptText.setPosition(800 / 2.f - promptText.getLocalBounds().width / 2.f, 200);
    nameEntryText.setFont(font);
    nameEntryText.setCharacterSize(40);
    nameEntryText.setFillColor(sf::Color::Yellow);
    
    sf::Clock shootClock;
    float shootCooldown = 0.3f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
           
            switch(currentState) {
                case GameState::MainMenu:
                    if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Up) menu.MoveUp();
                        if (event.key.code == sf::Keyboard::Down) menu.MoveDown();
                        if (event.key.code == sf::Keyboard::Return) {
                            switch (menu.getPressedItem()) {
                                case 0: // Start game 
                                    resetGame(player, asteroids, bullets, score, level, lives);
                                    currentState = GameState::Playing;
                                    break;
                                case 1: // High scores
                                    currentState = GameState::HighScores;
                                    break;
                                case 2: // Quit
                                    window.close();
                                    break;
                            }
                        }
                    }
                    break;
                case GameState::HighScores:
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                        currentState = GameState::MainMenu;
                    }
                    break;
                case GameState::GameOver:
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
                        currentState = GameState::MainMenu;
                    }
                    break;
                case GameState::EnteringName:
                    if (event.type == sf::Event::TextEntered) {
                        if (event.text.unicode < 128 && event.text.unicode != '\b' && event.text.unicode != '\r' && playerName.length() < 10) {
                            playerName += static_cast<char>(event.text.unicode);
                        } else if (event.text.unicode == '\b' && !playerName.empty()) {
                            playerName.pop_back();
                        }
                    } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && !playerName.empty()) {
                        highScoreManager.addScore(playerName, score);
                        currentState = GameState::HighScores;
                    }
                    break;
                case GameState::Playing:
                    break;
            }
        }

        // -- State specific updating and drawing ---
        window.clear(sf::Color::Black);
        switch(currentState) {
            case GameState::MainMenu:
                menu.draw(window);
                break;
            case GameState::HighScores:
                highScoreManager.draw(window);
                break;
            case GameState::EnteringName:
                {
                    nameEntryText.setString(playerName);
                    nameEntryText.setPosition(800 / 2.f - nameEntryText.getLocalBounds().width / 2.f, 250);
                    window.draw(promptText);
                    window.draw(nameEntryText);
                    break;
                }
            case GameState::GameOver:
            {
                sf::Text gameOverDisplay;
                gameOverDisplay.setFont(font);
                gameOverDisplay.setString("GAME OVER\nPress ENTER to return to menu");
                gameOverDisplay.setCharacterSize(40);
                gameOverDisplay.setFillColor(sf::Color::Red);
                sf::FloatRect bounds = gameOverDisplay.getLocalBounds();
                gameOverDisplay.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
                window.draw(gameOverDisplay);
                break;
            }
            case GameState::Playing:
            {
                // --- Input ---
                player.handleInput();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootClock.getElapsedTime().asSeconds() > shootCooldown) {
                    bullets.push_back(Bullet(player.getPosition(), player.getRotation()));
                    soundManager.play(SoundType::SHOOT);
                    shootClock.restart();
                }

                // --- Update ---
                player.update();
                for (auto& a : asteroids) a.update();
                for (auto& b : bullets) b.update();

                // --- Collisions --- 
                std::vector<Asteroid> newAsteroids;
                for (auto i = asteroids.begin(); i != asteroids.end(); ) {
                    bool asteroidHit = false;
                    for (auto j = bullets.begin(); j != bullets.end(); ) {
                        if (i->getBounds().intersects(j->getBounds())) {
                            soundManager.play(SoundType::ASTEROID_EXPLOSION);
                            if (i->getSize() == AsteroidSize::LARGE) {
                                newAsteroids.push_back(Asteroid(AsteroidSize::MEDIUM, i->getPosition()));
                                newAsteroids.push_back(Asteroid(AsteroidSize::MEDIUM, i->getPosition()));
                                score += 20;
                            } else if (i->getSize() == AsteroidSize::MEDIUM) {
                                newAsteroids.push_back(Asteroid(AsteroidSize::SMALL, i->getPosition()));
                                newAsteroids.push_back(Asteroid(AsteroidSize::SMALL, i->getPosition()));
                                score += 50;
                            } else {
                                score += 100;
                            }
                            j = bullets.erase(j);
                            asteroidHit = true;
                            break;
                        } else {
                            ++j;
                        }
                    }
                    if (asteroidHit) i = asteroids.erase(i); else ++i;
                }
                asteroids.insert(asteroids.end(), newAsteroids.begin(), newAsteroids.end());

                if (!player.isInvincible()) {
                    for (const auto& asteroid : asteroids) {
                        if (player.getBounds().intersects(asteroid.getBounds())) {
                            soundManager.play(SoundType::PLAYER_DEATH);
                            lives--;
                            if (lives > 0) {player.reset(); }
                            else {
                                if(highScoreManager.isHighScore(score)) {
                                    playerName = "";
                                    currentState = GameState::EnteringName;
                                } else {
                                    currentState = GameState::GameOver;
                                }
                            }
                            break;
                        }
                    }
                }
                // --- Cleanup and Leveling ---
                bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b){ return b.getPosition().x < 0 || b.getPosition().x > 800 || b.getPosition().y < 0 || b.getPosition().y > 600; }), bullets.end());
                if (asteroids.empty()) { level++; nextLevel(level, asteroids, player); }

                // --- Draw Gameplay --- 
                player.draw(window);
                for (auto& a : asteroids) a.draw(window);
                for (auto& b : bullets) b.draw(window);
                scoreText.setString("Score: " + std::to_string(score) + "    Level: " + std::to_string(level));;
                window.draw(scoreText);
                for (int i = 0; i < lives; ++i)
                    player.drawLife(window, sf::Vector2f(20 + i * 25, 580));
                break;
            }
        }
        window.display();
    }
    return 0;
}

// --- Helper Function Implementation ---
void resetGame(Player& player, std::vector<Asteroid>& asteroids, std::vector<Bullet>& bullets, int& score, int& level, int& lives) {
    player.reset();
    asteroids.clear();
    bullets.clear();
    score = 0;
    level = 1;
    lives = 3;

    for (int i = 0; i < 3; ++i) {
        float x, y;
        do {
            x = static_cast<float>(rand() % 800);
            y = static_cast<float>(rand() % 600);
        } while (std::sqrt(std::pow(x - player.getPosition().x, 2) + std::pow(y - player.getPosition().y, 2)) < 450.f);

        asteroids.push_back(Asteroid(AsteroidSize::LARGE, sf::Vector2f(x, y)));
    }
}

void nextLevel(int level, std::vector<Asteroid>& asteroids, Player& player) {
    asteroids.clear();
    for (int i = 0; i < 3 + level; ++i) { // Add one more asteroid each level
        float x, y;
        do {
            x = static_cast<float>(rand() % 800);
            y = static_cast<float>(rand() % 600);
        } while (std::sqrt(std::pow(x - player.getPosition().x, 2) + std::pow(y - player.getPosition().y, 2)) < 450.f);
        
        asteroids.push_back(Asteroid(AsteroidSize::LARGE, sf::Vector2f(x, y)));
    }
}
