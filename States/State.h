#ifndef STATE_H
#define STATE_H
#include "SFML/Graphics.hpp"
#include <vector>
#include <map>
#include <iostream>
class State
{
    public:
        State(sf::RenderWindow *target,std::vector<State*>*m_states);
        virtual ~State();
        virtual void update(const float &dt) = 0;
        virtual void render() = 0;
        const bool &isExit() const {return m_endState;}
    protected:
        sf::RenderWindow *target;
        bool m_endState;
        std::vector<State*>*m_states;
    private:

};

#endif // STATE_H
