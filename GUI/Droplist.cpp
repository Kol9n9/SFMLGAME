#include "Droplist.h"
namespace GUI{
    bool Droplist::isAvailable = true;
    Droplist::Droplist(const sf::Vector2f &start_pos, const sf::Vector2f &sizes, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK)
        : GUI(start_pos,sizes,c_IDLE,c_HOVER,c_CLICK)
    {
        this->shape.setPosition(this->getStartPos());
        this->shape.setSize(this->getSizes());
        this->shape.setOutlineColor(sf::Color(235,235,235));
        this->shape.setOutlineThickness(4);
        this->butWidth = 30;
        float butPosX = this->getStartPos().x + this->getSizes().x;
        this->but = new Button(sf::Vector2f(butPosX - this->butWidth,this->getStartPos().y),sf::Vector2f(this->butWidth,this->getSizes().y),
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
    void Droplist::update(const float &dt)
    {
        if(this->m_isRunning)
        {
            this->m_keyTime += dt;
            if(this->m_keyTime >= this->m_keyMaxTime)
            {
                this->m_keyTime = 0;
                Droplist::isAvailable = true;
                this->m_isRunning = false;
            }
        }
        this->update();

    }
    void Droplist::update()
    {
        this->m_ishovered = false;
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
                if(Droplist::isAvailable)
                {
                    this->isListVisible = true;
                    this->m_isRunning = true;
                    Droplist::isAvailable = false;
                }

                break;
            }
        }
        if(this->list)
        {
            this->list->update();
            if(this->list->getGUIStatus() == GUI_STATUS::HOVER || this->list->getGUIStatus() == GUI_STATUS::CLICKING || this->list->getGUIStatus() == GUI_STATUS::CLICK)
                this->m_ishovered = true;
        }

        if(this->list && this->isListVisible)
        {

            if(!this->list->isSliderSelected() && this->getMouseClickEvent() == MOUSE_CLICK_EVENTS::LEFTCLICK && this->list->getGUIStatus() != GUI_STATUS::HOVER
               && this->list->getGUIStatus() != GUI_STATUS::CLICK && this->list->getGUIStatus() != GUI_STATUS::CLICKING)
            {
                this->isListVisible = false;
                this->m_isRunning = true;
                Droplist::isAvailable = false;
            }

            if(this->list->getIsItemSelected())
            {
                this->activeItem = this->list->getActiveItem();
                this->text = this->activeItem.text->getText();
                this->isListVisible = false;
                this->m_isRunning = true;
                Droplist::isAvailable = false;
            }
        }
        if(this->list)
        {
            if(this->list->isItemsDrop())
                this->text.setString("");
        }
    }
    void Droplist::render(sf::RenderTarget *target)
    {

        if(this->isBoxShow)
        {
            sf::RectangleShape debug_shape;
            debug_shape.setOutlineColor(sf::Color::Red);
            debug_shape.setOutlineThickness(5);
            debug_shape.setPosition(this->getStartPos());
            debug_shape.setSize(this->getSizes());
            target->draw(debug_shape);
        }
        target->draw(this->shape);
        target->draw(this->but->getBox());
        if(this->list && this->isListVisible) this->list->render(target);
        this->text.setPosition(this->getStartPos());
        target->draw(this->text);
    }
    void Droplist::setList(List *list)
    {
        this->list = list;
        this->list->setSize(sf::Vector2f(this->getSizes().x,this->list->getSizes().y));
        this->list->setPosition(sf::Vector2f(this->getStartPos().x,this->getStartPos().y+this->getSizes().y+this->list->getBoxBorder()));

    }
    void Droplist::setPosition(const sf::Vector2f &pos)
    {
        this->setStartPos(sf::Vector2f(pos.x,pos.y));
        this->shape.setPosition(pos);
        this->but->setPosition(sf::Vector2f(pos.x + this->getSizes().x - this->butWidth, pos.y));
        if(this->list) this->list->setPosition(sf::Vector2f(pos.x,pos.y+this->getSizes().y + this->list->getBoxBorder()));
    }
    void Droplist::insert(Label* label)
    {
        if(!this->list) return;
        this->list->insert(label);
    }
    void Droplist::setActiveItem(const int &index)
    {
        if(!this->list) return;
        this->list->changeItem(index);
        this->activeItem = this->list->getActiveItem();
        this->text = this->activeItem.text->getText();
    }
    void Droplist::Moving()
    {
        this->setPosition(sf::Vector2f(static_cast<sf::Vector2f>(GUI::mousePos) - this->getMoveOffset()));
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
        this->but->setPosition(sf::Vector2f(this->getStartPos().x + this->getSizes().x - this->butWidth, this->getStartPos().y));
        if(this->list) this->list->setPosition(sf::Vector2f(this->getStartPos().x,this->getStartPos().y+this->getSizes().y+this->list->getBoxBorder()));
    }
    void Droplist::setButWidth(const float &width)
    {
        this->but->setSize(sf::Vector2f(width,this->getSizes().y));
        this->but->setPosition(sf::Vector2f(this->getStartPos().x + this->getSizes().x - width, this->getStartPos().y));
        this->butWidth = width;
    }
    const bool &Droplist::isItemSelected()
    {
        if(!list)return false;
        return list->getIsItemSelected();
    }
}
