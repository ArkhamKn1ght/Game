#pragma once
#include <SFML/Graphics.hpp>
class Object
{
public:
	Object(int x0, int y0, int width, int height, int ID);
	Object(int ID);
	~Object();
	float getX0();
	float getY0();
	float getWidth();
	float getHeight();

	float getPrevX0();
	float getPrevY0();
	float getPrevWidth();
	float getPrevHeight();

	sf::RectangleShape getRect();
	sf::RectangleShape getPrevRect();

	void setX0(float x0);
	void setY0(float y0);
	void setWidth(float width);
	void setHeight(float height);

	void setPrevX0(float x0);
	void setPrevY0(float y0);
	void setPrevWidth(float width);
	void setPrevHeight(float height);

	int getObjID();

	int getTileX0();
	int getTileY0();
	int getTileWidth();
	int getTileHeight();

	void setTiles(int x0, int  y0, int  width, int  height);
	void drawObject(sf::RenderWindow* wnd);
	Object operator=(Object tempObj);
	void setObjColor(sf::Color color);
private:
	int objID = 0;
	int objTileX0 = -1;
	int objTileY0 = -1;
	int objTileWidth = -1;
	int objTileHeight = -1;
	sf::RectangleShape rect;
	sf::RectangleShape prevRect;
};

