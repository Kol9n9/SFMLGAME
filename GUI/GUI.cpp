#include "GUI.h"
namespace GUI{
    MOUSE_CLICK_EVENTS GUI::mouse_click_event = MOUSE_CLICK_EVENTS::NONECLICK;
    MOUSE_WHEEL_EVENTS GUI::mouse_wheel_event = MOUSE_WHEEL_EVENTS::NONEWHEEL;
    sf::Vector2i GUI::mousePos = sf::Vector2i(0,0);
    bool GUI::isAnyGUIMoving = false;
    bool GUI::isAnyGUICorning = false;
    bool GUI::mouse_move_event = false;
    GUI::GUI(const sf::Vector2f &start_pos, const sf::Vector2f &sizes,sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK)
        : start_pos(start_pos), sizes(sizes), color_IDLE(c_IDLE), color_HOVER(c_HOVER), color_CLICK(c_CLICK)
    {
        this->cb_Click = nullptr;
        this->status = GUI_STATUS::IDLE;
        this->isMoving = false;
        this->isClicking = false;
        this->isVis = true;
        this->a_a = nullptr;
        this->isCorner = false;
        this->isBoxShow = false;
        this->target = nullptr;
        //ctor
    }

    GUI::~GUI()
    {
        //dtor
    }
    void GUI::updateGUIState()
    {



        if(this->isMoving)
        {
            std::cout << "pos x = " << start_pos.x << " y = " << start_pos.y << "\n";
            this->Moving();
            return;
        }
        if(this->isCorner && GUI::mouse_click_event == MOUSE_CLICK_EVENTS::LEFTCLICK)
        {

            sf::Vector2f newSize(this->mousePos.x - this->start_pos.x,this->mousePos.y - this->start_pos.y);
            if(newSize.x < 0) newSize.x = 0;
            if(newSize.y < 0) newSize.y = 0;
            this->sizes = newSize;
            std::cout << "sizes x = " << sizes.x << " y = " << sizes.y << "\n";
            this->Resizing();
            return;
        }
        if(this->status == GUI_STATUS::IDLE && (GUI::mouse_click_event == MOUSE_CLICK_EVENTS::LEFTCLICK || GUI::mouse_click_event == MOUSE_CLICK_EVENTS::RIGHTCLICK)) return;

        if(this->status == GUI_STATUS::CLICKING && GUI::mouse_click_event != MOUSE_CLICK_EVENTS::NONECLICK)
        {
            if(!this->isContains())
            {
                this->status = GUI_STATUS::IDLE;
            }
            return;
        }
        if(this->status == GUI_STATUS::CLICKING && GUI::mouse_click_event == MOUSE_CLICK_EVENTS::NONECLICK)
        {
            //std::cout << "Clicked: " << this << "\n";
            if(this->cb_Click != nullptr)
            {
                this->cb_Click(this,a_a);
            }
            this->status = GUI_STATUS::CLICK;
            return;

        }

        this->status = GUI_STATUS::IDLE;

        if(this->isContains())
        {
            this->status = GUI_STATUS::HOVER;
            if(GUI::mouse_click_event == MOUSE_CLICK_EVENTS::LEFTCLICK)
            {
                this->status = GUI_STATUS::CLICKING;
            }
        }
        //this->isCorner = false;
        if(!this->isContainCorner() && this->isCorner)
        {
            GUI::isAnyGUICorning = false;
            this->isCorner = false;
            sf::Cursor cursor;
            cursor.loadFromSystem(sf::Cursor::Arrow);
            this->target->setMouseCursor(cursor);
        }

    }
    bool GUI::isContains()
    {
        return (this->mousePos.x >= this->start_pos.x && this->mousePos.x <= this->start_pos.x+this->sizes.x &&
           this->mousePos.y >= this->start_pos.y && this->mousePos.y <= this->start_pos.y+this->sizes.y);
    }
    bool GUI::isContainCorner()
    {
        return (this->mousePos.x >= this->start_pos.x + this->sizes.x - 5 && this->mousePos.x <= this->start_pos.x + this->sizes.x + 5 &&
                this->mousePos.y >= this->start_pos.y + this->sizes.y - 5 && this->mousePos.y <= this->start_pos.y + this->sizes.y + 5);
    }

