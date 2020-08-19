#include "Droplist.h"
namespace GUI{
    Droplist::Droplist(sf::RenderWindow *target, const Point *start_pos, const sf::Vector2f &sizes, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK)
        : GUI(target,start_pos,sizes,c_IDLE,c_HOVER,c_CLICK)
    {
        this->shape.setPosition(sf::Vector2f(this->getStartPoint().x,this->getStartPoint().y));
        this->shape.setSize(this->getSizes());
        this->shape.setOutlineColor(sf::Color(235,235,235));
        this->shape.setOutlineThickness(4);
        this->butWidth = 30;
        float butPosX = this->getStartPoint().x + this->getSizes().x;
        this->but = new Button(this->target,new Point(butPosX - this->butWidth,this->getStartPoint().y),sf::Vector2f(this->butWidth,this->getSizes().y),
                               "",true,sf::Color(127,127,127),sf::Color(0,127,0),sf::Color(0,127,0));
        this->list = nullptr;
        this->text.setString("");
        this->isListVisible = false;
        //ctor
    }

    Droplist::~Droplist()
    {
        delete this->but;
        delete this->list;
        //dtor
    }
    void Droplist::update()
    {
        this->updateGUIState();
        //this->but->update();
        this->but->updateColor(this->getGUIStatus());
        switch(this->getGUIStatus())
        {

            case GUI_STATUS::IDLE:
            {
                this->shape.setFillColor(this->getColorIDLE());
                break;
            }
            case GUI_STATUS::HOVER:
            {
                this->shape.setFillColor(this->getColorHOVER());
                break;
            }
            case GUI_STATUS::CLICK:
            {
                this->isListVisible = true;
                break;
            }
        }

        if(this->list && this->isListVisible)
        {
            this->list->update();
            if(!this->list->isSliderSelected() && this->getMouseClickEvent() == MOUSE_CLICK_EVENTS::LEFTCLICK && this->list->getGUIStatus() != GUI_STATUS::HOVER
               && this->list->getGUIStatus() != GUI_STATUS::CLICK && this->list->getGUIStatus() != GUI_STATUS::CLICKING)
                this->isListVisible = false;
            if(this->list->getIsItemSelected())
            {
                this->activeItem = this->list->getActiveItem();
                this->text = this->activeItem.text->getText();
                this->isListVisible = false;
            }
        }
        if(this->list)
        {
            if(this->list->isItemsDrop())
                this->text.setString("");
        }
    }
    void Droplist::render()
    {

        if(this->isBoxShow)
        {
            sf::RectangleShape debug_shape;
            debug_shape.setOutlineColor(sf::Color::Red);
            debug_shape.setOutlineThickness(5);
            debug_shape.setPosition(sf::Vector2f(this->getStartPoint().x,this->getStartPoint().y));
            debug_shape.setSize(this->getSizes());
            this->target->draw(debug_shape);
        }
        this->target->draw(this->shape);
        this->target->draw(this->but->getBox());
        if(this->list && this->isListVisible) this->list->render();
        this->text.setPosition(sf::Vector2f(this->getStartPoint().x,this->getStartPoint().y));
        this->target->draw(this->text);
    }
    void Droplist::setList(List *list)
    {
        this->list = list;
        this->list->setSize(sf::Vector2f(this->getSizes().x,this->list->getSizes().y));
        this->list->setPosition(sf::Vector2f(this->getStartPoint().x,this->getStartPoint().y+this->getSizes().y+this->list->getBoxBorder()));

    }
    void Droplist::setPosition(const sf::Vector2f &pos)
    {
        this->setStartPoint(Point(pos.x,pos.y));
        this->shape.setPosition(pos);
        this->but->setPosition(sf::Vector2f(pos.x + this->getSizes().x - this->butWidth, pos.y));
        this->list->setPosition(sf::Vector2f(pos.x,pos.y+this->getSizes().y + this->list->getBoxBorder()));
    }
    void Droplist::Moving()
    {
        this->setPosition(sf::Vector2f(static_cast<sf::Vector2f>(this->getMousePos()) - this->getMoveOffset()));
    }
    void Droplist::setSize(const sf::Vector2f &size)
    {
        this->setSizes(size);
        this->shape.setSize(size);
        if(this->list) this->list->setSize(sf::Vector2f(size.x,this->list->getSizes().y));
        this->but->setSize(sf::Vector2f(this->butWidth,size.y));
    }
    void Droplist::Resizing()
    {
        this->setSize(this->getSizes());
        this->but->setPosition(sf::Vector2f(this->getStartPoint().x + this->getSizes().x - this->butWidth, this->getStartPoint().y));
        if(this->list) this->list->setPosition(sf::Vector2f(this->getStartPoint().x,this->getStartPoint().y+this->getSizes().y+this->list->getBoxBorder()));
    }
}
