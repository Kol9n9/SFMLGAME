#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <Label.h>

namespace GUI{
    const int GUI_TEXT_BACKSPACE = 8;
    const int GUI_TEXT_ESCAPE = 27;

    class TextInput : public Label
    {
        public:
            TextInput(const sf::Vector2f &start_pos, const sf::Vector2f &sizes, sf::Font *font, unsigned int textSize,sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            virtual ~TextInput();
            void update();
            void render(sf::RenderTarget *target);
            void setPosition(const sf::Vector2f &pos);
            void setSize(const sf::Vector2f &size);
            void inputSymbol(const uint32_t &symbol);
            bool const &Activated() const { return isActive;}
        protected:

        private:
            bool isActive;
            sf::RectangleShape text_box;


            void Moving();
            void Resizing();

    };
}
#endif // TEXTINPUT_H
