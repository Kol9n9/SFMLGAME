#include "List.h"
namespace GUI{
    List::List(const sf::Vector2f &start_pos, const sf::Vector2f &sizes,sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK)
        : GUI(start_pos,sizes,c_IDLE,c_HOVER,c_CLICK)
    {
        this->list_box.setFillColor(sf::Color::White);
        this->list_box.setPosition(this->getStartPos());
        this->list_box.setSize(this->getSizes());
        this->boxBorder = 5;
        this->list_box.setOutlineThickness(this->boxBorder);
        this->list_box.setOutlineColor(sf::Color(235,235,235));
        this->active_item = -1;
        this->currentIndex = 0;

        this->item_height_count = 4;
        this->item_height = this->getSizes().y / this->item_height_count;
        this->item_current_head = 0;
        this->sliderSize = 20;
        float x = this->getStartPos().x + this->getSizes().x - this->sliderSize;
        this->scr = new Scrollbar(sf::Vector2f(x,this->getStartPos().y),sf::Vector2f(this->sliderSize,this->getSizes().y),
                                  sf::Color(240,240,240),sf::Color(206,206,206),sf::Color(167,167,167),sf::Color(136,136,136));
        this->scr->setScrollingArea(Point(this->getStartPos().x,this->getStartPos().y),Point(this->getStartPos().x + this->getSizes().x,this->getStartPos().y + this->getSizes().y));
        this->isSliderShowed = false;
        this->isSliderHidden = false;
        this->isDropping = false;
        this->isItemSelected = false;
        this->isSliderSelect = false;
        this->scr->setVisibled(false);
        this->minSize = sf::Vector2f(0,0);

        //ctor
    }

    List::~List()
    {
        delete this->scr;
        if(!this->items.empty())
        {
            for(auto it = this->items.begin(); it != this->items.end(); ++it)
                delete (it->second).text;
        }
        //dtor
    }
    void List::update()
    {
        this->isItemSelected = false;
        this->isDropping = false;
        this->isSliderSelect = false;
        updateGUIState();

        if(!this->items.empty())
        {
            int i = 0;
            auto it = this->items.begin();
            advance(it,this->item_current_head);
            for(; it != this->items.end();++it)
            {
                if(i == this->item_height_count) break;
                (it->second).text->update();
                if((it->second).text->getGUIStatus() == GUI_STATUS::CLICK)
                {
                    this->changeItem((it->first));
                }
                i++;
            }
        }
        if(this->isSliderHidden)
        {
            auto it = this->items.begin();
            for(int i(0); i < this->item_height_count; i++, ++it)
            {
                (it->second).text->setBoxSize(sf::Vector2f(this->getSizes().x,this->item_height));
            }
            this->isSliderHidden = false;
        }
        if(this->items.size() <= this->item_height_count)
        {
            this->scr->setVisibled(false);
            return;
        }
        this->scr->update();
        if(Scrollbar::isSelectedSlider) this->isSliderSelect = true;
        int in = this->scr->getNewIndex();
        if(in != -1) this->item_current_head = in;
        if(this->isSliderShowed)
        {
            auto it = this->items.begin();
            for(int i(0); i < this->item_height_count; i++, ++it)
            {
                (it->second).text->setBoxSize(sf::Vector2f(this->getSizes().x - this->sliderSize,this->item_height));
            }

            this->isSliderShowed = false;
        }

    }
    void List::render(sf::RenderTarget *target)
    {

        target->draw(this->list_box);
        if(this->isBoxShow)
        {
            sf::RectangleShape debug_shape;
            debug_shape.setOutlineColor(sf::Color::Red);
            debug_shape.setOutlineThickness(5);
            debug_shape.setPosition(this->getStartPos());
            debug_shape.setSize(this->getSizes());
            target->draw(debug_shape);
        }
        if(!this->items.empty())
        {
            int i = 0;
            auto it = this->items.begin();
            advance(it,this->item_current_head);
            for(; it != this->items.end(); ++it)
            {
                if(i == this->item_height_count) break;
                if(this->active_item == (it->first))
                {
                    this->item_box.setFillColor(this->getColorCLICK());
                    this->item_box.setPosition(sf::Vector2f(this->getStartPos().x,this->getStartPos().y + this->item_height * i));
                    sf::Vector2f sz(this->getSizes().x,this->item_height+1);
                    if(this->scr->isVisibled()) sz.x -= this->sliderSize;
                    this->item_box.setSize(sz);
                    target->draw(this->item_box);
                }
                (it->second).text->setPosition(sf::Vector2f(this->getStartPos().x,this->getStartPos().y+(this->item_height+1)*i));
                (it->second).text->render(target);
                i++;
            }
        }
        this->scr->render(target);
    }
    void List::changeItem(const int &index)
    {
        if(index < 0 || index > this->currentIndex)return;
        this->isItemSelected = true;
        if(this->active_item == index) return;
        this->active_item = index;
        if(this->items[this->active_item].call_back != nullptr)
            this->items[this->active_item].call_back(this->items[this->active_item].call_back_object);
    }

