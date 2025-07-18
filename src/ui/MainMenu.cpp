#include <ui/MainMenu.hpp>
#include <ui/MenuItem.hpp>
#include <iostream>

namespace Ui {
    MainMenu::MainMenu(std::function<void()> onStartGame)
        : onStartGame(onStartGame)
    {
        items.emplace_back(std::make_unique<MenuItem>("Start Game", this->onStartGame));
        items.emplace_back(std::make_unique<MenuItem>("Exit", []() {
            std::cout << "Exiting game..." << std::endl;
            // Close the application
            std::exit(0);

        }));
        
        selectedIndex = 0; // Default
    }

    void MainMenu::render(sf::RenderWindow& window) {
        Menu::render(window);
    }

    void MainMenu::handleEvent(const sf::Event& event) {
        Menu::handleEvent(event);
    }

    void MainMenu::update(float dt) {
        Menu::update(dt); // no-op for now
    }
}