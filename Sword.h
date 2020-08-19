#ifndef SWORD_H
#define SWORD_H

#include "MeleeWeapon.h"
#include <string>
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
class Sword : public MeleeWeapon
{
    public:
        Sword(const std::string &texture_file);
        virtual ~Sword();
        void attack();
        void update(const int &dir, const sf::Vector2i &mousePos, const sf::Vector2f &center);
    protected:

    private:
};

#endif // SWORD_H
