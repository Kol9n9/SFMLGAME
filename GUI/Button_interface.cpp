#include "Button_interface.h"
namespace GUI{
    Button_interface::Button_interface(const Point *start_pos, const sf::Vector2f &sizes,sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK)
        : GUI(start_pos,sizes,c_IDLE,c_HOVER,c_CLICK)
    {
        this->buttonShape.setPosition(this->getStartPoint().x, this->getStartPoint().y);
        this->buttonShape.setSize(this->getSizes());
        //ctor
    }

    Button_interface::~Button_interface()
    {
        //dtor
    }

}
