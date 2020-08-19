#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#define RESOURCEFOLDER "resouces/"
using namespace std;
enum DIR{
    STOP = -1,
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    UP_RIGHT,
    UP_LEFT,
    DOWN_RIGHT,
    DOWN_LEFT
};
enum TYPERECIEVE{
    NONE = -1,
    CLIENT_CONNECT = 0,
    CLIENT_MOVE
};
class Animation{
private:
    map<int,sf::IntRect> frames;
    int totalFrames;
    sf::Sprite *sprite;
    int currentFrame;
    float time;
public:
    Animation()
    {
        this->currentFrame = 0;
        this->time = 0;
        this->totalFrames = 0;
    }
    void setSprite(sf::Sprite *sprite)
    {
        this->sprite = sprite;
    }
    void addFrame(sf::IntRect frame)
    {
        frames[this->totalFrames] = frame;
        this->totalFrames++;
    }
    void play(const float &dt)
    {
        this->time += dt;
        if(this->time > 40) this->currentFrame++;
        if(this->currentFrame >= this->totalFrames) this->currentFrame = 0;
        this->sprite->setTextureRect(this->frames[this->currentFrame]);
    }
    sf::IntRect & operator[](const int index)
    {
        return frames[index];
    }
};
class Entity{
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f spritePosition;
    sf::Vector2f spriteAcceleration;
public:
    Entity(const string &textureName, sf::Vector2f position = {0,0}, sf::Vector2f acceleration = {0,0})
    {
        this->texture.loadFromFile(textureName);
        this->sprite.setTexture(this->texture);
        this->spritePosition = position;
        this->spriteAcceleration = acceleration;
    }
    virtual void update(map<int,sf::Sprite *> &playerSptires,const float &dt) = 0;
    virtual void draw(map<int,sf::Sprite *> &playerSptires,sf::RenderWindow *window) = 0;
};
class Player : public Entity{
private:
    map<int,bool> keyPressed;
    sf::Vector2f playerPosition;
    sf::UdpSocket socket;
    sf::IpAddress adress;
    unsigned short port;

    sf::IpAddress adress2;
    unsigned short port2;
    sf::Packet packet;
    float speed = 0.2;
    int dir;

    int playerID;
    Animation ANIM_UP;
    Animation ANIM_DOWN;
    Animation ANIM_LEFT;
    Animation ANIM_RIGHT;
    Animation ANIM_IDLE;
    void InitAnimation()
    {
        ANIM_UP.setSprite(&this->sprite);
        ANIM_DOWN.setSprite(&this->sprite);
        ANIM_LEFT.setSprite(&this->sprite);
        ANIM_RIGHT.setSprite(&this->sprite);
        ANIM_IDLE.setSprite(&this->sprite);

        ANIM_UP.addFrame(sf::IntRect(187,2,19,31));
        ANIM_UP.addFrame(sf::IntRect(206,2,19,31));
        ANIM_UP.addFrame(sf::IntRect(225,2,19,31));
        ANIM_UP.addFrame(sf::IntRect(244,2,19,31));

        ANIM_DOWN.addFrame(sf::IntRect(433,2,20,31));
        ANIM_DOWN.addFrame(sf::IntRect(453,2,20,31));
        ANIM_DOWN.addFrame(sf::IntRect(475,2,22,31));
        ANIM_DOWN.addFrame(sf::IntRect(498,2,21,31));


        ANIM_LEFT.addFrame(sf::IntRect(267,2,20,31));
        ANIM_LEFT.addFrame(sf::IntRect(288,2,20,31));
        ANIM_LEFT.addFrame(sf::IntRect(308,2,20,31));
        ANIM_LEFT.addFrame(sf::IntRect(328,3,20,31));

        ANIM_RIGHT.addFrame(sf::IntRect(600,2,20,31));
        ANIM_RIGHT.addFrame(sf::IntRect(621,3,20,31));
        ANIM_RIGHT.addFrame(sf::IntRect(643,3,20,31));
        ANIM_RIGHT.addFrame(sf::IntRect(665,3,19,31));
    }
    void playerConnect()
    {
        this->socket.setBlocking(false);
        this->packet << TYPERECIEVE::CLIENT_CONNECT;
        this->socket.send(this->packet,this->adress,this->port);
        this->packet.clear();
        cout << "My IP: " << sf::IpAddress::getLocalAddress() << "\nMy Port: " << this->socket.getLocalPort() << "\n";
    }
public:

