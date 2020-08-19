#include "MainGameState.h"
void MainGameState::initPlayer()
{
    this->m_player = new Player();
    this->m_player2 = new Player();
}
MainGameState::MainGameState(sf::RenderWindow *target, std::vector<State*>*m_states)
    : State(target,m_states)
{
    this->initPlayer();
    //ctor
}

MainGameState::~MainGameState()
{
    //dtor
}

void MainGameState::update(const float &dt)
{

    this->updateKeyboard(dt);
    this->m_player->update(dt,this->mousePos);
    //this->m_player2->update(dt,this->mousePos);
    if(this->m_player->getHitbox().intersect(this->m_player2->getHitbox()))
    {

    }
}
void MainGameState::render()
{
    this->m_player->render(this->target);
    this->m_player2->render(this->target);


}
void MainGameState::updateKeyboard(const float &dt)
{
    float speed = 100*dt;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this->m_endState = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->m_player->move(dt,-1.f,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->m_player->move(dt,1.f,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->m_player->move(dt,0,-1.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->m_player->move(dt,0,1.f);
    }
}
