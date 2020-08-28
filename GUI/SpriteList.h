#ifndef SPRITELIST_H
#define SPRITELIST_H

#include <GUI.h>
#include "SFML/Graphics.hpp"
#include "../Tile.h"
namespace GUI{

    struct Item{
        sf::RectangleShape m_item_shape;
        Tile *m_tile;
        Item(const sf::Vector2f &size, Tile *tile)
        {
            m_item_shape.setSize(size);
            m_item_shape.setFillColor(sf::Color(0,0,0));
            m_tile = tile;
        }
    };

    class SpriteList : public GUI
    {
        public:
            SpriteList(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &box_fill_color, const sf::Color &box_item_hover_color);
            virtual ~SpriteList();
            void update();
            void render(sf::RenderTarget *target);
            void setPosition(const sf::Vector2f &pos);


            void addTile(Tile *tile);

            Tile *getHoverTile() {return m_list_item_hover->m_tile;}
            bool const &isHovered() {return m_isHovered;}
            void clear();
        protected:

        private:
            sf::RectangleShape m_list_box;
            Item *m_list_item_hover;
            bool m_isHovered;

            sf::Vector2i m_list_items_count;
            sf::Vector2f m_list_item_size;
            float m_list_item_margin;

            std::vector<Item> m_list_items;

            void Moving();

    };
}
#endif // SPRITELIST_H
