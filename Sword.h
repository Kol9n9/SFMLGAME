#ifndef SWORD_H
#define SWORD_H

#include "MeleeWeapon.h"

#include <string>

class Sword : public MeleeWeapon
{
    public:
        Sword(const std::string &texture_file);
        virtual ~Sword();
        void attack();
    protected:

    private:

};

#endif // SWORD_H
