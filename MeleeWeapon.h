#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "Weapon.h"


class MeleeWeapon : public Weapon
{
    public:
        MeleeWeapon(const std::string &texture_file);
        virtual ~MeleeWeapon();

    protected:
        float m_attack_deg;
        float m_attack_time_speed;
        float m_attack_current_speed;
        float m_attack_time;
        bool m_is_attack;
    private:
};

#endif // MELEEWEAPON_H
