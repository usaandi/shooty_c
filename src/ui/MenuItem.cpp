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
    {
        textObject.setFont(getFont());
        textObject.setString(text.data());
        textObject.setCharacterSize(30);
        textObject.setFillColor(sf::Color::White);

        sf::FloatRect bounds = textObject.getLocalBounds();
        textObject.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    }

    void MenuItem::render(sf::RenderWindow& window, bool selected, const sf::Vector2f& position) {
        
        textObject.setFillColor(selected ? sf::Color::Yellow : sf::Color::White);
  
        textObject.setPosition(position);
        
        window.draw(textObject);
    }

    void MenuItem::select() {
        if (onSelect) onSelect();
        
    }

    sf::FloatRect MenuItem::getBounds() const {
        return textObject.getGlobalBounds();
    }
}