    void GUI::startMove()
    {
        if(GUI::isAnyGUIMoving) return;
        GUI::isAnyGUIMoving = true;
        this->isMoving = true;
        this->move_offset = sf::Vector2f(this->mousePos.x - this->start_pos.x,this->mousePos.y - this->start_pos.y);
    }
    void GUI::endMove()
    {
        GUI::isAnyGUIMoving = false;
        this->isMoving = false;
    }
    void GUI::Resized()
    {
        if(GUI::isAnyGUICorning) return;
        if(!this->target)
        {
            std::cout << "Target not found. Please input setTarget(sf::RenderWindow *target)\n";
            return;
        }
        if(this->isContainCorner())
        {
            std::cout << "1\n";
            GUI::isAnyGUICorning = true;
            this->isCorner = true;
            sf::Cursor cursor;
            std::cout << "2\n";
            cursor.loadFromSystem(sf::Cursor::SizeTopLeftBottomRight);
            std::cout << "2.5\n";
            this->target->setMouseCursor(cursor);
            std::cout << "3\n";
        }
    }
    void GUI::updateEvents(sf::RenderWindow *target, sf::Event &events)
    {
        mousePos = static_cast<sf::Vector2i>(target->mapPixelToCoords(sf::Mouse::getPosition(*target)));
        GUI::mouse_wheel_event = MOUSE_WHEEL_EVENTS::NONEWHEEL;
        GUI::mouse_move_event = false;
        switch(events.type)
        {
            case sf::Event::MouseButtonPressed:
            {

                switch(events.mouseButton.button)
                {
                    case sf::Mouse::Left:
                    {
                        if(GUI::mouse_click_event == MOUSE_CLICK_EVENTS::RIGHTCLICK)
                            GUI::mouse_click_event = MOUSE_CLICK_EVENTS::BOTHCLICK;
                        else GUI::mouse_click_event = MOUSE_CLICK_EVENTS::LEFTCLICK;
                        break;
                    }
                    case sf::Mouse::Right:
                    {
                        if(GUI::mouse_click_event == MOUSE_CLICK_EVENTS::LEFTCLICK)
                            GUI::mouse_click_event = MOUSE_CLICK_EVENTS::BOTHCLICK;
                        else GUI::mouse_click_event = MOUSE_CLICK_EVENTS::RIGHTCLICK;
                        break;
                    }
                    case sf::Mouse::Middle:
                    {
                        break;
                    }
                }
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                switch(events.mouseButton.button)
                {
                    case sf::Mouse::Left:
                    {

                        if(GUI::mouse_click_event == MOUSE_CLICK_EVENTS::BOTHCLICK)
                            GUI::mouse_click_event = MOUSE_CLICK_EVENTS::RIGHTCLICK;
                        else GUI::mouse_click_event = MOUSE_CLICK_EVENTS::NONECLICK;
                        break;
                    }
                    case sf::Mouse::Right:
                    {
                        if(GUI::mouse_click_event == MOUSE_CLICK_EVENTS::BOTHCLICK)
                            GUI::mouse_click_event = MOUSE_CLICK_EVENTS::LEFTCLICK;
                        else GUI::mouse_click_event = MOUSE_CLICK_EVENTS::NONECLICK;
                        break;
                    }
                    case sf::Mouse::Middle:
                    {
                        break;
                    }
                }
                break;
            }
            case sf::Event::MouseWheelScrolled:
            {
                switch(events.mouseWheelScroll.wheel)
                {
                    case sf::Mouse::VerticalWheel:
                    {
                        if(events.mouseWheelScroll.delta == 1) GUI::mouse_wheel_event = MOUSE_WHEEL_EVENTS::WHEELUP;
                        else if(events.mouseWheelScroll.delta == -1) GUI::mouse_wheel_event = MOUSE_WHEEL_EVENTS::WHEELDOWN;
                        else GUI::mouse_wheel_event = MOUSE_WHEEL_EVENTS::NONEWHEEL;
                        break;
                    }
                    case sf::Mouse::HorizontalWheel:
                    {
                        std::cout << "wheel type: HorizontalWheel" << std::endl;
                        break;
                    }
                }
                break;
            }
            case sf::Event::MouseMoved:
            {
                GUI::mouse_move_event = true;
                break;
            }
        }
    }
}
