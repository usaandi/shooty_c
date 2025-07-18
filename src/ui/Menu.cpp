#include <ui/Menu.hpp>

namespace Ui {

    void Menu::handleEvent(const sf::Event& event) {
        if(event.type == sf::Event::KeyPressed) {
            if(event.key.code == sf::Keyboard::Up) {
                selectedIndex = (selectedIndex - 1 + items.size()) % items.size();
            } 
            else if(event.key.code == sf::Keyboard::Down) {
                selectedIndex = (selectedIndex + 1) % items.size();
            } 
            else if(event.key.code == sf::Keyboard::Enter) {
                if(!items.empty())
                    items[selectedIndex]->select();
            }
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
}