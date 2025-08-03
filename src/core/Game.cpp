#include <core/Game.hpp>

#include <renderer/SoldierRenderer.hpp>
#include <ui/MainMenu.hpp>

Game::Game()    
    :   config(),
        window()
{
    config.loadFromFile("src/config/game.cfg");
    window.create(sf::VideoMode(config.clientWidth, config.clientHeight), "Shooty");

    menuManager.setMenu(std::make_unique<Ui::MainMenu>([this]() {
        startGameScene2D();
    }));
}

void Game::run() {

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        processEvents();
        update(dt);

        window.clear(sf::Color(200,200,200));
        render();
        window.display();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (currentState == GameState::mainMenu) {
            menuManager.handleEvent(event);

        } if (currentState == GameState::playing) {
            scene2D->handleEvents(event);
        }
    }
}

void Game::update(float dt) {
    if (currentState == GameState::mainMenu ) {
        menuManager.update(dt);
    } else if (scene2D) {
        scene2D->update(dt);

        if (scene2D->shouldRestart()) {restartGameScene2D();};
    } 
}

void Game::render() {
    if (currentState == GameState::mainMenu ) {
        menuManager.render(window);
    } else if (scene2D) {
        scene2D->render(window);
    }
}

void Game::startGameScene2D(){
    currentState = GameState::playing;
    scene2D = std::make_unique<GameScene2D>(window.getSize(), config);
    scene2D->setWindow(&window);
    menuManager.setMenu(nullptr);
}

void Game::restartGameScene2D() {
    startGameScene2D();
}