#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <Button_interface.h>

namespace GUI{
    class Checkbox : public Button_interface
    {
        public:
            Checkbox(sf::RenderWindow *target, const Point *start_pos, const int& sz, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            virtual ~Checkbox();
            void update();
            void render();
            bool &isChecked() {return isCheck;}
            void Moving();
            void setPosition(const sf::Vector2f &pos);
            void setSize(const sf::Vector2f &size);
        protected:

        private:
            int lineWidth;
            sf::RectangleShape line1;
            sf::RectangleShape line2;
            bool isCheck;
            void updateLinesPosition();
            void updateLinesSize();
            void Resizing();
    };
}
#endif // CHECKBOX_H
