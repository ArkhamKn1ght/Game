#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

class Tile
{
public:
	Tile(int x0, int y0, int tileSize, Object* obj, bool isNull);
	Tile();
	bool isEmpty();
	~Tile();

	float getX0();
	float getY0();
	float getTileSize();

	std::vector <Object*> getObjStack();
	
	void addObjectToTile(Object *obj);
	void drawTile(sf::RenderWindow* wnd);

	bool checkForCollisionInTile(Object* obj, int ID, float x0, float y0, float width, float height);
	bool removeObjectFromTile(Object *obj);

private:
	sf::RectangleShape rect;
	std::vector <Object*> objStack;
	bool fEmpty = 1;
};


