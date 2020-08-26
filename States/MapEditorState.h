#ifndef MAPEDITORSTATE_H
#define MAPEDITORSTATE_H

#include <State.h>
#include "../MapTile.h"
#include "Droplist.h"

class MapEditorState : public State
{
    public:
        MapEditorState(sf::RenderWindow *target, std::vector<State*>*m_states);
        virtual ~MapEditorState();

        void update(const float &dt);
        void render();

    protected:

    private:
        MapTile *m_map_tile;
        sf::View m_view;
        sf::View m_default_view;
        GUI::Droplist *m_select_level;

        void initMapTile();
        void initView();
        void initDroplists();

        void updateKeyBoard();
        void endState();
};

#endif // MAPEDITORSTATE_H
