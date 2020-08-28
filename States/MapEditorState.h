#ifndef MAPEDITORSTATE_H
#define MAPEDITORSTATE_H

#include <State.h>
#include "../MapTile.h"
#include "Droplist.h"
#include "MouseScrollingArea.h"
#include "Checkbox.h"
#include "SpriteList.h"
#include <map>
#include <typeinfo>

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

        sf::RectangleShape m_settings;

        GUI::Droplist *m_droplist_selectlevel;
        GUI::Droplist *m_droplist_renderlevel;
        GUI::MouseScrollingArea *m_map_scrolling;
        GUI::Checkbox *m_checkbox_move;
        GUI::Checkbox *m_checkbox_resize;
        GUI::Checkbox *m_checkbox_showed;
        GUI::SpriteList *m_select_sprite_list;

        GUI::Label *m_label_renderlevel;
        GUI::Label *m_label_selectlevel;

        sf::Font m_font;

        sf::Vector2f m_mouse_offset;

        std::map<int,Tile*> m_level_tiles;
        Tile *m_current_tile;
        bool m_created_tile;
        bool m_edit_tile;

        int m_current_selected_level;
        int m_current_rendered_level;

        float m_zoom;

        void initMapTile();
        void initView();
        void initDroplists();
        void initMouseScrollingAreas();
        void initCheckboxes();
        void initLists();
        void initLabels();

        void loadMapLevel();

        void updateGUIElements();
        void updateKeyBoard();
        void updateCreateTile();
        void updateEditTile();
        void updateMapTile();
        void updateTileMoving();

        void renderGUIElements();
        void endState();

        void changeSelectedLevel(const int &level);
        void changeRenderedLevel(const int &level);


};

#endif // MAPEDITORSTATE_H
