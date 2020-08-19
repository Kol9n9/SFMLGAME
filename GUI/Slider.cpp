#include "Slider.h"
namespace GUI{
    Slider::Slider(sf::RenderWindow *target, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK)
        : GUI(target,new Point(0,0),new Point(0,0),c_IDLE,c_HOVER,c_CLICK)
    {
        //ctor
    }

    Slider::~Slider()
    {
        //dtor
    }

    void Slider::update()
    {
        updateGUIState();
        switch(this->getGUIStatus())
        {
            case GUI_STATUS::IDLE:
            {
                this->slider.setFillColor(this->getColorIDLE());
                break;
            }
            case GUI_STATUS::HOVER:
            {
                this->slider.setFillColor(this->getColorHOVER());
                break;
            }
            case GUI_STATUS::CLICKING:
            {
                this->slider.setFillColor(this->getColorCLICK());
                break;
            }
        }
    }
    void Slider::render()
    {
        this->target->draw(this->slider);
    }
}
