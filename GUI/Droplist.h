#ifndef DROPLIST_H
#define DROPLIST_H

#include <GUI.h>
#include "Button.h"

#include "List.h"

namespace GUI{
    class Droplist : public GUI
    {
        public:
            Droplist(const sf::Vector2f &start_pos, const sf::Vector2f &sizes, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            virtual ~Droplist();
            void update();
            void update(const float &dt);
            void render(sf::RenderTarget *target);
            void setList(List *list);
            void Moving();
            void setPosition(const sf::Vector2f &pos);
            void setSize(const sf::Vector2f &size);
            void setButWidth(const float &width);
            void insert(Label*);
            sf::Text &getActiveItemText() {return activeItem.text->getText();}
            void setActiveItem(const int &index);
            const bool &isItemSelected();
            const bool &isHovered() {return m_ishovered;};
            void setListItems(const int &c){if(!this->list)return; this->list->setItemCount(c);}
            static bool isAvailable;
        protected:

        private:
            sf::RectangleShape shape;
            Button *but;
            sf::Text text;
            List *list;

            float m_keyTime = 0;
            float m_keyMaxTime = 0.4;

            bool m_isRunning = false;


            bool m_ishovered;
            float butWidth;
            bool isListVisible;
            void (*callback)(void*);
            List_Item activeItem;


            void Resizing();


    };
}
#endif // DROPLIST_H
