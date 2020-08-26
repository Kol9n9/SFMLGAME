#ifndef GUI_H
#define GUI_H
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "SFML/Graphics.hpp"

#define M_PI 3.14159265358979323846
namespace GUI{
    enum GUI_STATUS{
        NONE = -1,
        IDLE = 0,
        HOVER,
        CLICK,
        CLICKING
    };
    enum MOUSE_CLICK_EVENTS{
        NONECLICK = -1,
        LEFTCLICK,
        RIGHTCLICK,
        BOTHCLICK,
        MIDDLECLICK
    };
    enum MOUSE_WHEEL_EVENTS{
        NONEWHEEL = -1,
        WHEELUP,
        WHEELDOWN
    };
    struct Point{
        float x;
        float y;
        Point() : x(0), y(0){}
        Point(float xx, float yy) : x(xx), y(yy) {}
    };
    class GUI
    {
        public:
            GUI(const sf::Vector2f &start_pos, const sf::Vector2f &sizes,sf::Color c_IDLE, sf::Color c_HOVER, sf::Color c_CLICK);
            virtual ~GUI();
            virtual void update() = 0;
            virtual void render(sf::RenderTarget *target) = 0;
            static void updateEvents(sf::RenderWindow *target, sf::Event &events);

            void setStartPos(const sf::Vector2f &start_pos) {this->start_pos = start_pos;}
            const sf::Vector2f &getStartPos() const {return start_pos;}

            sf::Vector2f &getSizes() {return this->sizes;}
            void setSizes(const sf::Vector2f &sz) {sizes = sz;}

            sf::Color &getColorIDLE() { return color_IDLE;}
            sf::Color &getColorHOVER() { return color_HOVER;}
            sf::Color &getColorCLICK() { return color_CLICK;}

            void setColorIDLE(sf::Color &cIDLE) { color_IDLE = cIDLE;}
            void setColorHOVER(sf::Color &cHOVER) { color_HOVER = cHOVER;}
            void setColorCLICK(sf::Color &cCLICK) { color_CLICK = cCLICK;}
            void setBoxShow(const bool &st) { this->isBoxShow = st;}
            void startMove();
            void endMove();
            void Resized();

            void setClickCallback(void(*newCb)(void *,void *),void *a) {cb_Click = newCb;a_a = a;}
            MOUSE_CLICK_EVENTS getMouseClickEvent() const {return this->mouse_click_event;}
            MOUSE_WHEEL_EVENTS getMouseWheelEvent() const {return this->mouse_wheel_event;}
            void setMouseWheelEvent(const MOUSE_WHEEL_EVENTS &event) {this->mouse_wheel_event = event;}
            GUI_STATUS getGUIStatus() const {return this->status;}
            void setVisibled(const bool &st) {this->isVis = st;}
            const bool &isVisibled() {return this->isVis;}
            static MOUSE_CLICK_EVENTS mouse_click_event;
            static MOUSE_WHEEL_EVENTS mouse_wheel_event;
            static bool mouse_move_event;
            static bool isAnyGUIMoving;
            static bool isAnyGUICorning;
            static sf::Vector2i mousePos;
            void setTarget(sf::RenderWindow *target) {this->target = target;}
        protected:
            sf::RenderWindow *target;

            void updateGUIState();

            bool &getMoving() {return isMoving;}

            sf::Vector2f &getMoveOffset() {return move_offset;}
            virtual void Moving(){};
            virtual void Resizing(){};
            bool isBoxShow;

            sf::String InputSymbol;
        private:
            void (*cb_Click)(void *,void *);
            void *a_a;

            GUI_STATUS status;
            sf::Vector2f start_pos;
            sf::Vector2f sizes;

            sf::Color color_IDLE;
            sf::Color color_HOVER;
            sf::Color color_CLICK;

            bool isContains();
            bool isContainCorner();
            bool isMoving;
            bool isCorner;
            sf::Vector2f move_offset;
            bool isClicking;
            bool isVis;


    };
}
#endif // GUI_H
