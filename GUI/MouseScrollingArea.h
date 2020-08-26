#ifndef MOUSESCROLLINGAREA_H
#define MOUSESCROLLINGAREA_H

#include <GUI.h>

namespace GUI{
class MouseScrollingArea : public GUI
{
    public:
        MouseScrollingArea(const sf::Vector2f &start_pos, const sf::Vector2f &sizes);
        virtual ~MouseScrollingArea();
        void render(sf::RenderTarget *target);
        void update();
        bool &isContain() { return m_isContain;}
        void setShowed(const bool &st) {m_isShowed = st;}
        void setPosition(const sf::Vector2f &pos);

    protected:
        void Moving();
        void Resizing(){}
    private:
        bool m_isContain;
        bool m_isShowed;
};
}
#endif // MOUSESCROLLINGAREA_H
