#include <ui/Menu.hpp>

namespace Ui {

    void Menu::handleEvent(const sf::Event& event) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handleKeyPressed(event.key);
                break;
            case sf::Event::MouseMoved:
                handleMouseMoved(event.mouseMove);
                break;
            case sf::Event::MouseButtonPressed:
                handleMousePressed(event.mouseButton);
                break;
            default:
                break;
        }
    }



    void Menu::update(float /*dt*/) {
    // No-op by default
    }


    void Menu::render(sf::RenderWindow& window) {
        const sf::Vector2u windowSize = window.getSize();
        const float spacing = 50.f;

        float totalHeight = items.size() * spacing;
        float startY = (windowSize.y - totalHeight) / 2.f;


        // Render each item in the menu
        for (size_t i = 0; i < items.size(); i++) {

            float y = startY + i * spacing;
            sf::Vector2f position(windowSize.x / 2.f, y); 
            items[i]->render(window, static_cast<int>(i) == selectedIndex,position);

        }
    }

    void Menu::handleKeyPressed(const sf::Event::KeyEvent& key) {
        if(key.code == sf::Keyboard::Up) {
                selectedIndex = (selectedIndex - 1 + items.size()) % items.size();
        } 
        else if(key.code == sf::Keyboard::Down) {
            selectedIndex = (selectedIndex + 1) % items.size();
        } 
        else if(key.code == sf::Keyboard::Enter) {
            if(!items.empty()) items[selectedIndex]->select();
        }
    }
    
    void Menu::handleMouseMoved(const sf::Event::MouseMoveEvent& mouseMove) {
        sf::Vector2f mousePos(static_cast<float>(mouseMove.x), static_cast<float>(mouseMove.y));
        for (size_t i = 0; i < items.size(); i++)
        {
            if(items[i]->getBounds().contains(mousePos)){
                selectedIndex = i;
                break;
            }
        }
    }

    void Menu::handleMousePressed(const sf::Event::MouseButtonEvent& mouseButton) {
        if(mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(static_cast<float>(mouseButton.x), static_cast<float>(mouseButton.y));
            if(!items.empty() && items[selectedIndex]->getBounds().contains(mousePos)) {
                items[selectedIndex]->select();
            }
        }
    }
}