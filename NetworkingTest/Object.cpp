#include "Object.h"
Object::Object(int x0, int y0, int width, int height, int ID)
{
	objID = ID;
	sf::Vector2f tempVect;
	tempVect.x = x0;
	tempVect.y = y0;
	rect.setPosition(tempVect);
	prevRect.setPosition(tempVect);
	tempVect.x = width;
	tempVect.y = height;
	rect.setSize(tempVect);
	prevRect.setScale(tempVect);
	rect.setFillColor(sf::Color::White);
	prevRect.setFillColor(sf::Color::White);
}
Object::Object(int ID) {
	objID = ID;
}

Object::~Object()
{
	
}

float Object::getX0() {
	sf::Vector2f tempVect;
	tempVect = rect.getPosition();
	return tempVect.x;
}
float Object::getY0() {
	sf::Vector2f tempVect;
	tempVect = rect.getPosition();
	return tempVect.y;
}
float Object::getWidth() {
	sf::Vector2f tempVect;
	tempVect = rect.getSize();
	return tempVect.x;
}
float Object::getHeight() {
	sf::Vector2f tempVect;
	tempVect = rect.getSize();
	return tempVect.y;
}

float Object::getPrevX0() {
	sf::Vector2f tempVect;
	tempVect = prevRect.getPosition();
	return tempVect.x;
}
float Object::getPrevY0() {
	sf::Vector2f tempVect;
	tempVect = prevRect.getPosition();
	return tempVect.y;
}
float Object::getPrevWidth() {
	sf::Vector2f tempVect;
	tempVect = prevRect.getSize();
	return tempVect.x;
}
float Object::getPrevHeight() {
	sf::Vector2f tempVect;
	tempVect = prevRect.getSize();
	return tempVect.y;
}

void Object::setX0(float x0) {
	sf::Vector2f tempVect(rect.getPosition());
	tempVect.x = x0;
	rect.setPosition(tempVect);
}
void Object::setY0(float y0) {
	sf::Vector2f tempVect(rect.getPosition());
	tempVect.y = y0;
	rect.setPosition(tempVect);
}
void Object::setWidth(float width) {
	sf::Vector2f tempVect(rect.getSize());
	tempVect.x = width;
	rect.setSize(tempVect);
}
void Object::setHeight(float height) {
	sf::Vector2f tempVect(rect.getSize());
	tempVect.y = height;
	rect.setSize(tempVect);
}

void Object::setPrevX0(float x0) {
	sf::Vector2f tempVect(prevRect.getPosition());
	tempVect.x = x0;
	rect.setPosition(tempVect);
}
void Object::setPrevY0(float y0) {
	sf::Vector2f tempVect(prevRect.getPosition());
	tempVect.y = y0;
	rect.setPosition(tempVect);
}
void Object::setPrevWidth(float width) {
	sf::Vector2f tempVect(prevRect.getSize());
	tempVect.x = width;
	rect.setSize(tempVect);
}
void Object::setPrevHeight(float height) {
	sf::Vector2f tempVect(prevRect.getSize());
	tempVect.y = height;
	rect.setSize(tempVect);
}


sf::RectangleShape Object::getRect() {
	return rect;
}
sf::RectangleShape Object::getPrevRect() {
	return prevRect;
}

Object Object::operator=(Object tempObj) {
	rect = tempObj.getRect();
	objTileX0 = tempObj.getTileX0();
	objTileY0 = tempObj.getTileY0();
	objTileWidth = tempObj.getTileWidth();
	objTileHeight = tempObj.getTileHeight();
	sf::RectangleShape rect;
	return *this;
}

int Object::getObjID() {
	return objID;
}

void Object::drawObject(sf::RenderWindow* wnd) {
wnd->draw(rect);
}

void Object::setTiles(int x0, int  y0, int  width, int  height) {
	objTileX0 = x0;
	objTileY0 = y0;
	objTileWidth = width;
	objTileHeight = height;
}

int Object::getTileX0() {
	return objTileX0;
}
int Object::getTileY0() {
	return objTileY0;
}
int Object::getTileWidth() {
	return objTileWidth;
}
int Object::getTileHeight() {
	return objTileHeight;
}

void Object::setObjColor(sf::Color color) {
	rect.setFillColor(color);
}