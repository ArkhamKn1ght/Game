#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/audio.hpp"
#include <iostream>
#include "Engine.h"
#include <thread>

#define NULL 0 

void checkNetwork(Engine *game, Object *obj) {
    sf::UdpSocket socket;
    socket.setBlocking(false);
    sf::IpAddress tempIp;
    unsigned short tempPort;
    sf::Packet packet;
    socket.bind(2002, "192.168.0.102");
    while (true) {
        
        
        
        if (socket.receive(packet, tempIp, tempPort) != sf::Socket::Done) {

        }
        else {
            float x = 0;
            float y = 0;
            packet >> x >> y;
            game->moveObject(obj, x, y, 0);
        }
    }
    return;
}
int main()
{
    bool flag = 1;
    sf::RenderWindow window(sf::VideoMode(900, 900), "Tiles test");
    window.setFramerateLimit(144);
    
    Object nullObj(NULL);
    
    Engine game(90, 90, 10, &nullObj);
    Object obj(50, 50, 30, 30, 10000);
    Object obj2(150, 150, 30, 30, 10002);
    Object wall(300, 60, 100, 10, 10001);
    wall.setObjColor(sf::Color::Yellow);
    game.addObject(&obj);
    game.addObject(&obj2);
    game.addObject(&wall);
    std::thread th(checkNetwork, &game, &obj2);
    th.detach();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::GainedFocus) {
                flag = 1;
            }
            if (event.type == sf::Event::LostFocus) {
                flag = 0;
            }
        }
        if (flag) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                game.moveObject(&obj, -2.5f, 0, 1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                game.moveObject(&obj, 2.5f, 0, 1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                game.moveObject(&obj, 0, -2.5f, 1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                game.moveObject(&obj, 0, 2.5f, 1);
            }
       }
        
        
        window.clear();
        game.drawMap(&window);
        obj.drawObject(&window);
        obj2.drawObject(&window);
        wall.drawObject(&window);
        window.display();
    }

    return 0;
}