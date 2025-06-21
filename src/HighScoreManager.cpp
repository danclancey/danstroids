#include "../includes/HighScoreManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>

HighScoreManager::HighScoreManager() {
    if (!font.loadFromFile("../assets/arial.ttf")) {
        std::cerr << "Error loading arial.ttf in HighScoreManager" << std::endl;
    }
    loadScores();
}

void HighScoreManager::loadScores() {
    std::ifstream file(filename);
    scores.clear();
    if (file.is_open()) {
        std::string name;
        int score;
        while (file >> name >> score) {
            scores.push_back({name, score});
        }
        file.close();
    }
}

void HighScoreManager::saveScores() {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& entry : scores) {
            file << entry.name << " " << entry.score << std::endl;
        }
        file.close();
    }
}

void HighScoreManager::addScore(const std::string& name, int score) {
    scores.push_back({ name, score });
    std::sort(scores.begin(), scores.end(), [](const HighScoreEntry& a, const HighScoreEntry& b) {
        return a.score > b.score;
    });
    if (scores.size() > maxScores) {
        scores.resize(maxScores);
    }
    saveScores();
}

bool HighScoreManager::isHighScore(int score) const {
    if (scores.size() < maxScores) {
        return true;
    }
    return score > scores.back().score;
}

void HighScoreManager::draw(sf::RenderWindow& window) {
    sf::Text title;
    title.setFont(font);
    title.setString("High Scores");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(800 / 2.f - title.getLocalBounds().width / 2.f, 50);
    window.draw(title);

    for (size_t i = 0; i < scores.size(); ++i) {
        sf::Text entryText;
        entryText.setFont(font);
        entryText.setString(std::to_string(i + 1) + ". " + scores[i].name + " - " + std::to_string(scores[i].score));
        entryText.setCharacterSize(30);
        entryText.setFillColor(sf::Color::White);
        entryText.setPosition(800 / 2.f - entryText.getLocalBounds().width / 2.f, 150 + i * 40);
        window.draw(entryText);
    }

    sf::Text instruction;
    instruction.setFont(font);
    instruction.setString("Press ESC to return to menu");
    instruction.setCharacterSize(20);
    instruction.setFillColor(sf::Color::Cyan);
    instruction.setPosition(800 / 2.f - instruction.getLocalBounds().width / 2.f, 550);
    window.draw(instruction);
}
