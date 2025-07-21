#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <memory>
#include <ui/MenuItem.hpp>
#include <SFML/Graphics.hpp>

namespace Ui {

    class Menu {
    public:
        virtual ~Menu() = default;
        virtual void handleEvent(const sf::Event&);
        virtual void update(float dt);
        virtual void render(sf::RenderWindow&);

        void handleKeyPressed(const sf::Event::KeyEvent& key);
        void handleMouseMoved(const sf::Event::MouseMoveEvent& mouseMove);
        void handleMousePressed(const sf::Event::MouseButtonEvent& mouseButton);
    protected:
        std::vector<std::unique_ptr<MenuItem>> items;
        int selectedIndex = 0;
    };
}

#endif