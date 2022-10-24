#include "Map.h"
Map::Map(int x, int y, int tempTileSize, Object* obj, bool isNull)
{
	tileX = x ;
	tileY = y ;
	tileSize = tempTileSize;
	map.resize(tileY , std::vector<Tile>(tileX, *(new Tile())));

	if (isNull) {
		for (int i = 0; i < tileX; i++) {
			for (int j = 0; j < tileY; j++) {
				map[i][j] = *(new Tile(i * tileSize, j * tileSize, tileSize, obj, 1));
			}
		}
	}
	else {
		for (int i = 0; i < tileX; i++) {
			for (int j = 0; j < tileY; j++) {
				map[i][j] = *(new Tile(i * tileSize, j * tileSize, tileSize, obj, 0));
			}
		}
	}

	
}
Map::Map()
{
}
Map::~Map()
{
}

void Map::drawMap(sf::RenderWindow* wnd) {
	for (int i = 0; i < tileX; i++) {
		for (int j = 0; j < tileY; j++) {
			map[i][j].drawTile(wnd);
		}
	}
}

int Map::getTileX() {
	return tileX;
}
int Map::getTileY() {
	return tileY;
}
int Map::getTileSize() {
	return tileSize;
}
std::vector<std::vector<Tile>> Map::getMapVector() {
	return map;
}

Map Map::operator=(Map tempMap) {
	tileX = tempMap.getTileX();
	tileY = tempMap.getTileY();
	tileSize = tempMap.getTileSize();
	map = tempMap.getMapVector();
	return *this;
}


void Map::addObjectToMap(Object* obj) {
	int iStart = obj->getX0() / tileSize;
	int iEnd = (obj->getX0() + obj->getWidth()) / tileSize;

	int jStart = obj->getY0() / tileSize;
	int jEnd = (obj->getY0() + obj->getHeight()) / tileSize;
	if (obj->getObjID() != NULL) {
		obj->setTiles(iStart, jStart, iEnd - iStart, jEnd - jStart);
	}
	for (int i = iStart; i <= iEnd; i++) {
		for (int j = jStart; j <= jEnd; j++) {
			map[i][j].addObjectToTile(obj);
		}
	}
}

void Map::removeObjectFromMap(Object *obj) {
	int iStart = obj->getTileX0();
	int iEnd = iStart + obj->getTileWidth();

	int jStart = obj->getTileY0();
	int jEnd = jStart + obj->getTileHeight();

	for (int i = iStart; i <= iEnd; i++) {
		for (int j = jStart; j <= jEnd; j++) {
			map[i][j].removeObjectFromTile(obj);
		}
	}
}

bool Map::checkForCollision(Object* obj) {
	int tempID = obj->getObjID();
	int iStart = obj->getTileX0();
	int iEnd = iStart + obj->getTileWidth();

	int jStart = obj->getTileY0();
	int jEnd = jStart + obj->getTileHeight();

	for (int i = iStart; i <= iEnd; i++) {
		for (int j = jStart; j <= jEnd; j++) {
			if (map[i][j].checkForCollisionInTile(obj, tempID, obj->getX0(), obj->getY0(), obj->getWidth(), obj->getHeight())) {
				return 1;
			}
			
		}
	}
	return 0;
}