#include "Progressbar.h"

namespace GUI{
    Progressbar::Progressbar(const sf::Vector2f &start_pos, const sf::Vector2f &sizes, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK)
        : GUI(start_pos,sizes,c_IDLE,c_HOVER,c_CLICK)
    {
        this->bar_box.setFillColor(this->getColorIDLE());
        this->bar_box.setPosition(this->getStartPos());
        this->bar_box.setSize(this->getSizes());



        this->filling_box.setFillColor(this->getColorCLICK());
        this->filling_box.setSize(sf::Vector2f(0,0));
        this->percents = 0;
        this->onePercent = 0;
        this->isFill = false;
        this->type = TYPE::BOX;
        this->updateOnePercent();
        this->m_outline = 0;
        this->updateFillingBoxPosition();
        isUpdatedPercent = true;

        this->m_label = nullptr;
        //ctor
    }
    Progressbar::Progressbar(const sf::Vector2f &start_pos, const float &rad, sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK)
        : GUI(start_pos,sf::Vector2f(rad*2,rad*2),c_IDLE,c_HOVER,c_CLICK), radius(rad)
    {
        this->startCirclePoint = sf::Vector2f(this->getStartPos().x + this->radius, this->getStartPos().y);

        this->percents = 0;
        this->onePercent = 0;
        this->isFill = false;

        this->type = TYPE::CIRCLE;

        this->updateCircleLength();
        this->updateOnePercent();
        isUpdatedPercent = true;

        this->m_label = nullptr;

    }
    Progressbar::~Progressbar()
    {
        //dtor
    }
    void Progressbar::update()
    {
        this->isFill = false;
        this->updateGUIState();
        if(isUpdatedPercent)
        {
            if(this->type == TYPE::BOX)
            {
                sf::Vector2f size(this->onePercent * this->percents,this->getSizes().y);
                if(this->percents != 0)
                {
                    size.x += 2 * this->m_outline;
                    size.y += 2 * this->m_outline;
                }
                this->filling_box.setSize(size);
            }
            this->isUpdatedPercent = false;
            if(this->percents == 100) this->isFill = true;
        }

    }
    void Progressbar::render(sf::RenderTarget *target)
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
        if(this->type == TYPE::BOX)
        {
            target->draw(this->bar_box);
            target->draw(this->filling_box);
        }
        else
        {
            if(this->percents == 0) return;
            sf::Vector2f prev_pos = this->startCirclePoint; //(this->getStartPoint().x,this->getStartPoint().y);
            sf::Vector2f pos;
            float prev_angle = 0;
            float angle = 0;

            for(int i = 0; i < 100; i++)
            {
                sf::RectangleShape fill;
                fill.setSize(sf::Vector2f(this->onePercent,this->onePercent));
                angle = 3.6 * i;
                fill.rotate(angle);

                pos.x = prev_pos.x + this->onePercent * std::cos(prev_angle * M_PI / 180);
                pos.y = prev_pos.y + this->onePercent * std::sin(prev_angle * M_PI / 180);

                if(i == 0)
                {
                    pos.x = prev_pos.x;
                    pos.y = prev_pos.y;
                }
                fill.setPosition(pos);
                fill.setFillColor(sf::Color(127,127,127));

                prev_angle = angle;
                prev_pos = pos;

                target->draw(fill);
            }
            prev_pos = this->startCirclePoint;
            prev_angle = 0;
            for(int i(0); i <= this->percents; i++)
            {
                sf::RectangleShape fill;
                fill.setSize(sf::Vector2f(this->onePercent,this->onePercent));
                angle = 3.6 * i;
                fill.rotate(angle);

                pos.x = prev_pos.x + this->onePercent * std::cos(prev_angle * M_PI / 180);
                pos.y = prev_pos.y + this->onePercent * std::sin(prev_angle * M_PI / 180);

                if(i == 0)
                {
                    pos.x = prev_pos.x;
                    pos.y = prev_pos.y;
                }
                fill.setPosition(pos);
                fill.setFillColor(this->getColorCLICK());

                prev_angle = angle;
                prev_pos = pos;

                target->draw(fill);
             }
        }
        if(this->m_label) this->m_label->render(target);
    }
    void Progressbar::updateOnePercent()
    {
        this->onePercent = ((this->type == TYPE::BOX) ? (float)this->getSizes().x : (float)this->lengthCircle)/100;
    }
    void Progressbar::setSize(const sf::Vector2f &size)
    {
        this->setSizes(size);
        if(this->type == TYPE::BOX)
            this->bar_box.setSize(size);
        else this->startCirclePoint = sf::Vector2f(this->getStartPos().x + this->radius, this->getStartPos().y);
        this->updateOnePercent();
        this->isUpdatedPercent = true;
    }
    void Progressbar::setPosition(const sf::Vector2f &pos)
    {
        this->setStartPos(pos);
        if(this->type == TYPE::BOX)
        {
            this->bar_box.setPosition(pos);
            this->filling_box.setPosition(sf::Vector2f(pos.x - this->m_outline,pos.y - this->m_outline));
        }
        else
        {
            this->startCirclePoint = sf::Vector2f(this->getStartPos().x + this->radius, this->getStartPos().y);
        }

    }
    void Progressbar::Moving()
    {
        this->setPosition(sf::Vector2f(static_cast<sf::Vector2f>(GUI::mousePos) - this->getMoveOffset()));
    }
    void Progressbar::Resizing()
    {
        sf::Vector2f newSize = this->getSizes();
        if(this->type == TYPE::CIRCLE)
        {
            newSize.y = newSize.x;
            this->radius = newSize.x / 2;
            this->updateCircleLength();
        }
        this->setSize(newSize);

    }
    void Progressbar::updateCircleLength()
    {
        this->lengthCircle = 2 * M_PI * this->radius;
    }
    void Progressbar::updateFillingBoxPosition()
    {
        this->filling_box.setPosition(sf::Vector2f(this->getStartPos().x - this->m_outline,this->getStartPos().y - this->m_outline));
    }
    void Progressbar::updateTextPosition()
    {
        this->m_label_offset.x = (this->getSizes().x - this->m_label->getSizes().x)/2;
        this->m_label_offset.y = (this->getSizes().y - this->m_label->getSizes().y)/2 - this->m_label->getSizes().y / 2 - 1.5*this->m_outline;
        sf::Vector2f pos(this->m_label_offset.x + this->getStartPos().x,this->m_label_offset.y + this->getStartPos().y);
        this->m_label->setPosition(pos);
    }
    void Progressbar::setLabel(Label *label)
    {
        this->m_label = label;
        this->updateTextPosition();

    }
    void Progressbar::setLabelText(const sf::String &str)
    {
        this->m_label->setText(str);
        this->updateTextPosition();
    }
}
