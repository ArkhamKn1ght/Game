#include "Engine.h"
#include "SFML/Network.hpp"
Engine::Engine(int mapWidth, int mapHeight, int tempTileSize, Object* obj) {
	tileSize = tempTileSize;
	Map tempMap(mapWidth, mapHeight, tileSize, obj, 1);
	map = tempMap;
	
}

Engine::~Engine()
{
}

void Engine::drawMap(sf::RenderWindow* wnd) {
	map.drawMap(wnd);
}


void Engine::addObject(Object* obj) {
	map.addObjectToMap(obj);

}


void Engine::moveObject(Object* obj, float x, float y, bool sendData) {
	if (sendData) {
		
		float tempX0 = obj->getX0();
		float tempY0 = obj->getY0();
		float tempX = x;
		float tempY = y;
		obj->setX0(tempX);
		obj->setY0(tempY);
		if (!map.checkForCollision(obj)) {
			obj->setX0(tempX0);
			obj->setY0(tempY0);
			map.removeObjectFromMap(obj);
			obj->setX0(tempX);
			obj->setY0(tempY);
			map.addObjectToMap(obj);
			sf::IpAddress tempIp;
			sf::UdpSocket socket;
			socket.setBlocking(false);
			sf::Packet packet;
			socket.bind(2003, "192.168.116.2");
			packet.clear();
			packet << x << y;
			socket.send(packet, "192.168.116.2", 2000);
			socket.unbind();
		}
		else {
			obj->setX0(tempX0);
			obj->setY0(tempY0);
		}
	}
	else {
		float tempX0 = obj->getX0();
		float tempY0 = obj->getY0();
		float tempX = x;
		float tempY = y;
		obj->setX0(tempX);
		obj->setY0(tempY);
		if (!map.checkForCollision(obj)) {
			obj->setX0(tempX0);
			obj->setY0(tempY0);
			map.removeObjectFromMap(obj);
			obj->setX0(tempX);
			obj->setY0(tempY);
			map.addObjectToMap(obj);
		}
		else {
			obj->setX0(tempX0);
			obj->setY0(tempY0);
		}
	}
	
	
}

void Engine::moveObjectTo(Object* obj, float x, float y) {
	float tempX0 = obj->getX0();
	float tempY0 = obj->getY0();
	float tempX = x;
	float tempY = y;
	obj->setX0(tempX);
	obj->setY0(tempY);
	if (!map.checkForCollision(obj)) {
		obj->setX0(tempX0);
		obj->setY0(tempY0);
		map.removeObjectFromMap(obj);
		obj->setX0(tempX);
		obj->setY0(tempY);
		map.addObjectToMap(obj);
	}
	else {
		obj->setX0(tempX0);
		obj->setY0(tempY0);
	}
}