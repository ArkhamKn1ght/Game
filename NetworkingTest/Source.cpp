#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/audio.hpp"
#include <iostream>
#include "Engine.h"
#include <thread>
#include <functional>

#define NULL 0 

void startNetwork(Engine &engine) {
    sf::IpAddress tempDestIp;
    unsigned short tempDestPort;
    sf::IpAddress tempLocalIp;
    unsigned short tempLocalPort;
    std::cout << "Enter destIp: "; 
    std::cin >> tempDestIp;
    std::cout << "Enter destPort: ";
    std::cin >> tempDestPort;
    std::cout << "Enter localIp: ";
    std::cin >> tempLocalIp;
    std::cout << "Enter localPort: ";
    std::cin >> tempLocalPort;
    engine.setUpNetwork(tempLocalIp, tempDestIp, tempLocalPort, tempDestPort);
}

int main()
{
    bool flag = 1;
    
    
    
    Object nullObj(NULL);
    
    Engine game(90, 90, 10, &nullObj);
    Object obj(50, 50, 30, 30, 10000);
    Object obj2(150, 150, 30, 30, 10002);
    Object wall(300, 60, 100, 10, 10001);
    wall.setObjColor(sf::Color::Yellow);
    game.addObject(&obj);
    game.addObject(&obj2);
    game.addObject(&wall);

    startNetwork(game);
    game.setTickrate(10);
    game.startNetworkThread();
    sf::RenderWindow window(sf::VideoMode(900, 900), "Dimas pidoras");
    window.setFramerateLimit(144);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                game.exit();
                window.close();
            }
                
            if (event.type == sf::Event::GainedFocus) {
                flag = 1;
            }
            if (event.type == sf::Event::LostFocus) {
                flag = 0;
            }
        }
        //game.setElapsedTime();
        //game.receivePacket();
        //game.correctMovement(obj);
        if (flag) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                game.moveObject(&obj2, -2.5f, 0, 1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                game.moveObject(&obj2, 2.5f, 0, 1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                game.moveObject(&obj2, 0, -2.5f, 1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                game.moveObject(&obj2, 0, 2.5f, 1);
            }
       }
        
        
        window.clear();
        game.drawMap(&window);
        obj.drawObject(&window);
        obj2.drawObject(&window);
        wall.drawObject(&window);
        window.display();
    }
    system("pause");
    return 0;
}