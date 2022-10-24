#pragma once
#include "Tile.h"
#include <vector>

class Map
{
public:
	Map(int x, int y, int tileSize, Object* obj, bool isNull);
	Map();
	~Map();
	void drawMap(sf::RenderWindow* wnd);

	int getTileX();
	int getTileY();
	int getTileSize();

	void addObjectToMap(Object *obj);
	void removeObjectFromMap(Object* obj);
	bool checkForCollision(Object* obj);

	std::vector<std::vector<Tile>> getMapVector();
	Map operator=(Map tempMap);

private:
	int tileX;
	int tileY;
	int tileSize;
	std::vector<std::vector<Tile>> map;
};

