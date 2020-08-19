#ifndef SLIDER_H
#define SLIDER_H

#include <GUI.h>

namespace GUI{
    class Slider : public GUI
    {
        public:
            Slider(sf::RenderWindow *target, const Point *start_pos, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            virtual ~Slider();
            void update();
            void render();
            sf::RectangleShape &getSlider(){return this->slider;}
            void setPosition(const sf::Vector2f&);
            void setSize()
        protected:

        private:
            sf::RectangleShape slider;

};
}
#endif // SLIDER_H
