#pragma once
#include "Map.h"
#include "SFML/Network.hpp"
class Engine
{
public:
	Engine(int mapWidth, int mapHeight, int tempTileSize, Object *obj);
	~Engine();

	void addObject(Object* obj);
	void moveObject(Object* obj, float x, float y, bool sendData);
	void moveObjectTo(Object* obj, float x, float y);
	void drawMap(sf::RenderWindow* wnd);
	void setUpNetwork(sf::IpAddress tempLocalIp, sf::IpAddress tempDestIp,
		unsigned short tempLocalPort, unsigned short tempDestPort);
	void sendPacket(sf::Packet tempPacket, sf::IpAddress tempDestIp, unsigned short tempDestPort);
	void receivePacket();
	void correctMovement(Object& obj);
	
private:
	Map map;
	int tileSize;

	sf::IpAddress lastReceivedIp;
	unsigned short lastReceivedPort;

	sf::IpAddress localIp;
	unsigned short localPort;
	
	sf::IpAddress destIp;
	unsigned short destPort;

	sf::UdpSocket socket;
	sf::Packet packet;

};



