#include <core/Game.hpp>

#include <renderer/SoldierRenderer.hpp>


Game::Game()    
    :   config(),
        window()
{
    config.loadFromFile("src/config/game.cfg");
    window.create(sf::VideoMode(config.clientWidth, config.clientHeight), "Shooty");
    scene2D = std::make_unique<GameScene2D>(window.getSize(), config);
}

void Game::run() {

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        window.clear(sf::Color(200,200,200));
        
        scene2D->handleEvents(window);
        scene2D->update(dt);
        scene2D->render(window);

        //TODO DRAW GAME 
        window.display();
    }
}