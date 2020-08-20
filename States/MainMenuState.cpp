#include "MainMenuState.h"
void MainMenuState::initVariables()
{
    this->m_font.loadFromFile("GUI/font.ttf");
}
void MainMenuState::initButtons()
{
    this->m_check = new GUI::Checkbox(new GUI::Point(161,6),20,sf::Color(0,0,0),sf::Color(127,127,127),sf::Color(0,255,0));



    this->m_buttons["NEW_GAME"] = new GUI::Button(new GUI::Point(37,93),sf::Vector2f(120,50),
                    new GUI::Label(new GUI::Point(0,0),"New Game",&m_font,25,sf::Color(255,255,255),sf::Color(0,255,255),sf::Color(255,255,255)),
                    false, sf::Color(255,255,255),sf::Color(255,255,255),sf::Color(255,255,255));
    this->m_buttons["SETTINGS"] = new GUI::Button(new GUI::Point(37,148),sf::Vector2f(120,50),
                    new GUI::Label(new GUI::Point(0,0),"Settings",&m_font,25,sf::Color(255,255,255),sf::Color(0,255,255),sf::Color(255,255,255)),
                    false, sf::Color(255,255,255),sf::Color(255,255,255),sf::Color(255,255,255));
    this->m_buttons["CREDITS"] = new GUI::Button(new GUI::Point(37,204),sf::Vector2f(120,50),
                    new GUI::Label(new GUI::Point(0,0),"Credits",&m_font,25,sf::Color(255,255,255),sf::Color(0,255,255),sf::Color(255,255,255)),
                    false, sf::Color(255,255,255),sf::Color(255,255,255),sf::Color(255,255,255));
    this->m_buttons["QUIT"] = new GUI::Button(new GUI::Point(37,260),sf::Vector2f(120,50),
                    new GUI::Label(new GUI::Point(0,0),"Quit",&m_font,25,sf::Color(255,255,255),sf::Color(0,255,255),sf::Color(255,255,255)),
                    false, sf::Color(255,255,255),sf::Color(255,255,255),sf::Color(255,255,255));
    this->m_buttons["NEW_GAME"].callback = &MainMenuState::cb_newgame;
    this->m_buttons["SETTINGS"].callback = &MainMenuState::cb_settings;
    this->m_buttons["CREDITS"].callback = &MainMenuState::cb_credits;
    this->m_buttons["QUIT"].callback = &MainMenuState::cb_quit;

}
MainMenuState::MainMenuState(sf::RenderWindow *target,std::vector<State*>*m_states)
    : State(target,m_states)
{
    initVariables();
    initButtons();
    //ctor
}

MainMenuState::~MainMenuState()
{
    //dtor
}

void MainMenuState::update(const float &dt)
{
    if(!this->m_buttons.empty())
    {
        for(auto it = this->m_buttons.begin(); it != this->m_buttons.end(); ++it)
        {
            (it->second).button->update();
            if((it->second).button->getGUIStatus() == GUI::GUI_STATUS::CLICK && (it->second).callback != nullptr)
                (this->*(it->second).callback)();
            if(GUI::GUI::mouse_click_event == GUI::MOUSE_CLICK_EVENTS::RIGHTCLICK && this->m_check->isChecked())
                if((it->second).button->getGUIStatus() == GUI::GUI_STATUS::HOVER) (it->second).button->startMove();
            if(GUI::GUI::mouse_click_event == GUI::MOUSE_CLICK_EVENTS::NONECLICK)
            {
                (it->second).button->endMove();
            }
        }
    }

    //this->m_check->update();
}
void MainMenuState::render()
{
    if(!this->m_buttons.empty())
    {
        for(auto it = this->m_buttons.begin(); it != this->m_buttons.end(); ++it)
            (it->second).button->render(this->target);
    }
    //this->m_check->render();
}
void MainMenuState::cb_newgame()
{
    std::cout << "cb_newgame\n";
    this->m_states->push_back(new MainGameState(this->target,this->m_states));

}
void MainMenuState::cb_settings()
{
    std::cout << "cb_settings\n";
}
void MainMenuState::cb_credits()
{
    std::cout << "cb_credits\n";
}
void MainMenuState::cb_quit()
{
    std::cout << "cb_quit\n";
    this->m_endState = true;
}