    Player(const string &textureName,sf::Vector2f position = {0,0}) : Entity(textureName,position)
    {
        this->InitAnimation();
        this->sprite.setTextureRect(ANIM_DOWN[0]);
        this->sprite.setPosition(this->spritePosition);
        this->dir = DIR::STOP;
        this->keyPressed[sf::Keyboard::A] = false;
        this->keyPressed[sf::Keyboard::D] = false;
        this->keyPressed[sf::Keyboard::W] = false;
        this->keyPressed[sf::Keyboard::S] = false;

        this->packet.clear();
        this->adress = "192.168.0.39";
        this->port = 5001;
        this->playerConnect();
    }
    int getID()
    {
        return this->playerID;
    }
    void move(int dir)
    {
        //if(dir != DIR::STOP) this->sprite.setTextureRect(this->dirSprite[dir]);
        this->dir = dir;
        switch(dir)
        {
        case DIR::STOP:
            {
                this->spriteAcceleration = {0,0};
                break;
            }
        case DIR::UP:
            {
                this->spriteAcceleration = {0,-this->speed};
                break;
            }
        case DIR::DOWN:
            {
                this->spriteAcceleration = {0,this->speed};
                break;
            }
        case DIR::LEFT:
            {
                this->spriteAcceleration = {-this->speed,0};
                break;
            }
        case DIR::RIGHT:
            {
                this->spriteAcceleration = {this->speed,0};
                break;
            }
        case DIR::DOWN_LEFT:
            {
                this->spriteAcceleration = {-this->speed,this->speed};
                cout << "1\n";
                break;
            }
        case DIR::DOWN_RIGHT:
            {
                this->spriteAcceleration = {this->speed,this->speed};
                cout << "2\n";
                break;
            }
        case DIR::UP_LEFT:
            {
                this->spriteAcceleration = {-this->speed,-this->speed};
                cout << "3\n";
                break;
            }
        case DIR::UP_RIGHT:
            {
                this->spriteAcceleration = {this->speed,-this->speed};
                cout << "4\n";
                break;
            }
        }
    }
    void draw(map<int,sf::Sprite *> &playerSptires, sf::RenderWindow *window)
    {
        for(pair<int,sf::Sprite *> element : playerSptires)
        {
            window->draw(*element.second);
        }
        //window->draw(this->sprite);
    }
    void updateSFMLEvent(sf::Event &event)
    {
        if(event.type == sf::Event::KeyReleased)
        {
            this->move(DIR::STOP);
            this->keyPressed[event.key.code] = false;
        }
    }
    void inputKeyboard()
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            this->keyPressed[sf::Keyboard::A] = true;
            this->move(DIR::LEFT);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            this->keyPressed[sf::Keyboard::D] = true;
            this->move(DIR::RIGHT);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            this->keyPressed[sf::Keyboard::W] = true;
            this->move(DIR::UP);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            this->keyPressed[sf::Keyboard::S] = true;
            this->move(DIR::DOWN);
        }
        if(keyPressed[sf::Keyboard::W] && keyPressed[sf::Keyboard::A])
        {
            this->move(DIR::UP_LEFT);
        }
        if(keyPressed[sf::Keyboard::W] && keyPressed[sf::Keyboard::D])
        {
            this->move(DIR::UP_RIGHT);
        }
        if(keyPressed[sf::Keyboard::S] && keyPressed[sf::Keyboard::A])
        {
            this->move(DIR::DOWN_LEFT);
        }
        if(keyPressed[sf::Keyboard::S] && keyPressed[sf::Keyboard::D])
        {
            this->move(DIR::DOWN_RIGHT);
        }
    }
    void SERVERANSWER(map<int,sf::Sprite *> &playerSptires)
    {
        if(this->socket.receive(this->packet,this->adress2,this->port2) == sf::Socket::Done)
        {
            int type = TYPERECIEVE::NONE;
            this->packet >> type;
            cout << "type = " << type << "\n";
            if(type == TYPERECIEVE::CLIENT_CONNECT)
            {
                int id = 0;
                sf::Vector2f pos;
                this->packet >> id;
                this->packet >> pos.x >> pos.y;
                this->playerID = id;
                string resources = RESOURCEFOLDER;
                resources+="sprites.gif";
                sf::Sprite sprite;
                sf::Texture a;
                a.loadFromFile(resources);

                sprite.setTexture(a);
                sprite.setTextureRect(sf::IntRect(433,2,20,31));
                playerSptires[id] = &sprite;
                playerSptires[id]->setPosition(pos);
            }
            if(type == TYPERECIEVE::CLIENT_MOVE)
            {
                int id = 0;
                this->packet >> id;
                sf::Vector2f pos;
                this->packet >> pos.x >> pos.y;
                playerSptires[id]->setPosition(pos);
            }
        }
    }
    void update(map<int,sf::Sprite *> &playerSptires, const float &dt)
    {
        SERVERANSWER(playerSptires);
        this->inputKeyboard();
        if(this->dir == DIR::UP)
            ANIM_UP.play(dt);
        if(this->dir == DIR::DOWN)
            ANIM_DOWN.play(dt);
        if(this->dir == DIR::RIGHT)
            ANIM_RIGHT.play(dt);
        if(this->dir == DIR::LEFT)
            ANIM_LEFT.play(dt);

        this->spritePosition += this->spriteAcceleration*dt;
        this->sprite.setPosition(this->spritePosition);

        if(this->dir != DIR::STOP)
        {
            int type = TYPERECIEVE::CLIENT_MOVE;
            this->packet << type;
            this->packet << this->spritePosition.x << this->spritePosition.y;
            this->socket.send(this->packet,this->adress,this->port);
            this->packet.clear();
        }
    }
};


