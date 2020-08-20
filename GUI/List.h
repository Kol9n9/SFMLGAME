#ifndef LIST_H
#define LIST_H

#include <GUI.h>
#include "Label.h"
#include "Scrollbar.h"

namespace GUI{
    struct List_Item{
                Label *text;
                void(*call_back)(void*);
                void *call_back_object;
                List_Item()
                {
                    text = nullptr;
                    call_back = nullptr;
                    call_back_object = nullptr;
                }
                List_Item(Label *t)
                {
                    text = t;
                    call_back = nullptr;
                    call_back_object = nullptr;
                }
                List_Item(Label *t, void(*c_b)(void*), void *obj)
                {
                    text = t;
                    call_back = c_b;
                    call_back_object = obj;
                }
            };
    class List : public GUI
    {
        public:


            List(const Point *start_pos, const sf::Vector2f &sizes, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            virtual ~List();
            void update();
            void render(sf::RenderTarget *target);
            void insert(Label*,void(*cb)(void*),void *);
            void insert(Label*);
            void changeItem(const int&);
            void setItemCount(const int &c) {item_height_count = c; updateItemHeight();}
            void itemUp();
            void itemDown();
            void itemDelete();
            void itemInsert(const std::string &str, sf::Font *font, unsigned int textSize,sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            void itemDrop();
            void setPosition(const sf::Vector2f &pos);
            void setSize(const sf::Vector2f &size);
            void setBoxBorder(const int &sz) { boxBorder = sz; list_box.setOutlineThickness(sz);}
            int &getBoxBorder() {return boxBorder;}

            bool &getIsItemSelected() {return isItemSelected;}
            List_Item &getActiveItem();
            bool &isItemsDrop() {return isDropping;}
            bool &isSliderSelected() { return isSliderSelect;}

        protected:

        private:


            //std::map<int,Text*> items_text;
            std::map<int,List_Item> items;

            Scrollbar *scr;
            sf::RectangleShape list_box;
            sf::RectangleShape item_box;
            int active_item;
            int item_height;
            int item_height_count;
            int item_current_head;
            float sliderSize;
            int currentIndex;
            bool isSliderShowed;
            bool isSliderHidden;
            bool isDropping;
            int boxBorder;
            bool isItemSelected;
            bool isSliderSelect;

            void Moving();
            void Resizing();
            void updateItemHeight();

            sf::Vector2f minSize;
    };
}
#endif // LIST_H
