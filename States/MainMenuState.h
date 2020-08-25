#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <State.h>
#include <iostream>
#include "Button.h"
#include "Checkbox.h"
#include "MainGameState.h"


class MainMenuState : public State
{
    public:
        MainMenuState(sf::RenderWindow *target, std::vector<State*>*m_states);
        virtual ~MainMenuState();

        void update(const float &dt);
        void render();
    protected:

    private:
        struct m_ButtItem{
            GUI::Button* button;
            void (MainMenuState::*callback)();
            m_ButtItem()
            {
                button = NULL;
                callback = nullptr;
            }
            m_ButtItem(GUI::Button* but)
            {
                button = but;
                callback = nullptr;
            }
            m_ButtItem(GUI::Button* butt,void (MainMenuState::*cb)())
            {
                button = butt;
                callback = cb;
            }
        };
        //variables
        std::map<std::string,m_ButtItem> m_buttons;
        GUI::Checkbox *m_check;
        sf::Font m_font;
        //inits
        void initButtons();
        void initVariables();
        //functions
        void cb_newgame();
        void cb_settings();
        void cb_credits();
        void cb_quit();
};

#endif // MAINMENUSTATE_H
