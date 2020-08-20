#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <GUI.h>

namespace GUI{
    class Progressbar : public GUI
    {
        public:
            Progressbar(const Point *start_pos, const sf::Vector2f &sizes, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            Progressbar(const Point *start_pos, const float &rad, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            virtual ~Progressbar();
            void update();
            void render(sf::RenderTarget *target);
            void setPercent(const int &n) {if(n < 0 || n > 100) return; percents = n; isUpdatedPercent = true;}
            bool &isFilled() { return isFill; }
            void setSize(const sf::Vector2f &size);
            void setPosition(const sf::Vector2f &pos);
            void Moving();
            enum TYPE{
                BOX,
                CIRCLE
            };
        protected:

        private:
            sf::RectangleShape bar_box;
            sf::RectangleShape filling_box;

            sf::Vector2f startCirclePoint;
            sf::Text text;
            float lengthCircle;

            float radius;
            float onePercent;
            int percents;
            bool isFill;
            TYPE type;

            void updateOnePercent();
            bool isUpdatedPercent;
            void updateCircleLength();
            void Resizing();


    };
}
#endif // PROGRESSBAR_H
