#ifndef MENUITEM_HPP
#define MENUITEM_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

namespace Ui {

    class MenuItem {
    public:
        MenuItem(const std::string_view& text, std::function<void()> onSelect);
        void render(sf::RenderWindow& window, bool selected, const sf::Vector2f& position);
        void select();
    private:
        std::string_view text;
        std::function<void()> onSelect;
    
    };
}

#endif