#ifndef DROPLIST_H
#define DROPLIST_H

#include <GUI.h>
#include "Button.h"

#include "List.h"

namespace GUI{
    class Droplist : public GUI
    {
        public:
            Droplist(sf::RenderWindow *target, const Point *start_pos, const sf::Vector2f &sizes, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            virtual ~Droplist();
            void update();
            void render();
            void setList(List *list);
            void Moving();
            void setPosition(const sf::Vector2f &pos);
            void setSize(const sf::Vector2f &size);
        protected:

        private:
            sf::RectangleShape shape;
            Button *but;
            sf::Text text;
            List *list;
            float butWidth;
            bool isListVisible;
            void (*callback)(void*);
            List_Item activeItem;
            void Resizing();

    };
}
#endif // DROPLIST_H
