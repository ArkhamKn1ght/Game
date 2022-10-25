#include "Engine.h"

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
		float tempX = tempX0 + x;
		float tempY = tempY0 + y;
		obj->setX0(tempX);
		obj->setY0(tempY);
		if (!map.checkForCollision(obj)) {
			obj->setX0(tempX0);
			obj->setY0(tempY0);
			map.removeObjectFromMap(obj);
			obj->setX0(tempX);
			obj->setY0(tempY);
			map.addObjectToMap(obj);
			sf::Packet tempPacket;
			tempPacket.clear();
			tempPacket << tempX << tempY;
			sendPacket(tempPacket, destIp, destPort);
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

void Engine::setUpNetwork(sf::IpAddress tempLocalIp, sf::IpAddress tempDestIp,
	unsigned short tempLocalPort, unsigned short tempDestPort) {
	localIp = tempLocalIp;
	destIp = tempDestIp;
	localPort = tempLocalPort;
	destPort = tempDestPort;
	socket.bind(localPort, localIp);
	socket.setBlocking(false);
}

void Engine::sendPacket(sf::Packet tempPacket, sf::IpAddress tempDestIp, unsigned short tempDestPort) {
	socket.send(tempPacket, tempDestIp, tempDestPort);
}

void Engine::receivePacket() {
	socket.receive(packet, lastReceivedIp, lastReceivedPort);
}

void Engine::correctMovement(Object &obj) {
	if (packet.getDataSize() > 0) {
		float tempX, tempY = 0;
		packet >> tempX >> tempY;
		moveObjectTo(&obj, tempX, tempY);
		packet.clear();
	}
}