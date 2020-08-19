#include "Game.h"

void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(800,600),"Game");
}
void Game::initState()
{
    this->states.push_back(new MainMenuState(this->window,&this->states));
}
void Game::initVariables()
{
    this->dt = 0;
}
Game::Game()
{
    this->window = NULL;
    this->initWindow();
    this->initState();
    this->initVariables();
    //ctor
}

Game::~Game()
{
    if(this->window) delete this->window;
    //dtor
}

void Game::run()
{
    while(this->window->isOpen())
    {
        this->updateSFMLEvents();
        this->update();
        this->render();
    }
}

void Game::render()
{
    this->window->clear(sf::Color(0,0,0));
    if(!this->states.empty())
    {
        this->states.back()->render();
    }
    this->window->display();
}
void Game::update()
{

    this->updatedtTime();
    if(!this->states.empty())
    {
        this->states.back()->update(this->dt);
        this->states.back()->updateMousePos();

        if(this->states.back()->isExit())
        {
            this->states.pop_back();
            if(this->states.empty())
                this->endApplication();
        }
    }
}
void Game::updatedtTime()
{
    this->dt = this->clock.restart().asSeconds();
}
void Game::endApplication()
{
    std::cout << "endApplication\n";
    this->window->close();
}
void Game::updateSFMLEvents()
{
    while(this->window->pollEvent(this->SFMLEvent))
    {
        switch(this->SFMLEvent.type)
        {
            case sf::Event::Closed:
            {
                window->close();
                break;
            }
            case sf::Event::Resized:
            {
                break;
            }
            default:
            {
                GUI::GUI::updateEvents(this->SFMLEvent);
                break;
            }
        }
    }
}
