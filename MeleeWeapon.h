#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "Weapon.h"
#include "Movement.h"

class MeleeWeapon : public Weapon
{
    public:
        MeleeWeapon(const std::string &texture_file);
        virtual ~MeleeWeapon();
        void update(const float &dt, const int &dir, const sf::Vector2i &mousePos, const sf::Vector2f &center);
        bool &getAttacking() {return m_is_attacking;}
    protected:
        float m_attack_deg;
        float m_attack_time_speed;
        float m_attack_current_speed;
        float m_attack_time;
        bool m_is_attack;
        bool m_is_attacking;
    private:
        float dss;
        float m_attack_deg_offset;
        float fullAngle;
        int m_dir;
        sf::Vector2f limitAttackAngle(const int &dir);
};

#endif // MELEEWEAPON_H
