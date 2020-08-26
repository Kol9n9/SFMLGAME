#ifndef BUTTON_INTERFACE_H
#define BUTTON_INTERFACE_H
#include "GUI.h"

namespace GUI{
    class Button_interface : public GUI
    {
        public:
            Button_interface(const sf::Vector2f &start_pos, const sf::Vector2f &sizes,sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            virtual ~Button_interface();
            sf::RectangleShape &getBox() {return buttonShape;}

        protected:

        private:
            sf::RectangleShape buttonShape;


    };
}
#endif // BUTTON_INTERFACE_H
