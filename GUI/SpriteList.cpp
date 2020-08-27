#include "SpriteList.h"
namespace GUI{
    SpriteList::SpriteList(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &box_fill_color, const sf::Color &box_item_hover_color)
        : GUI(pos,size,box_fill_color,box_item_hover_color, sf::Color(0,0,0))
    {
        this->m_list_box.setPosition(pos);
        this->m_list_box.setSize(size);
        this->m_list_box.setFillColor(box_fill_color);

        this->m_list_item_hover = nullptr;
        this->m_isHovered = false;

        m_list_items_count.x = 3;
        m_list_items_count.y = 3;
        this->m_list_item_margin = 5;

        this->m_list_item_size.x = (size.x - this->m_list_item_margin * (m_list_items_count.x + 1)) / m_list_items_count.x;
        this->m_list_item_size.y = (size.y - this->m_list_item_margin * (m_list_items_count.y + 1)) / m_list_items_count.y;
        this->m_list_item_size.y = this->m_list_item_size.x;



        /*
        sprite1.setScale(this->m_list_item_size.x/sprite1.getGlobalBounds().width,this->m_list_item_size.y/sprite1.getGlobalBounds().height);
        sprite2.setScale(this->m_list_item_size.x/sprite2.getGlobalBounds().width,this->m_list_item_size.y/sprite2.getGlobalBounds().height);


        this->m_list_items.push_back(Item(this->m_list_item_size,sprite1));
        this->m_list_items.push_back(Item(this->m_list_item_size,sprite2));
*/




        //ctor
    }

    SpriteList::~SpriteList()
    {
        //dtor
    }
    void SpriteList::addTile(Tile *tile)
    {
        this->m_list_items.push_back(Item(this->m_list_item_size,tile));
    }
    void SpriteList::update()
    {
        this->updateGUIState();
        this->m_list_item_hover = nullptr;
        this->m_isHovered = false;
        sf::RectangleShape shape;
        for(auto &item : this->m_list_items)
        {
            if(item.m_item_shape.getGlobalBounds().contains(GUI::mousePos.x,GUI::mousePos.y))
            {
                this->m_list_item_hover = &item;
                this->m_isHovered = true;
            }
        }
    }
    void SpriteList::render(sf::RenderTarget *target)
    {

        target->draw(this->m_list_box);
        int i = 0;
        int j = 0;
        for(auto &item : this->m_list_items)
        {
            sf::Sprite renderSprite;
            renderSprite = item.m_tile->getTile();
            renderSprite.setScale(this->m_list_item_size.x/renderSprite.getGlobalBounds().width,this->m_list_item_size.y/renderSprite.getGlobalBounds().height);
            if(i == m_list_items_count.x) {i = 0; j++;}
            sf::Vector2f pos(this->getStartPos().x + this->m_list_item_margin + ((this->m_list_item_size.x + this->m_list_item_margin) * i), this->getStartPos().y + this->m_list_item_margin + ((this->m_list_item_size.y + this->m_list_item_margin) * j));
            item.m_item_shape.setPosition(pos);
            renderSprite.setPosition(pos);
            target->draw(renderSprite);
            i++;
        }
    }
    void SpriteList::setPosition(const sf::Vector2f &pos)
    {
        std::cout << "pos = " << pos.x << " = " << pos.y << "\n";
        this->setStartPos(pos);
        this->m_list_box.setPosition(pos);
    }
    void SpriteList::Moving()
    {
        this->setPosition(sf::Vector2f(static_cast<sf::Vector2f>(GUI::mousePos) - this->getMoveOffset()));
    }
}
