#ifndef MAINGAMESTATE_H
#define MAINGAMESTATE_H

#include <State.h>

#include "../Player.h"

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
        Player *m_player2;
        Player *m_player3;
        std::vector<Entity*>m_entity;
        //inits
        void initPlayer();
        //functions
        void updateKeyboard(const float &dt);

};

#endif // MAINGAMESTATE_H