    void List::insert(Label* text, void(*cb)(void*),void *obj)
    {
        this->insert(text);

        this->items[this->currentIndex-1].call_back = cb;
        this->items[this->currentIndex-1].call_back_object = obj;
    }
    void List::insert(Label* text)
    {
        if(this->items.size() == this->item_height_count)
            this->scr->setVisibled(true);
        sf::Vector2f sz(this->getSizes().x,this->item_height);
        if(this->scr->isVisibled()) sz.x -= this->sliderSize;
        sf::Vector2f newSize = text->getTextBoxSize();
        if(this->minSize.x < newSize.x + this->sliderSize) this->minSize.x = newSize.x + this->sliderSize;
        if(this->minSize.y < newSize.y * this->item_height_count) this->minSize.y = newSize.y * this->item_height_count;
        std::cout << "text = " << text->getTextBoxSize().x << " " << text->getTextBoxSize().y << "\n";
        text->setBoxSize(sf::Vector2f(sz));
        this->items[this->currentIndex] = text;

        int x = this->items.size() - this->item_height_count + 1;
        if(x < 0) x = 0;
        this->scr->setSliderCountPos(x);
        this->currentIndex++;
        if(this->items.size() == this->item_height_count + 1) this->isSliderShowed = true;
    }
    void List::itemUp()
    {

        if(this->active_item == -1) return;
        auto it = this->items.find(this->active_item);
        if(it == this->items.begin()) return;
        it--;
        std::swap(this->items[this->active_item],this->items[(it->first)]);
        this->active_item = (it->first);
        if(this->active_item < this->item_current_head)
        {
            this->item_current_head--;
            this->scr->setSliderIndex(this->scr->getSliderIndex()-1);
        }

    }
    void List::itemDown()
    {
        if(this->active_item == -1) return;
        auto it = this->items.find(this->active_item);
        it++;
        if(it == this->items.end()) return;
        std::swap(this->items[this->active_item],this->items[(it->first)]);
        this->active_item = (it->first);
        if(this->active_item == (this->item_current_head + this->item_height_count))
        {
            this->item_current_head++;
            this->scr->setSliderIndex(this->scr->getSliderIndex()+1);
        }
    }
    void List::itemDelete()
    {
        if(this->active_item == -1) return;
        auto it = this->items.find(this->active_item);
        Label *tex = (it->second).text;
        if(tex) delete tex;

        it = this->items.erase(it);

        int x = this->items.size() - this->item_height_count + 1;
        if(x < 0) x = 0;

        this->scr->setSliderCountPos(x);

        if(scr->getSliderIndex() != 0) this->scr->setSliderIndex(scr->getSliderIndex()-1);
        if(this->item_current_head != 0) this->item_current_head--;
        this->active_item = -1;

        if(!this->isDropping && this->items.size() == this->item_height_count) this->isSliderHidden = true;

    }
    void List::itemInsert(const std::string &str, sf::Font *font, unsigned int textSize,sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK)
    {
        sf::String str2 = L"Строка ";
        str2 += std::to_string(this->currentIndex);
        this->insert(new Label(sf::Vector2f(0,0),str2,font,textSize,c_IDLE,c_HOVER,c_CLICK));
        if(this->items.size() - 1 < this->item_height_count) return;
        this->item_current_head++;
        this->scr->setSliderIndex(this->scr->getSliderIndex()+1);

    }
    void List::itemDrop()
    {
        this->isDropping = true;
        for(auto it = this->items.begin(); it != this->items.end(); ++it)
        {
            this->active_item = (it->first);
            this->itemDelete();
        }
        this->currentIndex = 0;
    }
    void List::setPosition(const sf::Vector2f &pos)
    {
        this->setStartPos(sf::Vector2f(pos.x,pos.y));
        this->list_box.setPosition(pos);
        //new Point(x,this->getStartPoint().y),new Point(this->getStartPoint().x + this->getSizes().x, this->getStartPoint().y + this->getSizes().y)
        float x = this->getStartPos().x + this->getSizes().x - this->sliderSize;
        this->scr->setPosition(sf::Vector2f(x,this->getStartPos().y));
        this->scr->setScrollingArea(Point(this->getStartPos().x,this->getStartPos().y),Point(this->getStartPos().x + this->getSizes().x,this->getStartPos().y + this->getSizes().y));
        this->scr->setSliderIndex(this->scr->getSliderIndex());
    }
    List_Item &List::getActiveItem()
    {
        return this->items[this->active_item];
    }
    void List::Moving()
    {
        this->setPosition(sf::Vector2f(static_cast<sf::Vector2f>(GUI::mousePos) - this->getMoveOffset()));
    }
    void List::Resizing()
    {
        sf::Vector2f newSize = this->getSizes();
        if(newSize.x < this->minSize.x) newSize.x = this->minSize.x;
        if(newSize.y < this->minSize.y) newSize.y = this->minSize.y;
        this->setSize(newSize);
    }
    void List::setSize(const sf::Vector2f &size)
    {
        this->setSizes(size);
        this->list_box.setSize(size);
        this->updateItemHeight();

        float x = this->getStartPos().x + this->getSizes().x - this->sliderSize;
        this->scr->setPosition(sf::Vector2f(x,this->getStartPos().y));
        this->scr->setSize(sf::Vector2f(this->sliderSize,size.y));
        this->scr->setScrollingArea(Point(this->getStartPos().x,this->getStartPos().y),Point(this->getStartPos().x + size.x,this->getStartPos().y + size.y));
        this->scr->setSliderIndex(this->scr->getSliderIndex());
    }
    void List::updateItemHeight()
    {
        this->item_height = this->getSizes().y / this->item_height_count;
        sf::Vector2f sz(this->getSizes().x,this->item_height);
        if(this->scr->isVisibled()) sz.x -= this->sliderSize;
        for(auto it = this->items.begin(); it != this->items.end(); ++it)
        {
            (it->second).text->setBoxSize(sz);
        }
    }
}
