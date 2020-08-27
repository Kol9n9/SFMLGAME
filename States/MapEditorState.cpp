#include "MapEditorState.h"

void MapEditorState::initMapTile()
{
    this->m_map_tile = new MapTile();
    this->m_map_tile->loadLevel();
    this->m_level_tiles = this->m_map_tile->getLevelTiles();
    for(auto &tile : this->m_level_tiles)
    {
        this->m_select_sprite_list->addTile((tile.second));
    }
}

void MapEditorState::initView()
{
    this->m_view.setSize(sf::Vector2f(800,600));
    this->m_view.setCenter(sf::Vector2f(400,300));
    this->m_default_view = this->target->getDefaultView();

}
void MapEditorState::initDroplists()
{
    this->m_droplist_selectlevel = new GUI::Droplist(sf::Vector2f(138,9),sf::Vector2f(100,20),sf::Color(255,255,255),sf::Color(127,127,127),sf::Color(255,255,255));
    //this->m_droplist_renderlevel = new GUI::Droplist(sf::Vector2f(138,9),sf::Vector2f(100,20),sf::Color(255,255,255),sf::Color(127,127,127),sf::Color(255,255,255));
}
void MapEditorState::initMouseScrollingAreas()
{
    this->m_map_scrolling = new GUI::MouseScrollingArea(sf::Vector2f(201,10),sf::Vector2f(583,584));
    //this->m_map_scrolling->setShowed(fa);
    this->m_map_scrolling->setTarget(this->target);
}
void MapEditorState::initCheckboxes()
{
    this->m_checkbox_move = new GUI::Checkbox(sf::Vector2f(773,5),20,sf::Color(0,0,0),sf::Color(0,0,0),sf::Color(0,0,0));
    this->m_checkbox_resize = new GUI::Checkbox(sf::Vector2f(773,35),20,sf::Color(0,0,0),sf::Color(0,0,0),sf::Color(0,0,0));
    this->m_checkbox_showed = new GUI::Checkbox(sf::Vector2f(773,65),20,sf::Color(0,0,0),sf::Color(0,0,0),sf::Color(0,0,0));
}
void MapEditorState::initLists()
{
    this->m_select_sprite_list = new GUI::SpriteList(sf::Vector2f(2,96),sf::Vector2f(200,500),sf::Color(127,127,127),sf::Color(127,127,0));
}
void MapEditorState::initLabels()
{

    this->m_font.loadFromFile("GUI/font.ttf");
    this->m_label_renderlevel = new GUI::Label(sf::Vector2f(2,2),"Render level",&this->m_font,20,sf::Color(255,255,255),sf::Color(255,255,255),sf::Color(255,255,255));
    this->m_label_selectlevel = new GUI::Label(sf::Vector2f(2,22),"Select level",&this->m_font,20,sf::Color(255,255,255),sf::Color(255,255,255),sf::Color(255,255,255));
}
MapEditorState::MapEditorState(sf::RenderWindow *target, std::vector<State*>*m_states)
    : State(target,m_states)
{
    this->initLists();
    this->initMapTile();
    this->initView();
    this->initDroplists();
    this->initMouseScrollingAreas();
    this->initCheckboxes();
    this->initLabels();

    this->m_current_tile = nullptr;
    this->m_created_tile = false;
    this->m_edit_tile = false;
    this->m_settings.setFillColor(sf::Color(127,127,127));
    this->m_settings.setSize(sf::Vector2f(200,90));
    this->m_settings.setPosition(2,5);
    //ctor
}

MapEditorState::~MapEditorState()
{
    delete this->m_map_tile;
    delete this->m_checkbox_move;
    delete this->m_checkbox_resize;
    delete this->m_droplist_selectlevel;
    delete this->m_map_scrolling;
    delete this->m_checkbox_showed;
    delete this->m_select_sprite_list;
    delete this->m_label_renderlevel;
    delete this->m_label_selectlevel;
    //dtor
}

