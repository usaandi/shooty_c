#ifndef MENUMANAGER_HPP
#define MENUMANAGER_HPP

#include <ui/Menu.hpp>

namespace Ui {

    class MenuManager {
    public:
        void setMenu(std::unique_ptr<Menu> menu);
        void handleEvent (const sf::Event&);
        void update(float dt);
        void render(sf::RenderWindow&);
    private:
        std::unique_ptr<Menu> currentMenu;
    };
}


#endif