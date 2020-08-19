#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "Weapon.h"

enum PLAYER_MOVE_DIR{
    NONE = -1,
    UP,
    RIGHT,
    DOWN,
    LEFT,
    UPRIGHT,
    DOWNRIGHT,
    DOWNLEFT,
    UPLEFT
};

class MeleeWeapon : public Weapon
{
    public:
        MeleeWeapon(const std::string &texture_file);
        virtual ~MeleeWeapon();
        void update(const float &dt, const int &dir, const sf::Vector2i &mousePos, const sf::Vector2f &center);
    protected:
        float m_attack_deg;
        float m_attack_time_speed;
        float m_attack_current_speed;
        float m_attack_time;
        bool m_is_attack;
        bool m_is_atacking;
    private:
        float dss;
        float m_attack_deg_offset;


        sf::Vector2f limitAttackAngle(const int &dir);
};

#endif // MELEEWEAPON_H
