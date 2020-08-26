#ifndef MAPEDITORSTATE_H
#define MAPEDITORSTATE_H

#include <State.h>
#include "../MapTile.h"
#include "Droplist.h"
#include "MouseScrollingArea.h"
#include "Checkbox.h"
#include <map>

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
        GUI::MouseScrollingArea *m_map_scrolling;
        GUI::Checkbox *m_checkbox_move;
        GUI::Checkbox *m_checkbox_resize;
        GUI::Checkbox *m_checkbox_showed;


        std::map<int,Tile*> m_level_tiles;
        Tile *m_current_tile;
        bool m_created_tile;
        bool m_edit_tile;

        void initMapTile();
        void initView();
        void initDroplists();
        void initMouseScrollingAreas();
        void initCheckboxes();





        void updateKeyBoard();
        void endState();
};

#endif // MAPEDITORSTATE_H
