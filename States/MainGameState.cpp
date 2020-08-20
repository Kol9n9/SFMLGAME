#include "MainGameState.h"
void MainGameState::initPlayer()
{
    this->m_player = new Player();
    this->m_player->getAtribute().setStrength(10);
    this->m_enemy.push_back(new Rat(sf::Vector2f(100,100)));
    this->m_enemy.push_back(new Rat(sf::Vector2f(200,100)));
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
    this->m_player->update(dt,GUI::GUI::mousePos);
    for(auto it = this->m_enemy.begin(); it != this->m_enemy.end(); ++it)
    {
        (*it)->update(dt,GUI::GUI::mousePos);
        if(this->m_player->getAttacking() && !(*it)->isDied() && !(*it)->getIntersected() && (*it)->getHitbox().intersect(this->m_player->getPointAttack(),this->m_player->getWeapon()->getSpriteSize()))
        {
            (*it)->loseHP(this->m_player->getAtribute().getDamage());
            (*it)->setIntersected(true);
        }
        if((*it)->getIntersected() && !(*it)->getHitbox().intersect(this->m_player->getPointAttack(),this->m_player->getWeapon()->getSpriteSize()))
        {
            (*it)->setIntersected(false);
        }
    }
}
void MainGameState::render()
{
    this->m_player->render(this->target);
    for(auto it = this->m_enemy.begin(); it != this->m_enemy.end(); ++it)
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
