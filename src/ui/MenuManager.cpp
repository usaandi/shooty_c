#include <ui/MenuManager.hpp>


namespace Ui {
    void MenuManager::setMenu(std::unique_ptr<Menu> menu) {
        currentMenu = std::move(menu);
    }

    void MenuManager::handleEvent(const sf::Event& event) {
        if (currentMenu) {
            currentMenu->handleEvent(event);
        }
    }

    void MenuManager::update(float dt) {
        if (currentMenu) {
            currentMenu->update(dt);
        }
    }

    void MenuManager::render(sf::RenderWindow& window) {
        if (currentMenu) {
            currentMenu->render(window);
        }
    }
}