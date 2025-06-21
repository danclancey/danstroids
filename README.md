# Danstroids (Asteroids Clone)
This project is a 2d space shooter game that I build from scratch in C++ using the SFML library. I did my best to clone the original arcade game "Asteroids"

## Features
- **Gameplay**: Fly your ship through an asteroid field, shoot/destroy asteroids, and avoid collisons
- **State-Driven Design**: A game loop manages different states such as 'Main Menu', 'Gameplay', 'High Scores', and 'Game Over' screens
- **Collision Detection**: Collision checks between player, bullets, and asteroids 
- **Difficulity**: Asteroids break into smaller pieces and new levels increase difficulty 
- **Scoring**: Player accumalates points based on asteroid size. 
- **Lives**: Player starts with 3 lives. Upon death, player is temporarily invincible on respawn to avoid "spawn camping" 
- **Main Menu and High Scores**: A functional main menu to start game, view persistent high scores, and quit. High scores are saved to `highscores.txt`
- **Sounds**: Sound effects for shooting, asteroid hits, and player death (Managed by `SoundManager` class)

## How to Play 
- **Movement**: Use `W`, `A`, `D` or `Up`, `Left`, `Right` arrows to control ship movement and rotation
- **Shooting**: Press `spacebar` to fire lasers at asteroids 
- **Menu Nav**: Use `Up` and `Down` arrows to navigate the menu. Use `Enter` to select option

## Reqauirements
To build and run this project, you'll need:
- A C++ compiler
- **SFML**. You must have the dev libraries installed for graphics, audio, window, and system

## Building and Running
1. Clone repository
2. Open terminal in project directory
3. Compile source code (Example using g++):
    ```
    ```c++
    g++ src/*.cpp -o asteroids -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
    ```
    ``` 
    ```
    ``````
    ```
4. Run Game 
    ```c++
    ```c++ 
    ./asteroids 
    ```
    ```
    ```
    ```
    ``` 
    ``````
    ```

## File Structure
- `main.cpp`: Entry point for applicatoin. Manages game states and main game loop 
- `Player.(h/cpp)`: Defines player ship, including movement, input, and invincibility
- `Asteroid.(h/cpp)`: Defines asteroids, including size, shape, and movement 
- `Bullet.(h/cpp)`: Defines bullets fired by player 
- `Menu.(h/cpp)`: Managed menu UI and navigation 
- `SoundManager.(h/cpp)`: Load and plays game audio 
- `HighScoreManager.(h/cpp)`: Handles loading, saving and displaying high scores (`highscores.txt`)
