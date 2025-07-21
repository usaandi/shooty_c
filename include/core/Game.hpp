#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include <core/scene/GameScene2D.hpp>
#include <config/GameConfig.hpp>
#include <ui/MenuManager.hpp>
#include <memory>

class Game {
public:
    Game();
    void run();


private:

    enum class GameState {
        mainMenu,
        playing,
        paused,
        gameOver
    };

    sf::RenderWindow window;
    std::unique_ptr<GameScene2D> scene2D;
    GameConfig config;
    Ui::MenuManager menuManager;
    GameState currentState = GameState::mainMenu;

    void processEvents();
    void update(float dt);
    void render();
    void startGameScene2D();
    void restartGameScene2D();
};




#endif //GAME_HPP