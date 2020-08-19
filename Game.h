#ifndef GAME_H
#define GAME_H
#include "GUI.h"
#include "MainMenuState.h"
class Game
{
    public:
        Game();
        virtual ~Game();
        void run();
    protected:

    private:
        //variables
        sf::RenderWindow *window;
        sf::Event SFMLEvent;
        std::vector<State*> states;
        float dt;
        sf::Clock clock;
        //inits
        void initWindow();
        void initVariables();
        void initState();
        // functions
        void update();
        void updateSFMLEvents();
        void updatedtTime();
        void render();
        void endApplication();
};

#endif // GAME_H
