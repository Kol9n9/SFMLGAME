#include "Scrollbar.h"
namespace GUI{
    bool Scrollbar::isSelectedSlider = false;
    Scrollbar::Scrollbar(const sf::Vector2f &start_pos, const sf::Vector2f &sizes, sf::Color scr_IDLE, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK)
        : GUI(start_pos,sizes,scr_IDLE,scr_IDLE,scr_IDLE), sliderIDLE(c_IDLE), sliderHOVER(c_HOVER), sliderCLICK(c_CLICK)
    {
        this->scrollbar.setFillColor(scr_IDLE);
        this->scrollbar.setPosition(this->getStartPos());
        this->scrollbar.setSize(this->getSizes());

        this->type = (this->getSizes().x >= this->getSizes().y) ? TYPE::HORIZONTAL : TYPE::VERTICAL;

        this->slider.setPosition(this->getStartPos());
        this->slider.setFillColor(sliderIDLE);
        this->sliderCountPos = 2;

        //ctor
        this->updateSliderSize();
        this->sliderCurrentIndex = 0;

        this->isUpdateIndex = false;
        this->startScrollingArea = Point(this->getStartPos().x,this->getStartPos().y);
        this->endScrollingArea = Point(this->getStartPos().x + this->getSizes().x ,this->getStartPos().y + this->getSizes().y);
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
            this->mouse_offset = sf::Vector2f(GUI::mousePos.x - this->slider.getPosition().x, GUI::mousePos.y - this->slider.getPosition().y);
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
    void Scrollbar::render(sf::RenderTarget *target)
    {
        if(!this->isVisibled()) return;
        if(this->isBoxShow)
        {
            sf::RectangleShape debug_shape;
            debug_shape.setOutlineColor(sf::Color::Red);
            debug_shape.setOutlineThickness(5);
            debug_shape.setPosition(this->getStartPos());
            debug_shape.setSize(this->getSizes());
            target->draw(debug_shape);
        }
        target->draw(this->scrollbar);
        target->draw(this->slider);
    }
    bool Scrollbar::isSliderContains()
    {
        return GUI::mousePos.x >= this->slider.getPosition().x && GUI::mousePos.x <= this->slider.getPosition().x + this->slider.getSize().x
            && GUI::mousePos.y >= this->slider.getPosition().y && GUI::mousePos.y <= this->slider.getPosition().y + this->slider.getSize().y;
    }
    bool Scrollbar::isScrollingAreaContains()
    {
        return GUI::mousePos.x >= this->startScrollingArea.x && GUI::mousePos.x <= this->endScrollingArea.x
            && GUI::mousePos.y >= this->startScrollingArea.y && GUI::mousePos.y <= this->endScrollingArea.y;
    }
    void Scrollbar::updateSliderPos()
    {
        float sliderPosX = this->getStartPos().x;
        float sliderPosY = this->getStartPos().y;

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
        this->setStartPos(pos);
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
        sf::Vector2f newPos(GUI::mousePos.x - this->mouse_offset.x,GUI::mousePos.y - this->mouse_offset.y);

        this->isUpdateIndex = false;
        int newIndex = -1;
        if(this->type == TYPE::HORIZONTAL)
        {
            float max_limit_x = this->getStartPos().x + this->getSizes().x - this->slider.getSize().x;
            float min_limit_x = this->getStartPos().x;
            float limit_y = this->getStartPos().y;
            if(newPos.x > max_limit_x) newPos.x = max_limit_x;
            if(newPos.x < min_limit_x) newPos.x = min_limit_x;
            newPos.y = limit_y;
            newIndex = (this->slider.getPosition().x - this->getStartPos().x + this->slider.getSize().x / 2) / (this->getSizes().x / this->sliderCountPos);
        }
        if(this->type == TYPE::VERTICAL)
        {
            float limit_x = this->getStartPos().x;
            float min_limit_y = this->getStartPos().y;
            float max_limit_y = this->getStartPos().y + this->getSizes().y - this->slider.getSize().y;
            if(newPos.y > max_limit_y) newPos.y = max_limit_y;
            if(newPos.y < min_limit_y) newPos.y = min_limit_y;
            newPos.x = limit_x;
            newIndex = (this->slider.getPosition().y - this->getStartPos().y + this->slider.getSize().x / 2) / (this->getSizes().y / this->sliderCountPos);
        }
        if(this->sliderCurrentIndex != newIndex)
        {
            this->isUpdateIndex = true;
        }
        this->sliderCurrentIndex = newIndex;
        this->slider.setPosition(newPos);
    }
}
