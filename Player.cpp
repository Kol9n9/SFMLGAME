#include "Player.h"

Player::Player(const float &base_hp, const float &base_damage,const sf::Vector2f &pos)
    : Entity("resouces/PLAYER_SHEET2.png", sf::IntRect(10,3,44,62), base_hp, base_damage, pos)
{
    this->initAnimations();
    this->m_movement = new Movement(this,0.2f,0.15f,0.2f);
    this->m_weapon = new Sword("resouces/sword.png");
    this->m_hp = this->m_base_hp;
    this->m_hp_max = this->m_base_hp_max;
    this->m_damage = this->m_base_damage;
    this->m_isDied = false;
    this->m_dir = movement_states::MOVING_DOWN;
    //ctor
}
void Player::initAnimations()
{
    this->m_animation = new Animation(this->m_sprite);
    this->m_animation->addAnimation("WALK_IDLE",15.f,
                                    std::vector<sf::IntRect>{
                                        sf::IntRect(10,3,44,62),sf::IntRect(74,3,44,62),sf::IntRect(138,6,44,59),sf::IntRect(202,6,44,59),
                                        sf::IntRect(266,6,44,59),sf::IntRect(330,6,44,59),sf::IntRect(394,6,44,59),sf::IntRect(458,4,44,61),sf::IntRect(522,3,44,62)
                                    }
                                    );
    this->m_animation->addAnimation("WALK_RIGHT",15.f,std::vector<sf::IntRect>{sf::IntRect(524,71,32,58),sf::IntRect(592,69,32,60),sf::IntRect(655,71,34,58),sf::IntRect(720,69,32,60)});
    this->m_animation->addAnimation("WALK_LEFT",11.f,std::vector<sf::IntRect>{sf::IntRect(464,69,32,60),sf::IntRect(400,71,32,58),sf::IntRect(336,69,32,60),sf::IntRect(272,71,34,58)});
    this->m_animation->addAnimation("WALK_DOWN",15.f,std::vector<sf::IntRect>{sf::IntRect(12,69,40,60),sf::IntRect(74,67,44,62),sf::IntRect(140,69,40,60),sf::IntRect(202,67,44,62)});
    this->m_animation->addAnimation("WALK_UP",15.f,std::vector<sf::IntRect>{sf::IntRect(780,69,40,60),sf::IntRect(842,67,47,62),sf::IntRect(908,69,40,60),sf::IntRect(970,67,44,62)});
}

Player::~Player()
{
    if(this->m_animation) delete this->m_animation;
    if(this->m_movement) delete this->m_movement;
    if(this->m_weapon) delete this->m_weapon;

    //dtor
}
void Player::render(sf::RenderTarget *target)
{
    if(this->m_isDied) return;
    target->draw(this->m_sprite);
    target->draw(this->getHitbox().getHitbox());
    target->draw(this->m_weapon->getSprite());
    sf::RectangleShape shape;
    shape.setPosition(this->m_weapon->getPointAttack());
    shape.setSize(sf::Vector2f(2,2));
    shape.setFillColor(sf::Color(255,0,0));
    target->draw(shape);
}
void Player::update(const float &dt,const sf::Vector2i &mousePos)
{
    if(this->m_isDied) return;
    this->m_first = true;
    if(this->m_old_dir == this->m_dir)
    {
        this->m_first = false;
    }
    this->m_old_dir = this->m_dir;
    if(this->m_movement)
        this->m_movement->update(dt);

    if(this->m_hitbox)
        this->m_hitbox->updateHitbox(this->m_position,this->getSpriteSize());

    if(this->m_weapon)
        this->m_weapon->update(dt, this->m_dir, mousePos,sf::Vector2f(this->getSpriteCenter().x + 5,this->getSpriteCenter().y + 10));

    if(this->m_movement)
    {
        if(this->m_movement->getState(IDLE))
        {
            this->m_old_dir = -1;

            //this->m_animation->play("WALK_IDLE",dt);
        }
        else if(this->m_movement->getState(MOVING_LEFT))
        {
            this->m_animation->play("WALK_LEFT",dt,this->m_first);
            this->m_dir = movement_states::MOVING_LEFT;
        }
        else if(this->m_movement->getState(MOVING_RIGHT))
        {
            this->m_animation->play("WALK_RIGHT",dt,this->m_first);
            this->m_dir = movement_states::MOVING_RIGHT;
        }
        else if(this->m_movement->getState(MOVING_UP))
        {
            this->m_animation->play("WALK_UP",dt,this->m_first);
            this->m_dir = movement_states::MOVING_UP;
        }
        else if(this->m_movement->getState(MOVING_DOWN))
        {
            this->m_animation->play("WALK_DOWN",dt,this->m_first);
            this->m_dir = movement_states::MOVING_DOWN;
        }
    }
}

void Player::move(const float &dt, const float &dir_x, const float &dir_y)
{
    if(this->m_weapon && this->m_weapon->getAttacking())
        return;
    if(this->m_movement)
        this->m_movement->move(dt,dir_x,dir_y);
}
void Player::attack()
{
    this->m_movement->stopMove();
    this->m_weapon->attack();
}
void Player::loseHP(const float &damage)
{
    this->m_hp -= damage;
    std::cout << "HP = " << this->m_hp << "\n";
    if(this->m_hp <= 0) this->m_isDied = true;
}