void move(int playerID, int dir, map<int,sf::CircleShape> &shapes)
{
     float speed = 0.1;
    sf::Vector2f pos = shapes[playerID].getPosition();
    switch(dir)
    {
    case DIR::DOWN:
        {
            pos.y += speed;
            break;
        }
    case DIR::UP:
        {
            pos.y -= speed;
            break;
        }
    case DIR::LEFT:
        {
            pos.x -= speed;
            break;
        }
    case DIR::RIGHT:
        {
            pos.x += speed;
            break;
        }
    }
    shapes[playerID].setPosition(pos);
    sf::UdpSocket socket;
    sf::Packet packet;
    sf::IpAddress IPSERVER = "192.168.0.39";
    unsigned short PORTSERVER = 5001;
    packet.clear();
    packet << TYPERECIEVE::CLIENT_MOVE << playerID << pos.x << pos.y;
    socket.send(packet,IPSERVER,PORTSERVER);
}

int main()
{
    map<int,sf::Vector2f> shapePosition;
    map<int,sf::CircleShape> shapes;

    bool isFocus = true;


    bool isConnected = false;
    int clientCounts = -1;
    int playerID = -1;
    sf::UdpSocket clientsocket;
    clientsocket.setBlocking(false);
    sf::IpAddress IPSERVER = "192.168.0.39";
    unsigned short PORTSERVER = 5001;
    sf::IpAddress IPREMOTE;
    unsigned short PORTREMOTE = 5001;
    sf::Packet packet;
    packet.clear();
    sf::CircleShape shape;
    shape.setRadius(50.f);
    shape.setFillColor(sf::Color::Green);
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800,600),"GAME");
    packet << TYPERECIEVE::CLIENT_CONNECT;
    if(clientsocket.send(packet,IPSERVER,PORTSERVER) != sf::Socket::Done)
    {
        cout << "Error server\n";
        return 0;
    }
    packet.clear();
    while(window->isOpen())
    {
        sf::Event event;
        while(window->pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed:
                {
                    window->close();
                    break;
                }
            case sf::Event::GainedFocus:
                {
                    isFocus = true;
                    break;
                }
            case sf::Event::LostFocus:
                {
                    isFocus = false;
                }

            }
        }
        window->clear();

        if(clientsocket.receive(packet,IPREMOTE,PORTREMOTE) == sf::Socket::Done)
        {
            int type = TYPERECIEVE::NONE;
            packet >> type;
            if(type == TYPERECIEVE::CLIENT_CONNECT)
            {
                sf::Vector2f pos = {0,0};
                int ID = -1;
                packet >> ID;
                packet >> pos.x >> pos.y;
                if(!isConnected) // подключился данный игрок
                {
                    playerID = ID;
                    packet >> clientCounts;
                    shapePosition[playerID] = {0,0};
                    shapes[playerID] = sf::CircleShape(20);
                    cout << "Connected players:\n";
                    for(int i(0), id(-1); i < clientCounts; i++)
                    {
                        packet >> ID;
                        packet >> pos.x >> pos.y;
                        if(ID == playerID) continue;
                        shapes[ID] = sf::CircleShape(20);
                        shapes[ID].setPosition(pos);
                        cout << "ID: " << ID << "\n";
                    }
                    isConnected = true;
                }
                else
                {
                    cout << "New playerID = " << ID << "\n";
                    shapes[ID] = sf::CircleShape(20);
                    shapes[ID].setPosition(pos);
                }
            }
            if(type == TYPERECIEVE::CLIENT_MOVE)
            {
                int ID = -1;
                packet >> ID;
                sf::Vector2f pos;
                packet >> pos.x >> pos.y;
                shapes[ID].setPosition(pos);
            }
        }

        if(isConnected)
        {

            for(pair<int,sf::CircleShape> element : shapes)
            {
                window->draw(element.second);
            }
            if(isFocus)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    move(playerID,DIR::LEFT,shapes);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    move(playerID,DIR::RIGHT,shapes);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    move(playerID,DIR::UP,shapes);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    move(playerID,DIR::DOWN,shapes);
                }
            }
            //window->draw(shape);
        }

        window->display();
    }





    /*map<int,sf::Sprite *> playerSptires;
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(800,600),"SFML is open");
    //window->setFramerateLimit(60);
    string resources = RESOURCEFOLDER;
    resources+="sprites.gif";

    Player player(resources,{100,100});

    sf::Clock clock;
    float dt;

    while(window->isOpen())
    {
        dt = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        dt /= 800;
        sf::Event event;
        while(window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window->close();
            }
            player.updateSFMLEvent(event);
        }
        player.update(playerSptires,dt);
        window->clear();
        player.draw(playerSptires,window);
        window->display();
    }*/
    return 0;
}
