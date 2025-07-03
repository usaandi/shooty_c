#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include <core/scene/GameScene2D.hpp>
#include <config/GameConfig.hpp>

class Game {
public:
    Game();
    void run();


private:
    sf::RenderWindow window;
    std::unique_ptr<GameScene2D> scene2D;
    GameConfig config;
};




#endif //GAME_HPP