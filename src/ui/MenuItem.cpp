#include <ui/MenuItem.hpp>
#include <iostream>

namespace Ui {

    // Static font shared by all MenuItems
    static sf::Font& getFont() {
        static sf::Font font;
        static bool loaded = false;
        if (!loaded) {
            if (!font.loadFromFile("../assets/fonts/arial/arial.ttf")) {
                std::cerr << "Failed to load font assets/fonts/arial.ttf\n";
            
            }
            loaded = true;
        }
        return font;
    }

    MenuItem::MenuItem(const std::string_view& text, std::function<void()> onSelect)
        : text(text), onSelect(std::move(onSelect))
    {}

    void MenuItem::render(sf::RenderWindow& window, bool selected, const sf::Vector2f& position) {
        sf::Text drawable;
        drawable.setFont(getFont());
        drawable.setString(text.data());
        drawable.setCharacterSize(30);
        drawable.setFillColor(selected ? sf::Color::Yellow : sf::Color::White);

        sf::FloatRect bounds = drawable.getLocalBounds();
        drawable.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        drawable.setPosition(position);
        
        window.draw(drawable);
    }

    void MenuItem::select() {
        if (onSelect) onSelect();
        
    }
}