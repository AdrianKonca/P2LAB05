#pragma once
#include "Item.h"

class Room
{
	std::string description;
	int x;
	int y;
	static int minX;
	static int maxX;
	static int minY;
	static int maxY;
	Room *neighborN;
	Room *neighborW;
	Room *neighborE;
	Room *neighborS;
	Item *item;
	double f, h;
	double g = 0;
	bool wasEvaluated = false;
	Room *parent;
	static void clearAfterPathfinding(std::vector <Room*> &rooms); 
	static std::vector <Room*> rebuildPath(std::vector <Room*> &rooms, Room* &endRoom);
public:
	std::string getDescription()	{ return description; };
	Room *getNeighborN()			{ return neighborN; };
	Room *getNeighborW()			{ return neighborW; };
	Room *getNeighborE()			{ return neighborE; };
	Room *getNeighborS()			{ return neighborS; };
	std::vector<Room*> getNeighbors();
	bool hasItem()					{ return (item != nullptr); };
	Item *getItem()					{ return item; };
	bool placeItem(Item* item);

	void assignNeighbors(std::vector <Room*> &rooms);
	char getSymbol();

	static float getHDistanceBetweenRooms(const Room *roomA, const Room *roomB);


	static Room* findRoomByCoordinates(std::vector <Room*> &rooms, int x, int y);
	static void findNeighbors(std::vector <Room*> &rooms);
	static std::string createMap(std::vector <Room*> &rooms);
	static std::vector <Room*> getShortestPathBetweenRooms(std::vector <Room*> &rooms, Room* startRoom, Room* endRoom);
	Room(int x, int y);
	~Room();
};

