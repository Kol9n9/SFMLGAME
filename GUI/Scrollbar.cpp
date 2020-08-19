#include "Scrollbar.h"
namespace GUI{
    bool Scrollbar::isSelectedSlider = false;
    Scrollbar::Scrollbar(sf::RenderWindow *target, const Point *start_pos, const sf::Vector2f &sizes, sf::Color scr_IDLE, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK)
        : GUI(target,start_pos,sizes,scr_IDLE,scr_IDLE,scr_IDLE), sliderIDLE(c_IDLE), sliderHOVER(c_HOVER), sliderCLICK(c_CLICK)
    {
        this->scrollbar.setFillColor(scr_IDLE);
        this->scrollbar.setPosition(sf::Vector2f(this->getStartPoint().x,this->getStartPoint().y));
        this->scrollbar.setSize(this->getSizes());

        this->type = (this->getSizes().x >= this->getSizes().y) ? TYPE::HORIZONTAL : TYPE::VERTICAL;

        this->slider.setPosition(sf::Vector2f(this->getStartPoint().x,this->getStartPoint().y));
        this->slider.setFillColor(sliderIDLE);
        this->sliderCountPos = 2;

        //ctor
        this->updateSliderSize();
        this->sliderCurrentIndex = 0;

        this->isUpdateIndex = false;
        this->startScrollingArea = Point(this->getStartPoint().x,this->getStartPoint().y);
        this->endScrollingArea = Point(this->getStartPoint().x + this->getSizes().x ,this->getStartPoint().y + this->getSizes().y);
    }
    Scrollbar::~Scrollbar()
    {
        //dtor
    }
    void Scrollbar::update()
    {
        this->isUpdateIndex = false;
        updateGUIState();
        //this->isUpdateIndex = false;
        if(this->getMoving() && this->getMouseClickEvent() == MOUSE_CLICK_EVENTS::NONECLICK)
        {
            this->endMove();
            Scrollbar::isSelectedSlider = false;
        }
        this->slider.setFillColor(sliderIDLE);
        if(this->getGUIStatus() == GUI_STATUS::HOVER && isSliderContains()) this->slider.setFillColor(sliderHOVER);
        if(this->getGUIStatus() == GUI_STATUS::CLICKING && isSliderContains()) this->slider.setFillColor(sliderCLICK);
        if(this->getMoving()) this->slider.setFillColor(sliderCLICK);
        if(!GUI::isAnyGUICorning && !Scrollbar::isSelectedSlider && this->isSliderContains() && !this->getMoving() && this->getMouseClickEvent() == MOUSE_CLICK_EVENTS::LEFTCLICK)
        {
            this->mouse_offset = sf::Vector2f(this->getMousePos().x - this->slider.getPosition().x,this->getMousePos().y - this->slider.getPosition().y);
            Scrollbar::isSelectedSlider = true;
            this->startMove();
        }
        if(this->isScrollingAreaContains())
        {
            //std::cout << "this->sliderCountPos = " << this->sliderCountPos << "\n";
            if(this->getMouseWheelEvent() == MOUSE_WHEEL_EVENTS::WHEELDOWN && this->sliderCountPos != 0 && this->sliderCurrentIndex != this->sliderCountPos-1)
            {
                this->isUpdateIndex = true;
                this->sliderCurrentIndex++;
                this->setMouseWheelEvent(MOUSE_WHEEL_EVENTS::NONEWHEEL);
                this->updateSliderPos();
            }
            if(this->getMouseWheelEvent() == MOUSE_WHEEL_EVENTS::WHEELUP && this->sliderCountPos != 0 && this->sliderCurrentIndex != 0)
            {
                this->isUpdateIndex = true;
                this->sliderCurrentIndex--;
                this->setMouseWheelEvent(MOUSE_WHEEL_EVENTS::NONEWHEEL);
                this->updateSliderPos();
            }
        }

    }
    void Scrollbar::render()
    {
        if(!this->isVisibled()) return;
        if(this->isBoxShow)
        {
            sf::RectangleShape debug_shape;
            debug_shape.setOutlineColor(sf::Color::Red);
            debug_shape.setOutlineThickness(5);
            debug_shape.setPosition(sf::Vector2f(this->getStartPoint().x,this->getStartPoint().y));
            debug_shape.setSize(this->getSizes());
            this->target->draw(debug_shape);
        }
        this->target->draw(this->scrollbar);
        this->target->draw(this->slider);
    }
    bool Scrollbar::isSliderContains()
    {
        return this->getMousePos().x >= this->slider.getPosition().x && this->getMousePos().x <= this->slider.getPosition().x + this->slider.getSize().x
            && this->getMousePos().y >= this->slider.getPosition().y && this->getMousePos().y <= this->slider.getPosition().y + this->slider.getSize().y;
    }
    bool Scrollbar::isScrollingAreaContains()
    {
        return this->getMousePos().x >= this->startScrollingArea.x && this->getMousePos().x <= this->endScrollingArea.x
            && this->getMousePos().y >= this->startScrollingArea.y && this->getMousePos().y <= this->endScrollingArea.y;
    }
    void Scrollbar::updateSliderPos()
    {
        float sliderPosX = this->getStartPoint().x;
        float sliderPosY = this->getStartPoint().y;

        if(this->type == TYPE::HORIZONTAL) sliderPosX += (this->getSizes().x / this->sliderCountPos) * this->sliderCurrentIndex;
        else sliderPosY += (this->getSizes().y / this->sliderCountPos) * this->sliderCurrentIndex;

        this->slider.setPosition(sliderPosX,sliderPosY);
    }
    void Scrollbar::updateSliderSize()
    {
        float sliderPosX = this->getSizes().x;
        float sliderPosY = this->getSizes().y;
        if(this->type == TYPE::HORIZONTAL) sliderPosX /= this->sliderCountPos;
        else sliderPosY /= this->sliderCountPos;
        this->slider.setSize(sf::Vector2f(sliderPosX,sliderPosY));
    }
    void Scrollbar::setPosition(const sf::Vector2f &pos)
    {
        this->setStartPoint(Point(pos.x,pos.y));
        this->slider.setPosition(pos);
        this->scrollbar.setPosition(pos);
    }
    void Scrollbar::setSize(const sf::Vector2f &newSize)
    {
        this->setSizes(newSize);
        this->scrollbar.setSize(this->getSizes());
        this->type = (this->getSizes().x >= this->getSizes().y) ? TYPE::HORIZONTAL : TYPE::VERTICAL;
        this->updateSliderSize();
    }
    void Scrollbar::Moving()
    {
        sf::Vector2f newPos(this->getMousePos().x - this->mouse_offset.x,this->getMousePos().y - this->mouse_offset.y);

        this->isUpdateIndex = false;
        int newIndex = -1;
        if(this->type == TYPE::HORIZONTAL)
        {
            float max_limit_x = this->getStartPoint().x + this->getSizes().x - this->slider.getSize().x;
            float min_limit_x = this->getStartPoint().x;
            float limit_y = this->getStartPoint().y;
            if(newPos.x > max_limit_x) newPos.x = max_limit_x;
            if(newPos.x < min_limit_x) newPos.x = min_limit_x;
            newPos.y = limit_y;
            newIndex = (this->slider.getPosition().x - this->getStartPoint().x + this->slider.getSize().x / 2) / (this->getSizes().x / this->sliderCountPos);
        }
        if(this->type == TYPE::VERTICAL)
        {
            float limit_x = this->getStartPoint().x;
            float min_limit_y = this->getStartPoint().y;
            float max_limit_y = this->getStartPoint().y + this->getSizes().y - this->slider.getSize().y;
            if(newPos.y > max_limit_y) newPos.y = max_limit_y;
            if(newPos.y < min_limit_y) newPos.y = min_limit_y;
            newPos.x = limit_x;
            newIndex = (this->slider.getPosition().y - this->getStartPoint().y + this->slider.getSize().x / 2) / (this->getSizes().y / this->sliderCountPos);
        }
        if(this->sliderCurrentIndex != newIndex)
        {
            this->isUpdateIndex = true;
        }
        this->sliderCurrentIndex = newIndex;
        this->slider.setPosition(newPos);
    }
}
