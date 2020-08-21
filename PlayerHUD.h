#ifndef PLAYERHUD_H
#define PLAYERHUD_H

#include "SFML/Graphics.hpp"
#include "Button.h"
#include "Progressbar.h"
#include "Attribute.h"
#include <string>
class PlayerHUD
{
    public:
        PlayerHUD(Attribute *player_attribute, const std::string &font_file);
        virtual ~PlayerHUD();
        void update(const float &dt);
        void render(sf::RenderTarget *target);
    protected:

    private:
        GUI::Button *m_level_button;
        GUI::Progressbar *m_hp_bar;
        GUI::Progressbar *m_exp_bar;
        sf::Font m_font;
        Attribute *m_player_attribute;
        void initHUD();
        void initFont(const std::string &font_file);
        void updateHP();
        void updateEXP();

};

#endif // PLAYERHUD_H
