#include "MainGameState.h"
void MainGameState::initPlayer()
{
    this->m_player = new Player(100,50);
    this->m_player2 = new Player(150,25,sf::Vector2f(200,200));
    this->m_player3 = new Player(400,40,sf::Vector2f(300,300));

    this->m_entity.push_back(this->m_player2);
    this->m_entity.push_back(this->m_player3);
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
    for(auto it = this->m_entity.begin(); it != this->m_entity.end(); ++it)
    {
        (*it)->update(dt,this->mousePos);
        if(this->m_player->getAttacking() && !(*it)->isDied() && !(*it)->getIntersected() && (*it)->getHitbox().intersect(this->m_player->getPointAttack()))
        {
            (*it)->loseHP(this->m_player->getDamage());
            (*it)->setIntersected(true);
        }
        if((*it)->getIntersected() && !(*it)->getHitbox().intersect(this->m_player->getPointAttack()))
        {
            (*it)->setIntersected(false);
        }
    }
}
void MainGameState::render()
{
    this->m_player->render(this->target);
    for(auto it = this->m_entity.begin(); it != this->m_entity.end(); ++it)
    {
        (*it)->render(this->target);
    }
}
void MainGameState::updateKeyboard(const float &dt)
{
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
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        this->m_player->attack();
    }
}
