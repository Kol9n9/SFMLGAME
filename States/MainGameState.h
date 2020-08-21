#ifndef MAINGAMESTATE_H
#define MAINGAMESTATE_H

#include <State.h>

#include "../Player.h"
#include "../Rat.h"
#include "../TextTag.h"
#include "../PlayerHUD.h"

class MainGameState : public State
{
    public:
        MainGameState(sf::RenderWindow *target, std::vector<State*>*m_states);
        virtual ~MainGameState();
        void update(const float &dt);
        void render();
    protected:

    private:
        //variables
        Player *m_player;
        TextTag *m_textTag;
        PlayerHUD *m_playerHUD;
        std::vector<Enemy*>m_enemy;
        //inits
        void initPlayer();
        void initEnemies();
        void initTextTag();
        void initPlayerHUD();
        //functions
        void updateKeyboard(const float &dt);

};

#endif // MAINGAMESTATE_H
