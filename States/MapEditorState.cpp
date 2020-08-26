#include "MapEditorState.h"

void MapEditorState::initMapTile()
{
    this->m_map_tile = new MapTile();
    this->m_map_tile->loadLevel();
    this->m_level_tiles = this->m_map_tile->getLevelTiles();
    for(auto &tile : this->m_level_tiles)
    {
        (tile.second)->getTile().setPosition(sf::Vector2f(0,200*(tile.first)));
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
    this->m_select_level = new GUI::Droplist(sf::Vector2f(0,0),sf::Vector2f(100,20),sf::Color(255,255,255),sf::Color(127,127,127),sf::Color(255,255,255));
}
void MapEditorState::initMouseScrollingAreas()
{
    this->m_map_scrolling = new GUI::MouseScrollingArea(sf::Vector2f(169,33),sf::Vector2f(603,551));
    //this->m_map_scrolling->setShowed(fa);
    this->m_map_scrolling->setTarget(this->target);
}
void MapEditorState::initCheckboxes()
{
    this->m_checkbox_move = new GUI::Checkbox(sf::Vector2f(773,5),20,sf::Color(0,0,0),sf::Color(0,0,0),sf::Color(0,0,0));
    this->m_checkbox_resize = new GUI::Checkbox(sf::Vector2f(773,35),20,sf::Color(0,0,0),sf::Color(0,0,0),sf::Color(0,0,0));
    this->m_checkbox_showed = new GUI::Checkbox(sf::Vector2f(773,65),20,sf::Color(0,0,0),sf::Color(0,0,0),sf::Color(0,0,0));
}
MapEditorState::MapEditorState(sf::RenderWindow *target, std::vector<State*>*m_states)
    : State(target,m_states)
{
    this->initMapTile();
    this->initView();
    this->initDroplists();
    this->initMouseScrollingAreas();
    this->initCheckboxes();
    //ctor
}

MapEditorState::~MapEditorState()
{
    if(this->m_map_tile) delete this->m_map_tile;
    delete this->m_checkbox_move;
    delete this->m_checkbox_resize;
    delete this->m_select_level;
    delete this->m_map_scrolling;
    delete this->m_checkbox_showed;
    //dtor
}

void MapEditorState::update(const float &dt)
{
    this->updateKeyBoard();
    this->m_select_level->update();
    this->m_map_scrolling->update();

    this->m_checkbox_move->update();
    this->m_checkbox_resize->update();
    this->m_checkbox_showed->update();


    this->m_map_scrolling->endMove();
    this->m_select_level->endMove();
    this->m_checkbox_move->endMove();
    this->m_checkbox_resize->endMove();
    if(this->m_checkbox_move->isChecked())
    {
        if(GUI::GUI::mouse_click_event == GUI::RIGHTCLICK && this->m_map_scrolling->getGUIStatus() == GUI::GUI_STATUS::HOVER) this->m_map_scrolling->startMove();
        if(GUI::GUI::mouse_click_event == GUI::RIGHTCLICK && this->m_select_level->getGUIStatus() == GUI::GUI_STATUS::HOVER) this->m_select_level->startMove();
        if(GUI::GUI::mouse_click_event == GUI::RIGHTCLICK && this->m_checkbox_move->getGUIStatus() == GUI::GUI_STATUS::HOVER) this->m_checkbox_move->startMove();
        if(GUI::GUI::mouse_click_event == GUI::RIGHTCLICK && this->m_checkbox_resize->getGUIStatus() == GUI::GUI_STATUS::HOVER) this->m_checkbox_resize->startMove();
    }
    if(this->m_checkbox_resize->isChecked())
    {
        this->m_map_scrolling->Resized();
    }
    this->m_map_scrolling->setShowed(this->m_checkbox_showed->isChecked());

    for(auto &tile : this->m_level_tiles)
    {
        if((tile.second)->isContain(GUI::GUI::mousePos) && GUI::GUI::mouse_click_event == GUI::LEFTCLICK && GUI::GUI::mouse_move_event)
        {
            this->m_map_tile->addTile(2,(tile.second),sf::Vector2f(200,200));
            //(tile.second)->Moving(sf::Vector2f(GUI::GUI::mousePos.x - (tile.second)->getTileCenter().x,GUI::GUI::mousePos.y - (tile.second)->getTileCenter().y));
        }
    }

}
void MapEditorState::render()
{
    this->target->setView(this->m_view);
    this->m_map_tile->render(this->target);


    this->target->setView(this->m_default_view);
    this->m_select_level->render(target);
    this->m_map_scrolling->render(target);


    this->m_checkbox_move->render(this->target);
    this->m_checkbox_resize->render(this->target);
    this->m_checkbox_showed->render(this->target);



    for(auto &tile : this->m_level_tiles)
    {
        (tile.second)->render(this->target);
    }
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
    this->m_endState = true;
}
