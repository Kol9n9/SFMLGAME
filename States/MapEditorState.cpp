#include "MapEditorState.h"

void MapEditorState::initMapTile()
{
    this->m_map_tile = new MapTile();
    this->m_map_tile->loadLevel();
}

void MapEditorState::initView()
{
    this->m_view.setSize(sf::Vector2f(800,600));
    this->m_view.setCenter(sf::Vector2f(400,300));
    this->m_default_view = this->target->getDefaultView();
}
void MapEditorState::initDroplists()
{
    this->m_select_level = new GUI::Droplist(new GUI::Point(0,0),sf::Vector2f(100,20),sf::Color(255,255,255),sf::Color(127,127,127),sf::Color(255,255,255));
}
MapEditorState::MapEditorState(sf::RenderWindow *target, std::vector<State*>*m_states)
    : State(target,m_states)
{
    this->initMapTile();
    this->initView();
    this->initDroplists();
    //ctor
}

MapEditorState::~MapEditorState()
{
    if(this->m_map_tile) delete this->m_map_tile;
    //dtor
}

void MapEditorState::update(const float &dt)
{
    this->updateKeyBoard();
    if(this->m_select_level) this->m_select_level->update();
}
void MapEditorState::render()
{
    this->target->setView(this->m_view);
    if(this->m_map_tile) this->m_map_tile->render(this->target);
    this->target->setView(this->m_default_view);
    if(this->m_select_level) this->m_select_level->render(target);
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
    {
        this->m_view.zoom(1.001f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
    {
        this->m_view.zoom(0.999f);
    }
}

void MapEditorState::endState()
{
    this->m_endState = true;
}
