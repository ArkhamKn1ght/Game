#include "Tile.h"
#include <algorithm>


Tile::Tile(int x0, int y0, int tileSize, Object* obj, bool isNull)
{
	sf::Vector2f tempVect;
	tempVect.x = x0;
	tempVect.y = y0;
	rect.setPosition(tempVect);
	tempVect.x = tileSize;
	tempVect.y = tileSize;
	rect.setSize(tempVect);
	objStack.push_back(obj);

	rect.setFillColor(sf::Color::Black);
	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::White);
	if (isNull) {
		fEmpty = 1;
	}
	else {
		fEmpty = 0;
	}
}


Tile::Tile()
{
}

Tile::~Tile()
{

}

float Tile::getX0() {
	sf::Vector2f tempVect;
	tempVect = rect.getPosition();
	return tempVect.x;
}
float Tile::getY0() {
	sf::Vector2f tempVect;
	tempVect = rect.getPosition();
	return tempVect.y;
}
float Tile::getTileSize() {
	sf::Vector2f tempVect;
	tempVect = rect.getSize();
	return tempVect.y;
}

std::vector <Object*> Tile::getObjStack() {
	return objStack;
}

bool Tile::isEmpty() {
	return fEmpty;
}
void Tile::drawTile(sf::RenderWindow* wnd) {
	
	if (!fEmpty) {
		rect.setFillColor(sf::Color::Red);
	}
	else {
		rect.setFillColor(sf::Color::Black);
	}
	wnd->draw(rect);
}


void Tile::addObjectToTile(Object* obj) {
	objStack.push_back(obj);
	fEmpty = 0;
}


bool Tile::removeObjectFromTile(Object* obj) {
	int tempID = obj->getObjID();
	for (auto it = objStack.begin(); it != objStack.end(); ) {
		if (tempID == (*it)->getObjID()) {
			it = objStack.erase(it);
			if (objStack.size() == 1) {
				fEmpty = 1;
			}
			return 1;
		}
		else {
			it++;
		}
	}
	return 0;
}

bool Tile::checkForCollisionInTile(Object* obj, int ID, float x0, float y0, float width, float height) {
	int test = 0;
	for (auto it = objStack.begin(); it != objStack.end(); test++) {
		if (ID != (*it)->getObjID()) {
			if (x0 < (*it)->getX0() + (*it)->getWidth() && x0 + width > (*it)->getX0() && y0 < (*it)->getY0() + (*it)->getHeight() && y0 + height > (*it)->getY0() ) {
				return 1;
			}
			it++;
		}
		else {
			it++;
		}
		
	}
	return 0;
}

/*int i = 0;
	int testj = objStack.size();
	for (std::vector <Object*>::iterator it = objStack.begin(); it != objStack.end();++it, ++i) {
		if (objStack[i]->getObjID() == tempID) {
			
			
			objStack.erase(it);

			if (objStack.size() == 1) {
				fEmpty = 1;
			}
			return 1;
		}
		
	}*/