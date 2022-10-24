#pragma once
#include "Map.h"
class Engine
{
public:
	Engine(int mapWidth, int mapHeight, int tempTileSize, Object *obj);
	~Engine();

	void addObject(Object* obj);
	void moveObject(Object* obj, float x, float y, bool sendData);
	void moveObjectTo(Object* obj, float x, float y);
	void drawMap(sf::RenderWindow* wnd);

	
private:
	Map map;
	int tileSize;
};



