#include "PlayerHUD.h"

void PlayerHUD::initHUD()
{
    this->m_level_button = new GUI::Button(sf::Vector2f(0,0),sf::Vector2f(70,70),
                        new GUI::Label(sf::Vector2f(0,0),"1",&this->m_font,40,sf::Color(0,0,0),sf::Color(255,255,255),sf::Color(255,255,255)),
                        true,sf::Color(255,255,255),sf::Color(127,127,127),sf::Color(127,127,127));
    this->m_hp_bar = new GUI::Progressbar(sf::Vector2f(70,0),sf::Vector2f(130,20),sf::Color(255,255,255),sf::Color(255,0,0),sf::Color(255,0,0));
    this->m_exp_bar = new GUI::Progressbar(sf::Vector2f(70,30),sf::Vector2f(130,20),sf::Color(255,255,255),sf::Color(255,255,0),sf::Color(0,255,0));
    this->m_exp_bar->setOutlineThickness(-3);
    this->m_exp_bar->setOutlineColor(sf::Color(127,127,127));

    this->m_hp_bar->setOutlineThickness(-3);
    this->m_hp_bar->setOutlineColor(sf::Color(127,127,127));
    this->m_hp_bar->setLabel(new GUI::Label(sf::Vector2f(0,0),"20/20",&this->m_font,15,sf::Color(255,255,255),sf::Color(255,255,255),sf::Color(255,255,255)));
    this->m_exp_bar->setLabel(new GUI::Label(sf::Vector2f(0,0),"0/20",&this->m_font,15,sf::Color(255,0,255),sf::Color(255,0,255),sf::Color(255,0,255)));

    this->updateHP();
    this->updateEXP();
    this->updateLevelButton();
}

void PlayerHUD::initFont(const std::string &font_file)
{
    this->m_font.loadFromFile(font_file);
}

PlayerHUD::PlayerHUD(Attribute *player_attribute,const std::string &font_file)
    : m_player_attribute(player_attribute)
{
    this->initFont(font_file);
    this->initHUD();
    //ctor
}

PlayerHUD::~PlayerHUD()
{
    if(this->m_level_button) delete this->m_level_button;
    if(this->m_hp_bar) delete this->m_hp_bar;
    //dtor
}

void PlayerHUD::update(const float &dt)
{
    this->updateHP();
    this->updateEXP();
    this->updateLevelButton();
    this->m_level_button->update();
    this->m_hp_bar->update();
    this->m_exp_bar->update();
    this->m_hp_bar->endMove();
    if(GUI::GUI::mouse_click_event == GUI::LEFTCLICK)
    {
        if(this->m_hp_bar->getGUIStatus() == GUI::GUI_STATUS::CLICKING) this->m_hp_bar->startMove();
    }
}
void PlayerHUD::render(sf::RenderTarget *target)
{
    this->m_level_button->render(target);
    this->m_hp_bar->render(target);
    this->m_exp_bar->render(target);
}
void PlayerHUD::updateHP()
{
    int percent = this->m_player_attribute->getHP() / this->m_player_attribute->getHPMax() * 100;
    this->m_hp_bar->setPercent(percent);
}
void PlayerHUD::updateEXP()
{
    int percent = this->m_player_attribute->getEXP() / this->m_player_attribute->getEXPMax() * 100;
    this->m_exp_bar->setPercent(percent);
    sf::String str;
    str += std::to_string((int)this->m_player_attribute->getEXP());
    str += "/";
    str += std::to_string((int)this->m_player_attribute->getEXPMax());
    this->m_exp_bar->setLabelText(str);
}
void PlayerHUD::updateLevelButton()
{
    sf::String str = std::to_string(this->m_player_attribute->getLevel());
    this->m_level_button->setText(str);
}

