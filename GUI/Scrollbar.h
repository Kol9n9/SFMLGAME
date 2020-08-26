#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <GUI.h>

namespace GUI{
    class Scrollbar : public GUI
    {
        public:
            Scrollbar(const sf::Vector2f &start_pos, const sf::Vector2f &sizes, sf::Color scr_IDLE, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            virtual ~Scrollbar();
            void render(sf::RenderTarget *target);
            void update();
            void setSliderCountPos(const int& c) { sliderCountPos = c;updateSliderSize();}
            void setSliderIndex(const int& in) { sliderCurrentIndex = in;updateSliderPos();}
            int const &getSliderIndex() { return this->sliderCurrentIndex;}

            enum TYPE{
                HORIZONTAL,
                VERTICAL
            };
            void Moving();
            void setPosition(const sf::Vector2f &pos);
            void setSize(const sf::Vector2f &newSize);
            int getNewIndex() {return (isUpdateIndex) ? sliderCurrentIndex : -1;}
            void setScrollingArea(const Point &start, const Point &end) {startScrollingArea = start; endScrollingArea = end;}
            static bool isSelectedSlider;
        protected:

        private:
            TYPE type;
            int sliderCountPos;
            int sliderCurrentIndex;
            sf::RectangleShape scrollbar;
            sf::RectangleShape slider;


            sf::Color sliderIDLE;
            sf::Color sliderHOVER;
            sf::Color sliderCLICK;
            sf::Vector2f mouse_offset;
            Point startScrollingArea;
            Point endScrollingArea;

            bool isSliderContains();
            bool isScrollingAreaContains();
            void updateSliderSize();
            bool isUpdateIndex;
            void updateSliderPos();

    };
}
#endif // SCROLLBAR_H
