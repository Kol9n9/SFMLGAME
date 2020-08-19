#include "State.h"

State::State(sf::RenderWindow *target,std::vector<State*>*m_states)
    : target(target),m_states(m_states)
{
    this->m_endState = false;
    //ctor
}

State::~State()
{
    //dtor
}
