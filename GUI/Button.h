#ifndef BUTTON_H
#define BUTTON_H
#include "Button_interface.h"
#include "Label.h"

namespace GUI{

    class Button : public Button_interface
    {
        public:
            Button(const Point *start_pos, const sf::Vector2f &sizes, Label *str,bool isV,sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            Button(const Point *start_pos, const sf::Vector2f &sizes, const std::string &str,bool isV,sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            virtual ~Button();
            void update();
            void render(sf::RenderTarget *target);
            void setBoxVisible(const bool st) {isBoxVisible = st;}
            bool &getBoxVisible() {return isBoxVisible;}
            void updateColor();
            void updateColor(const GUI_STATUS &status);
            void setPosition(const sf::Vector2f &pos);
            void updateTextPosition();
            void setSize(const sf::Vector2f &size);
            void setText(const sf::String &str);
        protected:

        private:
            Label *text;
            bool isBoxVisible;
            sf::Vector2f text_offset;
            void Moving();
            void Resizing();

    };
}
#endif // BUTTON_H
