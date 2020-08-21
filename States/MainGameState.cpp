#include "MainGameState.h"
void MainGameState::initPlayer()
{
    this->m_player = new Player();
    this->m_player->getAttribute().setStrength(10);

}
void MainGameState::initEnemies()
{
    this->m_enemy.push_back(new Rat(sf::Vector2f(100,100)));
    this->m_enemy.push_back(new Rat(sf::Vector2f(200,100)));
}
void MainGameState::initTextTag()
{
    this->m_textTag = new TextTag("GUI/font.ttf");
}
void MainGameState::initPlayerHUD()
{
    this->m_playerHUD = new PlayerHUD(&this->m_player->getAttribute(),"GUI/font.ttf");
}
MainGameState::MainGameState(sf::RenderWindow *target, std::vector<State*>*m_states)
    : State(target,m_states)
{
    this->initPlayer();
    this->initEnemies();
    this->initTextTag();
    this->initPlayerHUD();
    //ctor
}

MainGameState::~MainGameState()
{
    std::cout << "~MainGameState\n";
    if(!this->m_enemy.empty())
    {
        for(auto &it : this->m_enemy)
            delete it;
    }
    if(this->m_player) delete this->m_player;
    if(this->m_textTag) delete this->m_textTag;
    if(this->m_playerHUD) delete this->m_playerHUD;
    //dtor
}

void MainGameState::update(const float &dt)
{

    this->updateKeyboard(dt);
    this->m_player->update(dt,GUI::GUI::mousePos);
    this->m_textTag->update(dt);
    for(auto it = this->m_enemy.begin(); it != this->m_enemy.end(); ++it)
    {
        (*it)->update(dt,GUI::GUI::mousePos);
        if(this->m_player->getAttacking() && !(*it)->isDied() && !(*it)->getIntersected() && (*it)->getHitbox().intersect(this->m_player->getPointAttack(),this->m_player->getWeapon()->getSpriteSize()))
        {
            (*it)->loseHP(this->m_player->getAttribute().getDamage());
            sf::String str = " - ";
            str += std::to_string((int)this->m_player->getAttribute().getDamage());
            str += " HP";
            this->m_textTag->addTextTag(TextTag_TYPE::TextTag_NEGATIVE, str,(*it)->getPosition());
            if((*it)->isDied())
            {
                str = " + ";
                str += std::to_string((int)(*it)->getGivedXP());
                str += " XP";
                this->m_textTag->addTextTag(TextTag_TYPE::TextTag_POSITIVE, str,(*it)->getPosition());
                this->m_player->getAttribute().giveEXP((*it)->getGivedXP());
            }
            (*it)->setIntersected(true);
        }
        if((*it)->getIntersected() && !(*it)->getHitbox().intersect(this->m_player->getPointAttack(),this->m_player->getWeapon()->getSpriteSize()))
        {
            (*it)->setIntersected(false);
        }
    }
    if(this->m_playerHUD) this->m_playerHUD->update(dt);
}
void MainGameState::render()
{
    if(this->m_player) this->m_player->render(this->target);
    for(auto it = this->m_enemy.begin(); it != this->m_enemy.end(); ++it)
    {
        (*it)->render(this->target);
    }
    if(this->m_textTag) this->m_textTag->render(this->target);
    if(this->m_playerHUD) this->m_playerHUD->render(this->target);
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
