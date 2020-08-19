#ifndef Label_H
#define Label_H
#include "GUI.h"

namespace GUI{
    class Label : public GUI
    {
        public:
            Label(sf::RenderWindow *target, const Point *start_pos, const sf::String &str, sf::Font *font, unsigned int textSize,sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            virtual ~Label();
            void update();
            void render();
            void setText(const std::string&);
            void setFont(sf::Font *font);
            void setTextSize(const unsigned int);
            sf::Text &getText() {return this->text;}
            sf::Vector2f getTextBoxSize() {return sf::Vector2f(text.getLocalBounds().width, text.getLocalBounds().height);}
            void setPosition(const sf::Vector2f&);
            void updateColor();
            void updateColor(const GUI_STATUS&);
            void setBoxSize(const sf::Vector2f&);
            void setScale(const sf::Vector2f &scale);

        protected:
            sf::String str;
            sf::Font *font;
            unsigned int textSize;
            sf::Text text;
            void setTextBoxSize();


        private:
            void Moving();
            void Resizing();


    };
}
#endif // TEXT_H
