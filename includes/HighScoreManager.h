#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

struct HighScoreEntry {
    std::string name;
    int score;
};

class HighScoreManager {
public:
    HighScoreManager();
    void addScore(const std::string& name, int score);
    bool isHighScore(int score) const;
    void draw(sf::RenderWindow& window);

private:
    std::vector<HighScoreEntry> scores;
    sf::Font font;
    const std::string filename = "../assets/highscores.txt";
    const int maxScores = 10;

    void loadScores();
    void saveScores();
};
