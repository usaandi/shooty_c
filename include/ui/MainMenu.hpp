#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <ui/Menu.hpp>

namespace Ui {

    class MainMenu : public Menu {
    public:
        MainMenu(std::function<void()> onStartGame);
        void handleEvent(const sf::Event&) override;
        void update(float dt) override;
        void render(sf::RenderWindow&) override;
    private:
        std::function<void()> onStartGame;
    };
}


#endif