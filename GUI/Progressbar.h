#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <GUI.h>
#include "Label.h"
namespace GUI{
    class Progressbar : public GUI
    {
        public:
            Progressbar(const sf::Vector2f &start_pos, const sf::Vector2f &sizes, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            Progressbar(const sf::Vector2f &start_pos, const float &rad, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            virtual ~Progressbar();
            void update();
            void render(sf::RenderTarget *target);
            void setPercent(const int &n) {if(n < 0 || n > 100) return; percents = n; isUpdatedPercent = true;}
            bool &isFilled() { return isFill; }
            void setSize(const sf::Vector2f &size);
            void setPosition(const sf::Vector2f &pos);
            void setOutlineThickness(const int &value) { bar_box.setOutlineThickness(value); m_outline = value; updateFillingBoxPosition();}
            void setOutlineColor(const sf::Color &color) { bar_box.setOutlineColor(color);}
            void setLabel(Label *label);
            void setLabelText(const sf::String &str);
            void Moving();
            enum TYPE{
                BOX = 0,
                CIRCLE
            };
        protected:

        private:
            sf::RectangleShape bar_box;
            sf::RectangleShape filling_box;

            sf::Vector2f startCirclePoint;
            Label *m_label;

            sf::Vector2f m_label_offset;

            float lengthCircle;

            float radius;
            float onePercent;
            int percents;
            bool isFill;
            TYPE type;

            int m_outline;

            void updateOnePercent();
            bool isUpdatedPercent;
            void updateCircleLength();
            void updateFillingBoxPosition();
            void Resizing();
            void updateTextPosition();


    };
}
#endif // PROGRESSBAR_H
