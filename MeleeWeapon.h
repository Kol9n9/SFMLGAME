#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "Weapon.h"


class MeleeWeapon : public Weapon
{
    public:
        MeleeWeapon(const std::string &texture_file);
        virtual ~MeleeWeapon();

    protected:

    private:
};

#endif // MELEEWEAPON_H
