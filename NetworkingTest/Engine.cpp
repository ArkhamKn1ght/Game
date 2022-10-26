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
	objects.push_back(obj);

}


void Engine::moveObject(Object* obj, float x, float y, bool sendData) {
	if (sendData) {
		
		float tempX0 = obj->getX0();
		float tempY0 = obj->getY0();
		float tempX = tempX0 + x;
		float tempY = tempY0 + y;
		obj->setX0(tempX);
		obj->setY0(tempY);
		if (!map.checkForCollision(obj) && tempX + obj->getWidth() <= tileSize * map.getTileX()
			&& tempY + obj->getHeight() <= tileSize * map.getTileY()
			&& tempX >= 0 && tempY >= 0) {
			if (timeInMillis <= elapsedTime && sendData) {
				sf::Packet tempPacket;
				tempPacket.clear();
				tempPacket << packetCode::adjustPosition << obj->getObjID() << tempX << tempY;
				sendPacket(tempPacket, destIp, destPort);
			}
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
	if (!map.checkForCollision(obj) && tempX + obj->getWidth() <= tileSize * map.getTileX()
		&& tempY + obj->getHeight() <= tileSize * map.getTileY()
		&& tempX >= 0 && tempY >= 0) {
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
		sf::Packet tempPacket;
		tempPacket.clear();
		tempPacket << packetCode::correctPosition  << obj->getObjID()  << tempX0 << tempY0;
		sendPacket(tempPacket, destIp, destPort);
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
	if (timeInMillis <= elapsedTime) {
		socket.receive(packet, lastReceivedIp, lastReceivedPort);
	}
	
}



void Engine::setElapsedTime() {
	elapsedTime = clock.getElapsedTime().asMilliseconds();
}

void Engine::setTickrate(int tickrate) {
	timeInMillis = 1 / tickrate;
}

void Engine::resetClock() {
	clock.restart();
	elapsedTime = 0;
}
void Engine::handleNetwork() {
	while (true && !fExit) {
		setElapsedTime();
		receivePacket();
		processPackets();
		resetClock();
	}
	
	
}
void Engine::startNetworkThread() {
	th = std::thread(&Engine::handleNetwork, this);
	
}



void Engine::stopThread() {
	fExit = 1;
	th.join();
	
}

void Engine::processPackets() {
	sf::IpAddress tempIp;
	unsigned short tempPort;
	unsigned int tempPacketCode = 0;
	float tempX;
	float tempY;
	int tempID = -123;
	packet >> tempPacketCode;
	if (tempPacketCode == packetCode::correctPosition) {
		packet >>  tempID >> tempX >> tempY;
		getObject(tempID)->setX0(tempX);
		getObject(tempID)->setX0(tempY);
		
	}
	else if (tempPacketCode == packetCode::adjustPosition) {
		if (timeInMillis <= elapsedTime) {
			packet >>  tempID >> tempX >> tempY;
			moveObjectTo(getObject(tempID), tempX, tempY);
			
		}
	}
	packet.clear();
}

Object* Engine::getObject(int ID) {
	for (std::vector<Object*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if ((*it)->getObjID() == ID) {
			return *it;
		}
	}
	return 0;
}