void MapEditorState::update(const float &dt)
{
    this->updateKeyBoard();
    this->updateGUIElements();
    this->m_select_sprite_list->update();
    this->updateCreateTile();
    this->updateMapTile();
    this->updateEditTile();
    this->updateTileMoving();
}
void MapEditorState::updateGUIElements()
{
    this->m_droplist_selectlevel->update();
    this->m_map_scrolling->update();

    this->m_checkbox_move->update();
    this->m_checkbox_resize->update();
    this->m_checkbox_showed->update();

    this->m_label_selectlevel->update();
    this->m_label_renderlevel->update();

    this->m_map_scrolling->endMove();
    this->m_droplist_selectlevel->endMove();
    this->m_checkbox_move->endMove();
    this->m_checkbox_resize->endMove();

    this->m_label_selectlevel->endMove();
    this->m_label_renderlevel->endMove();
    if(this->m_checkbox_move->isChecked())
    {
        if(GUI::GUI::mouse_click_event == GUI::RIGHTCLICK && this->m_map_scrolling->getGUIStatus() == GUI::GUI_STATUS::HOVER) this->m_map_scrolling->startMove();
        if(GUI::GUI::mouse_click_event == GUI::RIGHTCLICK && this->m_droplist_selectlevel->getGUIStatus() == GUI::GUI_STATUS::HOVER) this->m_droplist_selectlevel->startMove();
        if(GUI::GUI::mouse_click_event == GUI::RIGHTCLICK && this->m_checkbox_move->getGUIStatus() == GUI::GUI_STATUS::HOVER) this->m_checkbox_move->startMove();
        if(GUI::GUI::mouse_click_event == GUI::RIGHTCLICK && this->m_checkbox_resize->getGUIStatus() == GUI::GUI_STATUS::HOVER) this->m_checkbox_resize->startMove();
        if(GUI::GUI::mouse_click_event == GUI::RIGHTCLICK && this->m_select_sprite_list->getGUIStatus() == GUI::GUI_STATUS::HOVER) this->m_select_sprite_list->startMove();
        if(GUI::GUI::mouse_click_event == GUI::RIGHTCLICK && this->m_label_selectlevel->getGUIStatus() == GUI::GUI_STATUS::HOVER) this->m_label_selectlevel->startMove();
        if(GUI::GUI::mouse_click_event == GUI::RIGHTCLICK && this->m_label_renderlevel->getGUIStatus() == GUI::GUI_STATUS::HOVER) this->m_label_renderlevel->startMove();
    }
    if(GUI::GUI::mouse_click_event != GUI::RIGHTCLICK )  this->m_select_sprite_list->endMove();
    if(this->m_checkbox_resize->isChecked())
    {
        this->m_map_scrolling->Resized();
    }
    this->m_map_scrolling->setShowed(this->m_checkbox_showed->isChecked());
}
void MapEditorState::updateCreateTile()
{
    if(!this->m_created_tile && !this->m_edit_tile && this->m_select_sprite_list->isHovered() && GUI::GUI::mouse_click_event == GUI::LEFTCLICK && GUI::GUI::mouse_move_event)
    {
        std::cout << "updateCreateTile\n";
        this->m_created_tile = true;
        this->m_current_tile = this->m_map_tile->addTile(2,this->m_select_sprite_list->getHoverTile(),sf::Vector2f(200,200));
    }
}
void MapEditorState::updateEditTile()
{
    if(this->m_map_scrolling->isContain() && !this->m_created_tile && !this->m_edit_tile && GUI::GUI::mouse_click_event == GUI::LEFTCLICK && this->m_map_tile->getHoverTile())
    {
        std::cout << "updateEditTile\n";
        this->m_current_tile = this->m_map_tile->getHoverTile();
        this->m_map_tile->setTileEdit(this->m_map_tile->getHoverTile());
        this->m_edit_tile = true;
    }
}
void MapEditorState::updateMapTile()
{
    this->target->setView(this->m_view);
    sf::Vector2i mousePos  = sf::Mouse::getPosition(*this->target);
    sf::Vector2f wordPos = this->target->mapPixelToCoords(mousePos);
    this->target->setView(this->m_default_view);
    this->m_map_tile->update(wordPos);
}
void MapEditorState::updateTileMoving()
{
    if((this->m_created_tile || this->m_edit_tile) && GUI::GUI::mouse_click_event != GUI::LEFTCLICK)
    {
        this->target->setView(this->m_view);
        sf::Vector2i mousePos  = sf::Mouse::getPosition(*this->target);
        sf::Vector2f wordPos = this->target->mapPixelToCoords(mousePos);
        this->target->setView(this->m_default_view);
        this->m_current_tile->getTile().setScale(1,1);
        this->m_current_tile->Moving(sf::Vector2f(wordPos.x - this->m_current_tile->getTileCenter().x,wordPos.y - this->m_current_tile->getTileCenter().y));
        this->m_created_tile = false;
        this->m_edit_tile = false;
        this->m_current_tile = nullptr;
        this->m_map_tile->setTileEdit(nullptr);

    }
    if((this->m_created_tile || this->m_edit_tile)&& this->m_current_tile)
    {
        this->m_current_tile->Moving(sf::Vector2f(GUI::GUI::mousePos.x - this->m_current_tile->getTileCenter().x,GUI::GUI::mousePos.y - this->m_current_tile->getTileCenter().y));
    }
}
void MapEditorState::render()
{
    this->target->setView(this->m_view);
    this->m_map_tile->render(this->target);


    this->target->setView(this->m_default_view);
    this->target->draw(this->m_settings);
    this->m_map_scrolling->render(target);
    this->m_select_sprite_list->render(this->target);
    if(this->m_current_tile)
    {
        float zoom = (this->m_view.getSize().x / this->m_default_view.getSize().x);
        this->m_current_tile->getTile().setScale(1/zoom,1/zoom);
        this->m_current_tile->render(target);
    }
    this->renderGUIElements();
}
void MapEditorState::renderGUIElements()
{
    this->m_droplist_selectlevel->render(target);
    this->m_checkbox_move->render(this->target);
    this->m_checkbox_resize->render(this->target);
    this->m_checkbox_showed->render(this->target);

    this->m_label_renderlevel->render(this->target);
    this->m_label_selectlevel->render(this->target);
}
void MapEditorState::updateKeyBoard()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        this->endState();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->m_view.setCenter(sf::Vector2f(this->m_view.getCenter().x - 0.5,this->m_view.getCenter().y));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->m_view.setCenter(sf::Vector2f(this->m_view.getCenter().x + 0.5,this->m_view.getCenter().y));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->m_view.setCenter(sf::Vector2f(this->m_view.getCenter().x,this->m_view.getCenter().y - 0.5));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->m_view.setCenter(sf::Vector2f(this->m_view.getCenter().x,this->m_view.getCenter().y + 0.5));
    }
    if(this->m_map_scrolling->isContain() && GUI::GUI::mouse_wheel_event == GUI::WHEELDOWN)
    {
        this->m_view.zoom(1.1f);
        GUI::GUI::mouse_wheel_event = GUI::NONEWHEEL;
    }
    if(this->m_map_scrolling->isContain() && GUI::GUI::mouse_wheel_event == GUI::WHEELUP)
    {
        this->m_view.zoom(0.9f);
        GUI::GUI::mouse_wheel_event = GUI::NONEWHEEL;
    }
}

void MapEditorState::endState()
{
    this->m_map_tile->saveLevel();
    this->m_endState = true;
}
