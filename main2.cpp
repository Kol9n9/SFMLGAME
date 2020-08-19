#include "GUI/Button.h"
#include "GUI/Label.h"
#include "GUI/TextInput.h"
#include "GUI/List.h"
#include "GUI/Scrollbar.h"
#include "GUI/Droplist.h"
#include "GUI/Checkbox.h"
#include "GUI/Progressbar.h"
#include "Timer.h"

using namespace std;

sf::Font font;
struct sendProgressbar{
    GUI::Progressbar *progressbar;
    int value;
    sendProgressbar(GUI::Progressbar *pr, int i)
    {
        progressbar = pr;
        value = i;
    }
};
struct Resolution{
    sf::RenderWindow *window;
    string text;
    float width;
    float height;
    Resolution(sf::RenderWindow *win,const string &t, float w, float h)
    {
        window = win;
        text = t;
        width = w;
        height = h;
    }
};
void printOut()
{
    std::cout << "but clicked\n";
}
void PrintOut2(int& a)
{
    std::cout << "clicked = " << a << "\n";
}
void ListItemUp(void *text,void *lst)
{
    if(lst) static_cast<GUI::List*>(lst)->itemUp();
}
void ListItemDown(void *text,void *lst)
{
    if(lst) static_cast<GUI::List*>(lst)->itemDown();
}
void ListItemDel(void *text, void *lst)
{
    if(lst) static_cast<GUI::List*>(lst)->itemDelete();
}
void ListItemInsert(void *text, void *lst)
{
    if(lst) static_cast<GUI::List*>(lst)->itemInsert("Строка",&font,20,sf::Color(0,0,0),sf::Color(127,127,0),sf::Color(0,0,0));
}
void ListItemClear(void *text, void *lst)
{
     if(lst) static_cast<GUI::List*>(lst)->itemDrop();
}
void timerUpdateProgressbar(void *object)
{
    if(!object) return;
    sendProgressbar *recieve = static_cast<sendProgressbar*>(object);
    recieve->progressbar->setPercent(recieve->value);
    recieve->value += 1;
}
void progressbarReset(void *text, void *object)
{
    if(!object) return;
    sendProgressbar *recieve = static_cast<sendProgressbar*>(object);
    recieve->progressbar->setPercent(0);
    recieve->value = 0;
}
void changeResolution(void *object)
{
    if(!object) return;
    Resolution *res = static_cast<Resolution*>(object);
    std::cout << res->text << " = " << res->width << " " << res->height << "\n";
    //res->window->setView(sf::View(res->window->getView().getCenter(),sf::Vector2f((float)res->width,(float)res->height)));

    //res->window->setPosition(sf::Vector2i(0,0));

    int scrW = res->width; //1024 for this game
    int scrH = res->height; //768 for this game
    sf::View window1View = res->window->getView();
    window1View.reset(sf::FloatRect(0,0,res->width,res->height));
    window1View.setViewport(sf::FloatRect(0,0,1,1));
    window1View.setSize(scrW,scrH);
    window1View.setCenter((scrW/2),(scrH/2));
    res->window->setView(window1View);

}
int t_main()
{
    sf::ContextSettings set;
    set.antialiasingLevel = 0;
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800,600),"GUI",sf::Style::Default,set);
    font.loadFromFile("GUI/font.ttf");
    vector<GUI::GUI*> GUIVECTOR;
    GUI::Label *list_up = new GUI::Label(window, new GUI::Point(300,165),L"Вверх",&font,25,sf::Color(0,0,0),sf::Color(127,127,0),sf::Color(0,0,0));
    GUI::Label *list_down = new GUI::Label(window, new GUI::Point(300,201),L"Вниз",&font,25,sf::Color(0,0,0),sf::Color(127,127,0),sf::Color(0,0,0));
    GUI::Label *list_insert = new GUI::Label(window, new GUI::Point(6,147),L"Добавить",&font,25,sf::Color(0,0,0),sf::Color(127,127,0),sf::Color(0,0,0));
    GUI::Label *list_del = new GUI::Label(window, new GUI::Point(6,180),L"Удалить",&font,25,sf::Color(0,0,0),sf::Color(127,127,0),sf::Color(0,0,0));
    GUI::Label *list_clear = new GUI::Label(window, new GUI::Point(3,218),L"Очистить",&font,25,sf::Color(0,0,0),sf::Color(127,127,0),sf::Color(0,0,0));
    GUI::Label *info_1 = new GUI::Label(window, new GUI::Point(9,6),L"Двигать элементы",&font,15,sf::Color(0,0,0),sf::Color(0,0,0),sf::Color(0,0,0));
    GUI::Label *info_2 = new GUI::Label(window, new GUI::Point(25,41),L"Изменить размер",&font,15,sf::Color(0,0,0),sf::Color(0,0,0),sf::Color(0,0,0));
    GUI::Label *info_3 = new GUI::Label(window, new GUI::Point(60,84),L"Debug mode",&font,15,sf::Color(0,0,0),sf::Color(0,0,0),sf::Color(0,0,0));
    GUI::Label *timer_1 = new GUI::Label(window, new GUI::Point(319,7),L"Перезапустить",&font,15,sf::Color(0,0,0),sf::Color(127,127,127),sf::Color(0,0,0));
    GUI::Label *timer_2 = new GUI::Label(window, new GUI::Point(319,81),L"Перезапустить",&font,15,sf::Color(0,0,0),sf::Color(127,127,127),sf::Color(0,0,0));
    GUI::List *list1 = new GUI::List(window,new GUI::Point(136,148),sf::Vector2f(150,102),sf::Color(0,255,0),sf::Color(127,127,0),sf::Color(0,0,255));
    GUI::List *list2 = new GUI::List(window,new GUI::Point(200,20),sf::Vector2f(350,130),sf::Color(0,255,0),sf::Color(127,127,0),sf::Color(0,0,255));
    GUI::Droplist *drop1 = new GUI::Droplist(window,new GUI::Point(136,280),sf::Vector2f(150,30),sf::Color(255,255,255),sf::Color(127,127,127),sf::Color(0,0,255));
    GUI::Checkbox *check = new GUI::Checkbox(window,new GUI::Point(161,6),20,sf::Color(0,0,0),sf::Color(127,127,127),sf::Color(0,255,0));
    GUI::Checkbox *check2 = new GUI::Checkbox(window,new GUI::Point(161,42),20,sf::Color(0,0,0),sf::Color(127,127,127),sf::Color(0,255,0));
    GUI::Checkbox *check3 = new GUI::Checkbox(window,new GUI::Point(161,81),20,sf::Color(0,0,0),sf::Color(127,127,127),sf::Color(0,255,0));
    GUI::Progressbar *progress = new GUI::Progressbar(window,new GUI::Point(206,7),sf::Vector2f(100,20),sf::Color(255,255,255),sf::Color(127,127,127),sf::Color(0,255,0));
    GUI::Progressbar *progress2 = new GUI::Progressbar(window,new GUI::Point(204,36),50,sf::Color(255,255,255),sf::Color(127,127,127),sf::Color(0,255,0));
    GUI::Button *but1 = new GUI::Button(window,new GUI::Point(447,10),sf::Vector2f(120,50),
                    new GUI::Label(window,new GUI::Point(0,0),"New Game",&font,25,sf::Color(0,0,0),sf::Color(0,255,255),sf::Color(255,255,255)),
                    true, sf::Color(0,255,255),sf::Color(255,255,255),sf::Color(255,255,255));
    GUI::TextInput *textinput = new GUI::TextInput(window,new GUI::Point(109,335),sf::Vector2f(200,20),&font,20,sf::Color(0,0,0),sf::Color(0,0,255),sf::Color(0,0,255));
    sendProgressbar send(progress,0);

    Timer *timer = new Timer(50.f,timerUpdateProgressbar,&send);
    timer_1->setClickCallback(progressbarReset,&send);
    sendProgressbar send2(progress2,0);
    timer_2->setClickCallback(progressbarReset,&send2);
    Timer *timer2 = new Timer(50.f,timerUpdateProgressbar,&send2);
    timer->start();
    timer2->start();
    list_insert->setTextSize(20);

    GUIVECTOR.push_back(list1);
    GUIVECTOR.push_back(drop1);
    GUIVECTOR.push_back(list_up);
    GUIVECTOR.push_back(list_insert);
    GUIVECTOR.push_back(list_del);
    GUIVECTOR.push_back(list_down);
    GUIVECTOR.push_back(list_clear);
    GUIVECTOR.push_back(check);
    GUIVECTOR.push_back(check2);
    GUIVECTOR.push_back(check3);
    GUIVECTOR.push_back(info_1);
    GUIVECTOR.push_back(info_2);
    GUIVECTOR.push_back(info_3);
    GUIVECTOR.push_back(progress);
    GUIVECTOR.push_back(progress2);
    GUIVECTOR.push_back(timer_1);
    GUIVECTOR.push_back(timer_2);
    GUIVECTOR.push_back(but1);
    GUIVECTOR.push_back(textinput);
    drop1->setList(list2);
    //progress->setPercent(50);
    //list1->setItemCount();
    list1->insert(new GUI::Label(window, new GUI::Point(0,40),L"Строка 1",&font,20,sf::Color(0,0,0),sf::Color(127,127,0),sf::Color(0,0,0)));
    list1->insert(new GUI::Label(window, new GUI::Point(0,40),L"Строка 2",&font,20,sf::Color(0,0,0),sf::Color(127,127,0),sf::Color(0,0,0)));
    list2->insert(new GUI::Label(window, new GUI::Point(0,40),"800x600",&font,25,sf::Color(0,0,0),sf::Color(127,127,0),sf::Color(0,0,0)),changeResolution,new Resolution(window,"800x600",800,600));
    list2->insert(new GUI::Label(window, new GUI::Point(0,40),"1024x768",&font,25,sf::Color(0,0,0),sf::Color(127,127,0),sf::Color(0,0,0)),changeResolution,new Resolution(window,"1024x768",1024,768));
    list2->insert(new GUI::Label(window, new GUI::Point(0,40),"1920x1080",&font,25,sf::Color(0,0,0),sf::Color(127,127,0),sf::Color(0,0,0)),changeResolution,new Resolution(window,"1920x1080",1920,1080));

    list_up->setClickCallback(*ListItemUp,list1);
    list_down->setClickCallback(*ListItemDown,list1);
    list_del->setClickCallback(*ListItemDel,list1);
    list_insert->setClickCallback(*ListItemInsert,list1);
    list_clear->setClickCallback(*ListItemClear,list1);

    sf::Event event;
    sf::Clock clock;
    float dt;

    while(window->isOpen())
    {
        dt = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        dt /= 800;
        if(!timer->isRun() && !progress->isFilled() && timer_1->getGUIStatus() == GUI::GUI_STATUS::CLICK) timer->start();
        if(progress->isFilled()) timer->stop();

        if(!timer2->isRun() && !progress2->isFilled() && timer_2->getGUIStatus() == GUI::GUI_STATUS::CLICK) timer2->start();
        if(progress2->isFilled()) timer2->stop();

        timer->update(dt);
        timer2->update(dt);


        while(window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                {
                    window->close();
                    break;
                }
                case sf::Event::Resized:
                {
                    break;
                }
                case sf::Event::MouseEntered:
                {
                    if(!GUI::GUI::isAnyGUICorning)
                    {
                        sf::Cursor cursor;
                        cursor.loadFromSystem(sf::Cursor::Arrow);
                        window->setMouseCursor(cursor);
                    }
                    break;

                }
                case sf::Event::TextEntered:
                {
                    if(textinput->Activated()) textinput->inputSymbol(event.text.unicode);
                    break;
                }
                default:
                {
                    GUI::GUI::updateEvents(event);
                    break;
                }
            }
        }
        window->clear(sf::Color::White);



        if(check->isChecked() && GUI::GUI::mouse_click_event == GUI::MOUSE_CLICK_EVENTS::RIGHTCLICK)
        {
            for(auto it = GUIVECTOR.begin(); it != GUIVECTOR.end(); ++it)
            {
                if((*it)->getGUIStatus() == GUI::GUI_STATUS::HOVER) (*it)->startMove();
            }
        }
        if(check2->isChecked())
        {
            for(auto it = GUIVECTOR.begin(); it != GUIVECTOR.end(); ++it)
            {
                (*it)->Resized();
            }
        }
        if(GUI::GUI::mouse_click_event == GUI::MOUSE_CLICK_EVENTS::NONECLICK)
        {
            for(auto it = GUIVECTOR.begin(); it != GUIVECTOR.end(); ++it)
            {
                (*it)->endMove();
            }

        }

        for(auto it = GUIVECTOR.begin(); it != GUIVECTOR.end(); ++it)
        {
            (*it)->setBoxShow(check3->isChecked());
            (*it)->update();
            (*it)->render();
        }
        window->display();
        //system("cls");
    }
    return 0;
}
